import QtQuick
import QtQuick.Layouts
import "ServerFuncs.js" as Funcs

Item{
    id: bottom_item

    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 10
        rowSpacing: 10

        //Messages list
        ListViewMessages{
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        //Clients list
        ListViewClients{
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 150
            Layout.fillHeight: true
        }

        //Text area for input message
        InputMessage {
            id: server_input_message
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            input_message_rect.color: serverIsStarted ? "#ffe4b5" : "#B9A583"
            enabled: serverIsStarted ? 1 : 0
            input_message_text.placeholderText:
                serverIsStarted ? "Enter text..." : ""
        }

        //Button send message
        ButtonSendMessage{
            id: button_send_message_to_server
            Layout.preferredWidth: 150
            Layout.preferredHeight: 70
            enabled: (serverIsStarted
                      && (server_input_message.input_message_text.text !== ""))
                      ? 1 : 0
            grad_start_pos.color: (serverIsStarted
                                  && (server_input_message.input_message_text.text !== ""))
                                  ? "#FFD8B5" : "#B4B2B3"
            grad_stop_pos.color:  (serverIsStarted
                                  && (server_input_message.input_message_text.text !== ""))
                                  ? "#e16b44" : "#696868"
            onClicked: Funcs.sendMsgToClient(server_input_message.input_message_text.text)
        }
    }
}
