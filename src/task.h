#ifndef TASK_H
#define TASK_H

#include <QString>

struct Task
{
    Task(int id, QString name, QString category, bool isDone);
    int id;
    QString name;
    QString category;
    bool isDone;
};

#endif // TASK_H
