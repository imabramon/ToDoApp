#include "task.h"

Task::Task(int id, QString name, QString category, bool isDone)
{
    this->id = id;
    this->name = name;
    this->category = category;
    this->isDone = isDone;
}
