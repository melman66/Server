import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Window
import "ServerFuncs.js" as Funcs

Rectangle {
    id: list_view_messages_main_rect
    color: "#FED7A8"
    radius: 10

    ListModel {
        id: server_list_model_messages
        ListElement{
            message: "Welcome to server!"
        }
    }

    Component {
        id: delegate_list_view_messages

        Item {
            id: delegate_item
            width: delegate_text_messages.width + 5
            height: delegate_text_messages.height + 5
            focus: true

            LabelsTextForDelegate{                
                id: delegate_text_messages
                delegate_text.text: modelData
            }
        }
    }

    ListView{
        id: list_view_messages
        model: server_list_model_messages
        delegate: delegate_list_view_messages
        width: parent.width
        height: parent.height - 5

        clip: true
        ScrollBar.vertical: ScrollBar{ id: scroll_messages }
        onCountChanged: { scroll_messages.position = contentHeight }
    }

    Component.onCompleted: {
        server_view.messageSended.connect(Funcs.addMessageToList)
        server_view.readFromClient.connect(Funcs.addMessageToList)
        server_view.clientName.connect(Funcs.addMsgNewClient)
        server_view.removeClientFromList.connect(Funcs.removeMsgClient)
        server_view.errorServer.connect(Funcs.addMessageToList)
    }
}
