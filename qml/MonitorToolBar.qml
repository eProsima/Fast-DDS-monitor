import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

ToolBar {
    id: toolBar

    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: "Init new monitor"
            onClicked: {
                dialogInitMonitor.open()
            }
        }

        ToolSeparator {}

        ToolButton {
            text: "Display new data"
            onClicked: {
                dataKindDialog.open()
            }
        }

        ToolSeparator {}

        ToolButton {
            text: "Refresh"
            onClicked: {
                controller.refresh_click()
            }
        }

        ToolSeparator {}

        Item {
            Layout.fillWidth: true
        }
    }
}
