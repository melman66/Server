
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import "ServerFuncs.js" as Funcs

ButtonTemplate {
    id: button_start_server

    onCheckedChanged: {
        if (!Funcs.startServer()){
            checked = false;
        }
    }

    LabelsText {
        id: button_server_text
        anchors.fill: parent
        text: checked ? "stop" : "start"
    }

    states: [
        State {
            name: "disable"

            when: server_input_text_port.server_port_isAccepted == false

            PropertyChanges {
                target: button_start_server
                enabled: false
            }
            PropertyChanges {
                target: grad_start_pos_
                color: "#B4B2B3"
            }
            PropertyChanges {
                target: grad_stop_pos_
                color: "#696868"
            }
        }
    ]

}

