#include "categorylist.h"

#include <QSet>
#include <QDebug>

CategoryList::CategoryList(QObject * parent): QAbstractListModel(parent), m_categories(){}

QVariant CategoryList::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    switch(role) {
    case NameRole:
        return QVariant(m_categories[index.row()]);
    case AllCountRole:
        return QVariant(m_tasks->getTaskCountByCategory(m_categories[index.row()]));
    case ComplitedCountRole:
        return QVariant(m_tasks->getComplitedTaskCountByCategory(m_categories[index.row()]));
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CategoryList::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AllCountRole] = "allCount";
    roles[ComplitedCountRole] = "completedCount";
    return roles;
}

void CategoryList::setTaskData(TaskListModel * tasks){
    qDebug() << "Set TaskData";
    m_tasks = tasks;

    QObject::connect(m_tasks, &TaskListModel::dataChanged, this, &CategoryList::changeData);
    QObject::connect(this, &CategoryList::taskDataChanged, this, &CategoryList::changeData);
    QObject::connect(m_tasks, &TaskListModel::taskAdded, this, &CategoryList::changeData);
    QObject::connect(m_tasks, &TaskListModel::taskDeleted, this, &CategoryList::changeData);
    QObject::connect(m_tasks, &TaskListModel::taskCategoryChanged, this, &CategoryList::changeData);
    QObject::connect(m_tasks, &TaskListModel::taskCompletedChanged, this, &CategoryList::changeData);
    QObject::connect(this, &CategoryList::categoryAdded, this, &CategoryList::changeData);


    emit taskDataChanged();
}

void CategoryList::changeData(){
    qDebug() << "change data";
    beginResetModel();
    QSet<QString> temp;

    for(auto i = m_tempCategories.begin(); i != m_tempCategories.end(); i++)
        temp.insert(*i);

    for(auto i = m_tasks->begin(); i != m_tasks->end(); i++){
        if(temp.find(i->category) == temp.end() && i->category != "None") temp.insert(i->category);
    }

    m_categories.clear();

    m_categories.append("None");


    for(auto i = temp.begin(); i != temp.end(); i++){
        qDebug() << *i;
        m_categories.append(*i);
    }
    endResetModel();
}

void CategoryList::addCategory(QString category){
    m_tempCategories.append(category);

    emit categoryAdded();
}

