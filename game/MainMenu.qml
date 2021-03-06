import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12


Item {

    id: root
    anchors.centerIn: parent
    width: parent.width
    height: parent.height

    Rectangle {
        id:rect

        anchors.fill: parent
        color: "white"
        opacity: 1
    }

    Column {
        id: column
        anchors.centerIn: rect
        width: rect.width * 0.8
        spacing: 5
        opacity: 0.9

        Button {
            id: singlePlayerButton
            Layout.alignment: Qt.AlignCenter
            text: "Singleplayer"
            font.pointSize: root.width / 15
            width: parent.width
            onClicked: {
                Game.singlePlayer()
                singleplayerMenu.visible = true
                mainMenu.visible = false
            }

            Keys.onPressed: {
                Game.keyEvent(event.key)
            }
        }

        Button {
            id: exitButton
            Layout.alignment: Qt.AlignCenter
            text: "Exit"
            font.pointSize: root.width / 15
            width: parent.width
            onClicked: Qt.quit()
        }
    }
}
