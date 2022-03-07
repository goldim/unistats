import QtQuick 2.0

Rectangle {
    id : it
    color: "white"
    width: 50
    height: 50

    Text {
        id : textVal;
        anchors.centerIn: parent
        text : "0"
    }

    function setValue(value){
        textVal.text = value;
    }
}
