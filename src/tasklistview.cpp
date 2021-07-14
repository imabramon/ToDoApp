#include "tasklistview.h"

#include <QVariant>
#include "datastorer.h"
#include <QDebug>

TaskListView::TaskListView(QObject* parent) : QAbstractListModel(parent), m_index(), m_filterByCategory(false), m_filter("")
{
}

QHash<int, QByteArray> TaskListView::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DoneRole] = "completed";
    roles[TaskIdRole] = "taskid";
    roles[CategoryRole] = "category";
    return roles;
}

QVariant TaskListView::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant();
    switch(role) {
    case NameRole:
        return QVariant(m_model->getElement(m_index[index.row()])->name);
    case DoneRole:
        return QVariant(m_model->getElement(m_index[index.row()])->isDone);
    case TaskIdRole:
        qDebug() << "read id";
        return QVariant(m_index[index.row()]);
    case CategoryRole:
        qDebug() << "read category";
        return QVariant(m_model->getElement(m_index[index.row()])->category);
    default:
        return QVariant();
    }
}

void TaskListView::changeData(){
    beginResetModel();
    qDebug() << "ChangeData";
    m_index.clear();
    for(auto i = m_model->begin(); i != m_model->end(); i++){
        if(i->isDone == m_completedFilter && filter(*i)){
            qDebug() << "Append id: " << i->id;
            m_index.append(i->id);
        }
    }

    endResetModel();
}

void TaskListView::updateView(){
    qDebug() << "Update view";
    beginResetModel();
    endResetModel();
}

void TaskListView::setTaskData(TaskListModel * m){
    m_model = m;
    qDebug() << m_model;

    //connect model to view with change data
    QObject::connect(m_model, &TaskListModel::dataChanged, this, &TaskListView::changeData);
    QObject::connect(m_model, &TaskListModel::taskAdded, this, &TaskListView::changeData);
    QObject::connect(m_model, &TaskListModel::taskDeleted, this, &TaskListView::changeData);
    QObject::connect(m_model, &TaskListModel::taskCompletedChanged, this, &TaskListView::changeData);
    QObject::connect(m_model, &TaskListModel::taskCategoryChanged, this, &TaskListView::changeData);

    //connect model to view with update view
    QObject::connect(m_model, &TaskListModel::taskNameChanged, this, &TaskListView::updateView);
    QObject::connect(m_model, &TaskListModel::taskNameChanged, this, &TaskListView::updateView);

    //connect view to view with change data
    QObject::connect(this, &TaskListView::taskDataChanged, this, &TaskListView::changeData);
    QObject::connect(this, &TaskListView::completedFilterChanged, this, &TaskListView::changeData);
    QObject::connect(this, &TaskListView::filterByCategoryChanged, this, &TaskListView::changeData);
    QObject::connect(this, &TaskListView::filterChanged, this, &TaskListView::changeData);

    emit taskDataChanged();
}

void TaskListView:: setCompletedFilter(bool completedFilter){
    m_completedFilter = completedFilter;

    emit completedFilterChanged();
}

void TaskListView::setFilterByCategory(bool filterByCategory){
    m_filterByCategory = filterByCategory;
    emit filterByCategoryChanged();
}

void TaskListView::setFilter(QString filter){
    m_filter = filter;
    emit filterChanged();
}

bool TaskListView::filter(Task & task){
    if(this->m_filterByCategory == false) return true;

    if(task.category == m_filter) return true;

    return false;
}

