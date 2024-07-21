import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
    RowLayout {
        width: parent.width
        height: 30
        spacing: 10

        //input text port number
        LabelsText{text: "Port"}
        InputTextPortServer {
            id: server_input_text_port
        }

        //button start server
        ButtonServerStart{
            id: button_start_server
        }

        //filler item
        Item{
            Layout.fillWidth: true
        }

        //light connected
        LightConnected{
            id: server_light_connected
            lightIsConnected: serverIsStarted  ? 1 : 0

        }
    }
}
