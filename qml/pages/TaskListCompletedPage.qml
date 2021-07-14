import QtQuick 2.0
import Sailfish.Silica 1.0
import ".."
import ToDoApp 1.0

Page {
    id: page

    property alias filterByCategory: completedList.filterByCategory
    property alias filter: completedList.filter
    property string headerTitle : ""

    TaskListView{
        id: completedList
        taskData: taskListModel
        completedFilter: true
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

                                var task = pageStack.push(Qt.resolvedUrl("TaskViewCompletedPage.qml"), {
                                               taskid: model.taskid,
                                               name: model.name,
                                               category: model.category
                                               });
                            }
                         }
    }

    SilicaListView{
        anchors.fill: parent
        contentHeight: contentHeight

        header: PageHeader{
            title: page.headerTitle
        }

        model: completedList
        delegate: taskViewDelegate

        VerticalScrollDecorator {}
    }


}
