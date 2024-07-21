import QtQuick
import QtQuick.Controls.Basic

ScrollView{
    property alias input_message_text: input_message_text
    property alias input_message_rect: input_text_client_messages_main_rect

    TextArea {
        id: input_message_text

        background: Rectangle{
            id: input_text_client_messages_main_rect
            color: "#FED7A8"
            radius: 10
        }
        color: "#2e1300"
        font.family: "Verdana"
        font.pointSize: 12
        width: parent.width
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        textMargin: 10
        clip: true
        wrapMode: Text.WordWrap
        placeholderText: "Enter text..."

    }
}
