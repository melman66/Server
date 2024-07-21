import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import "ServerFuncs.js" as Funcs

Rectangle {
    id: list_view_clients_main_rect

    color: "#FED7A8"
    radius: 10

    ListModel{
        id: clients_list_model
    }

    Component {
        id: delegate_list_view_clients

        Item {
            id: delegate_item
            width: delegate_text_messages.width + 5
            height: delegate_text_messages.height + 5

            LabelsTextForDelegate{
                id: delegate_text_messages
                width: 140
                delegate_text.text: modelData
            }
        }
    }

    Flickable {
        Layout.margins: 10
        anchors.fill: list_view_clients_main_rect
        ListViewTemplate{
            id: list_view_clients
            model: clients_list_model
            delegate: delegate_list_view_clients
            anchors.fill: parent
        }
    }

    Component.onCompleted: {
        server_view.clientName.connect(Funcs.addClientToList)
        server_view.removeClientFromList.connect(Funcs.removeClientFromList)

    }
}
