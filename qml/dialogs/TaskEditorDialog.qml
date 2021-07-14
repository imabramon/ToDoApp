import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: root

    property string name: ""
    property string acceptText: ""
    property string title: ""
    property string category: ""

    property alias categoriesModel: categories.model



    onCategoryChanged:  {
        console.log("Category Changed")
        console.log(root.category);
        if(root.category !== ""){
             categoryMenu.value = root.category;
        }
    }

    Component{
        id: categoriesDelegate

        MenuItem{
            text: model.name
            onClicked: {
                console.log("MenuItem with name " + model.name + " is clicked");
                root.category = model.name
            }
        }
    }

    DialogHeader{
        id: editorHeader
        acceptText: root.acceptText
        title: root.title
    }

    Column{
        id:content

        anchors{
            top: editorHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }

        spacing: Theme.paddingMedium

        Label{
            id: taskNameHeaderLabel
            text: qsTr("Task name: ")
            font.pixelSize: Theme.fontSizeSmall
        }

        TextField{
            id: taskNameField

            width: parent.width
            text: root.name
            placeholderText: qsTr("Task name")
        }

        ComboBox{
            id: categoryMenu
            label: qsTr("Category")
            menu: ContextMenu{
                Repeater{
                    id: categories
                    delegate: categoriesDelegate
                }
            }


        }

    }





    onAccepted: {
        console.log("AcceptText is \"" + root.acceptText + "\"")
        console.log("Title is \"" + root.title + "\"")
        root.name = taskNameField.text
        root.category = categoryMenu.value;
        console.log(categoryMenu.currentItem.text);
    }
}
