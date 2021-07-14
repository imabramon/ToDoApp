import QtQuick 2.0
import Sailfish.Silica 1.0
import ".."
import ToDoApp 1.0

Page {
    id: page

    Component{
        id: categoryViewDelegate

        BackgroundItem{
            //property double completedTasks: 5
            //property double allTasks: 10
            //anchors.bottomMargin: 100

            width: parent.width
            Column{
                anchors.fill: parent

                Label{
                    anchors{
                        left: parent.left
                        right: parent.right
                        //fill: parent
                        leftMargin: Theme.horizontalPageMargin
                        topMargin: 20;
                        //verticalCenter: parent.verticalCenter
                    }

                    text: model.name + ((model.allCount !== 0) ? (" (" + model.completedCount + "/" + model.allCount + ")") : "")

                }

                ProgressBar{
                    id: progressBar
                    width: parent.width
                    value: model.completedCount
                    maximumValue: model.allCount

                    indeterminate: model.allCount === 0


                }
            }


            onClicked: {
                console.log("Choose category")
                pageStack.push(Qt.resolvedUrl("TaskListNonCompletedPage.qml"), {
                                filter: model.name,
                                filterByCategory: true,
                                headerTitle: model.name
                               });

            }
        }
    }


    SilicaListView{
        anchors.fill: parent
        contentHeight: contentHeight

        header: PageHeader{
            title: qsTr("Categories")
        }

        PullDownMenu {
            id: menu
            MenuItem {
                id: addCategoryMenuItem
                text: qsTr("Add category")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/NewCategoryDialog.qml"));

                    dialog.accepted.connect(function(){
                        console.log("add new category nemed " + dialog.categoryName);
                        categoryList.addCategory(dialog.categoryName);
                    });
                }
            }
            MenuItem{
                id: viewAllMenuItem
                text: qsTr("View All")
                onClicked:{
                    pageStack.push(Qt.resolvedUrl("TaskListAllNonCompletedPage.qml"), {
                                    filterByCategory: false
                                   });
                }
            }
        }

        model: categoryList
        delegate: categoryViewDelegate
        spacing: 20

        VerticalScrollDecorator {}
    }
}

