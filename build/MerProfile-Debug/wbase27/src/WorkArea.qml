import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.wbase27

GridLayout {
    columns: 3  // Определяем 2 колонки

    Rectangle {
        id: goToSettings
        Layout.row: 1
        Layout.column: 0
        width: root.width * 0.2
        height: root.width * 0.2
        radius: 20
        color: root.panelColor
        Image {
            anchors.centerIn: parent
            width: parent.width * 0.4
            height: parent.height * 0.4
            source: "qrc:/settings.png"
        }
    }


    Column {
        id: timeOptions
        Layout.row: 1
        Layout.column: 1
        spacing: 20
        Layout.alignment: Qt.AlignTop

        Label {
            text: "Set Standby Interval (ms):"
            color: root.textColor
        }

        SpinBox {
            id: intervalInput
            from: 10000
            to: 3600000
            stepSize: 30000
            value: standby.interval
            onValueChanged: standby.interval = value
        }

        Row {
            spacing: 10

            Button {
                text: "Start Standby"
                onClicked: standby.startStandbyTimer()
            }

            Button {
                text: "Stop Standby"
                onClicked: standby.stopStandbyTimer()
            }
        }

        Row {
            spacing: 10

            Button {
                text: "Save Settings"
                onClicked: standby.saveSettings("standby_settings.json")
            }

            Button {
                text: "Load Settings"
                onClicked: standby.loadSettings("standby_settings.json")
            }
        }
    }

    StandbyManager {
        id: standby
    }
}
