import QtQuick 2.0
import Sailfish.Silica 1.0
import ".."
import ToDoApp 1.0

Page {
    id: page

    property string filter: ""
    property bool filterByCategory: false
    property string headerTitle: ""

    TaskListView{
        id: nonCompletedList
        taskData: taskListModel
        completedFilter: false

        filterByCategory: page.filterByCategory
        filter: page.filter

        onTaskDataChanged: {
            console.log(nonCompletedList.taskData);
        }
    }

    Component{
        id: taskViewDelegate

        BackgroundItem{
            width: parent.width
            height: 80
            Label{
                anchors{
                    left: parent.left
                    right: parent.right
                    fill: parent
                    leftMargin: Theme.horizontalPageMargin
                    verticalCenter: parent.verticalCenter
                }

                text: model.name
                color: (model.completed) ? Theme.highlightColor : Theme.primaryColor
            }

            onClicked: {
                //console.log(viewAll.host);

                var task = pageStack.push(Qt.resolvedUrl("TaskViewPage.qml"), {
                               taskid: model.taskid,
                               name: model.name,
                               category: model.category
                               });
            }
        }
    }


    SilicaListView{
        id: view
        anchors.fill: parent
        contentHeight: contentHeight

        header: PageHeader{
            title: page.headerTitle
        }

        PullDownMenu {
            id: menu
            MenuItem {
                id: addTaskMenuItem
                text: qsTr("Add task")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/TaskEditorDialog.qml"), {
                                                acceptText: qsTr("Create"),
                                                title: qsTr("New Task"),
                                                category: page.filter,
                                                categoriesModel: categoryList
                                                });
                    dialog.accepted.connect(function(){
                        taskListModel.addTask(dialog.name, dialog.category);
                    });
                }
            }

            MenuItem{
                id: viewCompletedTaskMenuItem
                text: qsTr("View completed task")
                onClicked: pageStack.push(Qt.resolvedUrl("TaskListCompletedPage.qml"), {
                                          filterByCategory: nonCompletedList.filterByCategory,
                                          filter: nonCompletedList.filter,
                                          pageHeader: qsTr("Completed tasks")
                                          });
            }
        }

        model: nonCompletedList
        delegate: taskViewDelegate

        VerticalScrollDecorator {}
    }
}
