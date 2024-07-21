import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Button{
    id: button_send_message
    checkable: true
    hoverEnabled: false

    Layout.preferredWidth: 100
    Layout.preferredHeight: 70

    property alias grad_start_pos: grad_start_pos
    property alias grad_stop_pos:  grad_stop_pos

    LabelsText{
        text: "send"
        anchors.fill: parent
    }

    background: Rectangle{
        id: button_send_rect
        width: parent.width
        height: parent.height
        anchors.fill: parent
        radius: 10
        gradient: Gradient {
            GradientStop {
                id: grad_start_pos
                position: button_send_message.down ? 1 : 0
                color: "#FFD8B5"
            }

            GradientStop {
                id: grad_stop_pos
                position: button_send_message.down ? 0 : 1
                color: "#e16b44"
            }
            orientation: Gradient.Vertical
        }
    }
}



