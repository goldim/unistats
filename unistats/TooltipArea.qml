import QtQuick 2.0

MouseArea {
    id: _root
    property string text: ""
    anchors.fill: parent
    hoverEnabled: _root.enabled
    onExited: Tooltip.hideText()

    onCanceled: Tooltip.hideText()
    onClicked: {
        if (typeof(_root.parent.pressed) !== 'undefined')
        _root.parent.pressed = !_root.parent.pressed
    }
    Timer {
        interval: 1000
        running: _root.enabled && _root.containsMouse && _root.text.length
        onTriggered: Tooltip.showText(_root, Qt.point(_root.mouseX, _root.mouseY), _root.text)
    }
}
