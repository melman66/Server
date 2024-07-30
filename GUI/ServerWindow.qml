import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Server
import "ServerFuncs.js" as Funcs

ApplicationWindow {
    id: server_window

    property bool serverIsStarted: server_view.stateServerStarted
    property bool error_flag: false
    property string selectedClient: ""

    visible: true
    minimumHeight: 400
    minimumWidth: 600
    maximumHeight: 400
    maximumWidth: 600
    title: "Server"
    x:100
    y: 100

    ServerView{ id: server_view }

    Rectangle{
        color: "#febc6b"
        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent

            TopItem {
                id: top_item

                Layout.margins: 10
                Layout.fillWidth: true
                Layout.preferredHeight: 30
            }

            BottomItem {
                id: bottom_item

                Layout.margins: 10
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
    Component.onCompleted: {
        server_view.stateServerStartedChanged.connect(Funcs.changeServerState)
        server_view.errorServer.connect(Funcs.setErrorFlag)
    }
}
