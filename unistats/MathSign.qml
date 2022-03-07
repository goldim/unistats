import QtQuick 2.0

Rectangle {
    id : it
    color: "white"
    width: 50
    height: 50

    property string title
    property string tooltip

    Text {
        anchors.centerIn: parent
        text : it.title
    }
}
