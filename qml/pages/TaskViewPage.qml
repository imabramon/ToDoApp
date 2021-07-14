import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: root

    property alias name: taskNameLabel.text
    property alias category: taskCategoryLabel.text

    property int taskid: 0

    SilicaFlickable{
        anchors.fill: parent
        contentHeight: content.height

        PullDownMenu{
            MenuItem{
                text: qsTr("Complete task")
                onClicked: {
                    //taskCompleted();
                    console.log(taskListModel);
                    taskListModel.setCompleted(taskid, true);
                    pageStack.pop();
                }
            }

            MenuItem{

                text: qsTr("Edit task")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/TaskEditorDialog.qml"), {
                                                acceptText: qsTr("Confirm"),
                                                title: qsTr("Edit Task"),
                                                name: taskNameLabel.text,
                                                category: taskCategoryLabel.text,
                                                categoriesModel: categoryList
                                                });

                    dialog.accepted.connect(function(){
                        taskListModel.setName(root.taskid, dialog.name);
                        taskListModel.setCategory(root.taskid, dialog.category);

                        taskNameLabel.text = dialog.name;
                        taskCategoryLabel.text = dialog.category;
                    });
                }
            }

            MenuItem{
                id: deleteTaskMenuItem
                text: qsTr("Delete task")
                onClicked: {
                    //taskDeleted();
                    taskListModel.delTask(taskid)
                    pageStack.pop();
                }
            }
        }

        Column{
            id:content

            anchors{
                left: parent.left
                right: parent.right
                leftMargin: Theme.horizontalPageMargin
                rightMargin: Theme.horizontalPageMargin
            }

            spacing: Theme.paddingMedium

            PageHeader{
                id: pageHeader
                title: qsTr("Task info")
            }

            Label{
                id: taskNameHeaderLabel
                text: qsTr("Task name: ")
                font.pixelSize: Theme.fontSizeSmall
            }

            Label{
                id: taskNameLabel
                color: Theme.highlightColor
            }

            Label{
                id: taskCategoryHeaderLabel
                text: qsTr("Category: ")
                font.pixelSize: Theme.fontSizeSmall
            }

            Label{
                id: taskCategoryLabel
                color: Theme.highlightColor
            }
        }
    }

}
