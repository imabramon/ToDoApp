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
                text: qsTr("Delete task")
                onClicked: {
                    taskListModel.del(taskid);
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
