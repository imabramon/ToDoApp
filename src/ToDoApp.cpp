#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "tasklistmodel.h"
#include "tasklistview.h"
#include "categorylist.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<TaskListModel>("ToDoApp", 1, 0, "TaskListModel");
    qmlRegisterType<TaskListView>("ToDoApp", 1, 0, "TaskListView");
    qmlRegisterType<CategoryList>("ToDoApp", 1, 0, "CategoryList");

    return SailfishApp::main(argc, argv);
}
