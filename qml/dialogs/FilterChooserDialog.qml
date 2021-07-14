import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: root

    property string category: ""

    property alias categoriesModel: categories.model

    DialogHeader{
        id: header
        acceptText: qsTr("Confirm")
        title: "Choose category"
    }

    onCategoryChanged:  {
        console.log("Category Changed")
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


    Column{
        id:content

        anchors{
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }

        spacing: Theme.paddingMedium

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
        root.category = categoryMenu.currentItem.text;
        console.log(categoryMenu.currentItem.text);
    }
}
