#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H


#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QDebug>

#include "task.h"
#include "tasklistmodel.h"


class TaskListView : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TaskListModel *taskData READ getTaskData WRITE setTaskData NOTIFY taskDataChanged)
    Q_PROPERTY(bool completedFilter READ getCompletedFilter WRITE setCompletedFilter NOTIFY completedFilterChanged)
    Q_PROPERTY(bool filterByCategory READ getFilterByCategory WRITE setFilterByCategory NOTIFY filterByCategoryChanged)
    Q_PROPERTY(QString filter READ getFilter WRITE setFilter NOTIFY filterChanged)
public:
    explicit TaskListView(QObject *parent=nullptr);

    // Note list
    enum TaskRoles {
        NameRole = Qt::UserRole + 1,
        DoneRole,
        TaskIdRole,
        CategoryRole
    };

    virtual int rowCount(const QModelIndex&) const { return m_index.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    TaskListModel * getTaskData() const{return m_model;}
    bool getCompletedFilter() const {return m_completedFilter;}
    bool getFilterByCategory() const {return m_filterByCategory;}

    QString getFilter() const {return m_filter;}
signals:
    void taskDataChanged();
    void completedFilterChanged();
    void filterByCategoryChanged();
    void filterChanged();
private slots:
    void changeData();
    void updateView();
private:
    bool m_completedFilter;
    bool m_filterByCategory;

    QList<int> m_index;
    QString m_filter;

    TaskListModel * m_model;

    void setTaskData(TaskListModel * m);
    void setCompletedFilter(bool completedFilter);
    void setFilterByCategory(bool filterByCategory);
    void setFilter(QString filter);

    bool filter(Task & task);
};

#endif // TASKLISTVIEW_H
