#include "tasksublist.h"

#include "tasklist.h"
#include <QVariant>
#include "datastorer.h"
#include <QDebug>

TaskSubList::TaskSubList(TaskList * tasklist,QObject* parent) : parentList(tasklist), QAbstractListModel(parent), m_notes()
{

}

QHash<int, QByteArray> TaskSubList::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TextRole] = "text";
    roles[DoneRole] = "completed";
    return roles;
}

QVariant TaskSubList::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant();
    switch(role) {
    case NameRole:
        return QVariant(m_notes[index.row()]->name);
    case TextRole:
        return QVariant(m_notes[index.row()]->note);
    case DoneRole:
        return QVariant(m_notes[index.row()]->isDone);
    default:
        return QVariant();
    }
}

void TaskSubList::addNote(QString name, QString text, bool isDone) {
    //auto notesSize = m_notes.size();
    //beginInsertRows(QModelIndex(), notesSize, notesSize);
    parentList->addNote(name, text, isDone);
    //обновить TaskSubList

    //endInsertRows();
}
bool TaskSubList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "set Data";
    if (!index.isValid()) {
        qDebug() << "index invalid";
        return false;
    }

    switch (role) {
    case NameRole:
        qDebug() << "Name Role";
        m_notes[index.row()]->name = value.toString();
        qDebug() << m_notes[index.row()]->name << " <= " << value.toString();
        break;
    case TextRole:
        qDebug() << "Text role";
        m_notes[index.row()]->note = value.toString();
        qDebug() << m_notes[index.row()]->note;
        break;
    case DoneRole:
        qDebug() << "IsDone Role";
        m_notes[index.row()]->isDone = value.toBool();
        qDebug() << m_notes[index.row()]->isDone << " <= " << value.toBool();
        break;
    default:
        return false;
    }

    //Обновить родительский список emit parentList->dataChanged();
    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

