import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window

Window {
    id: root
    width: 1280
    height: 720
    minimumWidth: 720
    minimumHeight: 800
    visible: true
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowMinMaxButtonsHint

    property string buttonsColor: "#BB86FC"
    property string backgroundColor: "#121212"
    property string panelColor: "#1F1B24"
    property string borderColor: "#292929"
    property string textColor: "#E0E0E0"
    property string hoverColor: "#3700B3"

    Action {
        id: closeHotKey
        text: "&Open"
        shortcut: "Ctrl+Q"
        onTriggered: root.close()
    }

    ToolButton { action: closeHotKey }

    Rectangle {
        id: visibleWindow
        width: root.width
        height: root.height
        radius: 10
        color: root.backgroundColor
        border.color: root.borderColor
        border.width: 1
    }

    // Верхняя кастомная панель
    Rectangle {
        id: title
        x: (root.width - width) / 2
        y: 0
        width: root.width
        height: 70
        radius: 10
        color: root.panelColor
        border.color: root.borderColor
        border.width: 1

        MouseArea {
            id: dragArea
            anchors.fill: parent
            property real dragStartX
            property real dragStartY

            onPressed: (mouse) => {
                dragStartX = mouse.x
                dragStartY = mouse.y
            }

            onPositionChanged: (mouse) => {
                var dx = mouse.x - dragStartX
                var dy = mouse.y - dragStartY
                root.x += dx
                root.y += dy
            }
        }

        Item {
            id: titleRowLike
            anchors.fill: parent

            Text {
                text: "WBase27"
                color: root.textColor
                font.family: "Noto Sans"
                font.pointSize: 15
                font.bold: true
                anchors.centerIn: titleRowLike
            }

            Row {
                spacing: 4
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: titleRowLike.verticalCenter

                // Кнопка "Свернуть"
                Item {
                    id: minimizeButton
                    width: 30
                    height: 30

                    Rectangle {
                        id: minimizeButtonRect
                        anchors.verticalCenter: minimizeButton.verticalCenter
                        width: minimizeButton.width * 0.8
                        height: 3
                        color: root.buttonsColor

                    }
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: root.lower()
                        onEntered: minimizeButtonRect.color = root.hoverColor
                        onExited: minimizeButtonRect.color = root.buttonsColor
                    }
                }

                // Кнопка "Максимизировать/Свернуть"
                Item {
                    id: maxScaleButton
                    width: 30
                    height: 30
                    property bool isFullscreen: false

                    Image {
                        id: fullScreenStat
                        visible: maxScaleButton.isFullscreen
                        source: "qrc:/fullscreen.svg"
                        anchors.centerIn: parent
                    }

                    Image {
                        id: defaultScreenStat
                        visible: !maxScaleButton.isFullscreen
                        source: "qrc:/fullscreen_exit.svg"
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        hoverEnabled: true
                        anchors.fill: maxScaleButton

                        onClicked: {
                            if (!maxScaleButton.isFullscreen) {
                                root.visibility = Window.FullScreen;
                                maxScaleButton.isFullscreen = true;
                            } else {
                                root.visibility = Window.Windowed;
                                maxScaleButton.isFullscreen = false;
                            }
                        }
                    }
                }

                // Кнопка "Закрыть"
                Item {
                    id: closeButton
                    width: 30
                    height: 30

                    Image {
                        source: "qrc:/close.svg"
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: root.close()
                    }
                }
            }
        }
    }

    Item {
        id: workAreaLimiter
        width: visibleWindow.width
        height: visibleWindow.height - title.height
        anchors.top: title.bottom
    WorkAreaRow {
        id: workArea
        width: parent.width
        height: 40
        spacing: 10
        anchors.margins: 15
        }
    }
}
