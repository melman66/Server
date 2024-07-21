import QtQuick
import QtQuick.Controls.Basic
import "../"

Rectangle{
    id: server_text_port_rect

    property alias server_string_port: server_text_port.text
    property alias server_port_isAccepted: server_text_port.acceptableInput

    width: 100
    height: 30
    radius: 10
    color: serverIsStarted ? "#B9A583" : "#ffe4b5"
    InputText {
        id: server_text_port
        anchors.fill: parent
        text: "49152"
        enabled: serverIsStarted ? false : true
        color: serverIsStarted ? "#716551" : "#2e1300"
           && acceptableInput  ? "#2e1300" : "#ff1300"

        validator: IntValidator {
            top: 65535
            bottom: 49152
        }

        onAccepted: {
            button_start_server.checked = true
        }
    }
}
