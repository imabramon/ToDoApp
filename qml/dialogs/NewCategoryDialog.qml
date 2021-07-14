import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog{
    id: root

    property string categoryName: ""

    DialogHeader{
        id: dialogHeader
        acceptText: qsTr("Create")
        title: qsTr("New category")
    }

    Column{
        id:content

        anchors{
            top: dialogHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }

        spacing: Theme.paddingMedium

        Label{
            id: categoryNameHeaderLabel
            text: qsTr("Category name: ")
            font.pixelSize: Theme.fontSizeSmall
        }

        TextField{
            id: categoryNameField

            width: parent.width
            placeholderText: qsTr("Category name")
        }
    }

    onAccepted: {
        root.categoryName = categoryNameField.text
    }
}
