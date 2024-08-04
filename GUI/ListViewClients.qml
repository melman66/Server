import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Server
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
            height: delegate_text.height
            width: list_view_clients_main_rect.width

            LabelsText{
                id: delegate_text
                text: modelData
                height: contentHeight + 10
                x: 5
            }
            MouseArea {
                anchors.fill: delegate_item
                onPressed: { list_view_clients.currentIndex = index }
            }
        }
    }

    Flickable {
        Layout.margins: 10
        anchors.fill: list_view_clients_main_rect
        ListView{
            id: list_view_clients
            model: clients_list_model
            delegate: delegate_list_view_clients
            anchors.fill: parent
            clip: true
            focus: true

            ScrollBar.vertical: ScrollBar{}
            highlight:  Rectangle{
                radius: 5
                color: "#FD9583"
            }
            highlightMoveDuration: 100

            onHighlightItemChanged: {
                if (list_view_clients.count > 0) {
                    selectedClient = clients_list_model.get(list_view_clients.currentIndex).client
                }
            }
            onCurrentIndexChanged: {
                if (list_view_clients.count > 0) {
                    selectedClient = clients_list_model.get(list_view_clients.currentIndex).client
                }
            }
        }
    }

    Component.onCompleted: {
        server_view.clientName.connect(Funcs.addClientToList)
        server_view.removeClientFromList.connect(Funcs.removeClientFromList)
    }
}
