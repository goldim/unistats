import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4

Item {
    id : it
    signal addMsg(string text)
    signal clear
    signal save

    onAddMsg : conSpace.addMsg(text)
    onClear: conSpace.clear()
    onSave: conSpace.save()

    Rectangle{
        id: conToolBar
        anchors.top : parent.top
        anchors.left : parent.left
        anchors.right : parent.right
        height: 25
        color: "#404244"
        Row
        {
            anchors.fill: parent
            leftPadding: 20

            Text{
                anchors.verticalCenter: parent.verticalCenter
                id: conLbl
                color: "white"
                text: qsTr("Вывод приложения   ")
            }

            ToolButton {
                anchors {
                    top : parent.top
                    bottom : parent.bottom
                }
                iconSource : "images/clean.png"
                onClicked: it.clear();
            }
            ToolButton {
                anchors {
                    top : parent.top
                    bottom : parent.bottom
                }
                iconSource : "images/save.png"
                onClicked: it.save();
            }
        }
    }

    Rectangle {
        id : conSpace

        signal addMsg(string text)
        signal clear
        signal save

        onClear: {
            conText.text = "";
        }

        onSave: {
            _controller.save(conText.text);
        }

        onAddMsg: {
            conText.text = text + "\n" + conText.text;
        }

        anchors {
            top : conToolBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        TextArea {
            id : conText
            anchors.fill: parent
            text: qsTr("")
            textFormat: TextEdit.RichText
            font.pixelSize: 12
            wrapMode: TextEdit.Wrap
        }
    }
}
