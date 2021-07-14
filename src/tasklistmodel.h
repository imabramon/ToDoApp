#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>

#include "task.h"


class TaskListModel : public QObject
{
    Q_OBJECT
public:
    explicit TaskListModel(QObject *parent=nullptr);

    Q_INVOKABLE void readList();
    Q_INVOKABLE void storeList();

    Q_INVOKABLE void addTask(QString name, QString category, bool isDone = false);
    Q_INVOKABLE void delTask(int index);

    Q_INVOKABLE void setName(int id, QString name);
    Q_INVOKABLE void setCompleted(int id, bool completed);
    Q_INVOKABLE void setCategory(int id, QString category);

    Q_INVOKABLE int size() const  {return m_task.size();}
    Q_INVOKABLE int getComplitedTaskCountByCategory(QString category) const;
    Q_INVOKABLE int getTaskCountByCategory(QString category) const;

    QList<Task>::iterator begin() {return m_task.begin();}
    QList<Task>::iterator end(){return m_task.end();}
    QList<Task>::iterator getElement(int i);
signals:
    void dataChanged();

    void taskAdded();
    void taskDeleted();
    void taskNameChanged();
    void taskNoteChanged();
    void taskCategoryChanged();
    void taskCompletedChanged();
private:
    QList<Task> m_task;
    int uniqueid;
};

#endif // TASKLISTMODEL_H
