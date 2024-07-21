import QtQuick
import QtQuick.Controls.Basic

TextInput{
    color: "#2e1300"
    verticalAlignment: Text.AlignVCenter
    selectByMouse: true
    mouseSelectionMode: TextInput.SelectCharacters
    selectedTextColor: "#930000"
    selectionColor: "#fdff01"
    font.pointSize: 12
    font.family: "Verdana"
    leftPadding: 10
    rightPadding: 10
    clip: true
    maximumLength: 30
}
