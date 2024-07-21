import QtQuick
import QtQuick.Layouts

Rectangle{

    property alias delegate_text: delegate_text
    x: 5
    y: 5

    width: delegate_text.width
    height: delegate_text.height

    color: "#FD9583"
    radius: 5
    LabelsText{
        id: delegate_text
        font.pointSize: 10
        padding: 5
        horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        width: 400
        height: contentHeight + 10
        clip: true
    }
}
