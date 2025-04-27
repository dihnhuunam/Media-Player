import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 1024
    height: 600
    minimumWidth: 800
    minimumHeight: 500
    visible: true
    title: "Media Player"

    StackView {
        id: stackView
        anchors.fill: parent
        Layout.fillWidth: true
        Layout.fillHeight: true
        initialItem: "qrc:/Source/View/LoginView.qml"
    }
}
