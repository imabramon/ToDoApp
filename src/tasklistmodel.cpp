#include "tasklistmodel.h"

#include "QDebug"
#include "datastorer.h"


TaskListModel::TaskListModel(QObject* parent) : QObject(parent), m_task(), uniqueid(0)
{

}

void TaskListModel::addTask(QString name, QString category, bool isDone) {
    m_task.append(Task(uniqueid++, name, category, isDone));
    //emit dataChanged();
    emit taskAdded();
}

void TaskListModel::delTask(int index){
    qDebug() << "Delete element at index " << index;
    m_task.erase(getElement(index));
    emit taskDeleted();
}

void TaskListModel::readList() {
    m_task = DataStorer::readData();

    for (auto i = m_task.begin(); i != m_task.end(); i++) {
            i->id = uniqueid++;
    }
    emit dataChanged();
}

void TaskListModel::storeList() {
    DataStorer::storeData(m_task);
}

QList<Task>::iterator TaskListModel::getElement(int i){
    auto b = m_task.begin();
    for(; b != m_task.end(); b++){
        if(b->id == i) break;
    }
    return b;
}

void TaskListModel::setName(int id, QString name){
    getElement(id)->name = name;
    //emit dataChanged();
    emit taskNameChanged();
}

void TaskListModel::setCompleted(int id, bool completed){
    getElement(id)->isDone = completed;
    emit taskCompletedChanged();
}

void TaskListModel::setCategory(int id, QString category){
    getElement(id)->category = category;
    emit taskCategoryChanged();
}

int TaskListModel::getTaskCountByCategory(QString category) const{
    int count = 0;
    for(auto i = m_task.begin(); i != m_task.end(); i++){
        if(i->category == category) count++;
    }

    return count;
}

int TaskListModel::getComplitedTaskCountByCategory(QString category) const{
    int count = 0;
    for(auto i = m_task.begin(); i != m_task.end(); i++){
        if(i->category == category && i->isDone == true) count++;
    }

    return count;
}

