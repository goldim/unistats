import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

Window {
    id : win
    visible: false
    width: 300
    height: width / 2
    title: qsTr("О программе")
    modality: Qt.WindowModal

    Rectangle {
        anchors.fill: parent
        antialiasing: true

        Image {
            id: logo
            source: "appicon.png"
            anchors {
                left : parent.left
                top: parent.top
                bottom: parent.bottom
                right: parent.horizontalCenter
            }
        }

        Label {
            anchors {
                left : parent.horizontalCenter
                top: parent.top
                bottom: parent.bottom
                right: parent.right
            }
            wrapMode: "Wrap"
            text : "Программа разработа для использования в математических расчетах статистики университета.\n Разработчик: Золотов Д.Ю."
        }
    }

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }
}
