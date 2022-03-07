import QtQuick 2.0
import QtQuick.Controls 1.4

Button {
    id: button

    signal pressAndHold()

    Timer {
        id: longPressTimer

        interval: 2000 //your press-and-hold interval here
        repeat: false
        running: false

        onTriggered: {
            button.pressAndHold()
        }
    }


    onPressedChanged: {
        if ( pressed ) {
            longPressTimer.running = true;
        } else {
            longPressTimer.running = false;
        }
    }
}
