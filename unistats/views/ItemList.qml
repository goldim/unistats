import QtQuick 2.0

import "../models" as Models

Rectangle {
    color : "gray"
    Component {
        id : delegate
        Item {
            width : parent.width
            height : 70
            Row {
                anchors.verticalCenter: parent.verticalCenter
                Column {
                    Text {color : "black"; text: name; font.pointSize: 12}
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
//        focus : true
        highlight : Rectangle {
            width : parent.width
            color : "blue"
        }

        model : Models.Years{}
        delegate: delegate
    }
}


