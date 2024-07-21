import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Button{
    checkable: true
    hoverEnabled: false

    property alias grad_start_pos_: grad_start_pos
    property alias grad_stop_pos_: grad_stop_pos

    Layout.preferredWidth: 100
    Layout.preferredHeight: 30

    background: Rectangle{
        width: parent.width
        height: parent.height
        anchors.fill: parent
        radius: 10
        gradient: Gradient {
            GradientStop {
                id: grad_start_pos
                position: checked ? 1 : 0
                color:  "#FFD8B5"
            }

            GradientStop {
                id: grad_stop_pos
                position: checked ? 0 : 1
                color: "#e16b44"
            }
            orientation: Gradient.Vertical
        }
    }
}

