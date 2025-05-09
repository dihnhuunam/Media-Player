import QtQuick
import QtQuick.Controls

Button {
    id: hoverButton

    property string imageSource: ""
    property real buttonWidth: 60
    property real buttonHeight: 60
    property real imageWidth: 30
    property real imageHeight: 30
    property color hoverColor: "#f0f0f0"
    property color defaultColor: "transparent"
    property real hoverScale: 1.05
    property real defaultScale: 1.0
    property int animationDuration: 150
    property bool showBorder: true
    property bool enableHover: true

    width: buttonWidth
    height: buttonHeight
    flat: true

    background: Rectangle {
        radius: width / 2
        color: enableHover && hoverButton.hovered ? hoverColor : defaultColor

        Behavior on color {
            ColorAnimation {
                duration: animationDuration
            }
        }
    }

    Image {
        anchors.centerIn: parent
        source: imageSource
        width: imageWidth
        height: imageHeight
        visible: imageSource !== ""
    }

    scale: (enableHover && hoverButton.hovered) ? hoverScale : defaultScale
    Behavior on scale {
        NumberAnimation {
            duration: animationDuration
        }
    }
}
