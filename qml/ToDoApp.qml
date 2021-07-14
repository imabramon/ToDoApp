import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

import ToDoApp 1.0

ApplicationWindow
{
    id: app
    initialPage: Component { CategoryListPage {}}
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    TaskListModel{
        id: taskListModel
    }

    /*
    ListModel{
        id: categoryList

        ListElement{name: "None"}
        ListElement{name: "Laba"}
        ListElement{name: "Kontest"}
        ListElement{name: "Practica"}
    }
    */

    CategoryList{
        id: categoryList
        taskData: taskListModel
    }

    Component.onCompleted:  taskListModel.readList()
    Component.onDestruction: taskListModel.storeList()
}
