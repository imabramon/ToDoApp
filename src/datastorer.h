#ifndef DATASTORER_H
#define DATASTORER_H


#include <QList>
#include <QString>
#include "task.h"

namespace DataStorer {
    QList<Task> readData();
    void storeData(QList<Task> &notes);
};

#endif // DATASTORER_H
