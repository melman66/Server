import QtQuick
import QtQuick.Controls.Basic

Rectangle {
    id: light_connected

    property bool lightIsConnected: false

    width: 160
    height: 30
    color: "#ff8177"
    radius: 100
    gradient: Gradient {
        GradientStop {
            id: light_connected_gradientStop
            position: 0
            color: "#ff8177"
        }
        GradientStop {
            id: light_connected_gradientStop1
            position: 1
            color: "#b12a5b"
        }
        orientation: Gradient.Vertical
    }
    LabelsText{
        id: light_connected_text
        anchors.fill: parent
        text: "disconnected"
    }

    states: [
        State {
            name: "State1"
            when: lightIsConnected == true

            PropertyChanges {
                target: light_connected_gradientStop
                color: "#7fff77"
            }

            PropertyChanges {
                target: light_connected_gradientStop1
                color: "#32b12a"
            }

            PropertyChanges {
                target: light_connected_text
                text: "connected"
            }
        }
    ]
}
