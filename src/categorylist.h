#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QString>

#include "tasklistmodel.h"

class CategoryList: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TaskListModel *taskData READ getTaskData WRITE setTaskData NOTIFY taskDataChanged)
public:
    explicit CategoryList(QObject * parent = nullptr);

    enum CategoryRoles{
        NameRole = Qt::UserRole + 1,
        AllCountRole,
        ComplitedCountRole,
    };

    virtual int rowCount(const QModelIndex&) const { return m_categories.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    TaskListModel * getTaskData() {return m_tasks;}

    Q_INVOKABLE void addCategory(QString category);
signals:
    void taskDataChanged();
    void categoryAdded();
private slots:
    void changeData();
    void updateView(){
        beginResetModel();
        endResetModel();
    }
private:
    QList<QString> m_categories;
    QList<QString> m_tempCategories;
    TaskListModel * m_tasks;

    void setTaskData(TaskListModel * tasks);
};

#endif // CATEGORYLIST_H
