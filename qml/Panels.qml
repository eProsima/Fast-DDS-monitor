import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Item {
    id: item1
    GridLayout {
        id: gridLayout
        anchors.fill: parent
        anchors.margins: 5

        rows: 3
        columns: 3

        RowLayout {
            id: rowLayout

            Layout.row:0
            Layout.column: 0
            Layout.columnSpan: 3

            Button {
                text: "Init new monitor"
                onClicked: dialogInitMonitor.open()
            }
        }

        ColumnLayout {
            id: columnLayout

            Layout.row:1
            Layout.column: 0

            Text {
                id: entityLabel
                text: qsTr("DDS ENTITIES")
                font.pixelSize: 15
                font.bold: true
            }

            ColumnLayout {
                EntityList {}
            }

        }

        ColumnLayout {
            id: columnLayoutContainer

            Layout.row:2
            Layout.column: 0

            TabBar {
                id: physicalViewTabBar

                TabButton {
                    text: "Physical List"
                }

                TabButton {
                    text: "Logical List"
                }
            }

            StackLayout {
                currentIndex: physicalViewTabBar.currentIndex

                PhysicalView {}

                LogicalView {}
            }
        }

        Rectangle {
            Layout.row:1
            Layout.rowSpan: 2
            Layout.column: 1
            width: parent.width / 5 * 3
            height: parent.height / 5 * 4
            color: "grey"
        }

        ColumnLayout {
            id: rightColumnLayout

            Layout.row: 1
            Layout.rowSpan: 2
            Layout.column: 2

            TabBar {
                id: settingsViewTabBar

                TabButton {
                    text: "QoS"
                }

                TabButton {
                    text: "Statistics"
                }
                TabButton {
                    text: "Issues"
                }
            }

            StackLayout {
                currentIndex: settingsViewTabBar.currentIndex

                QosView {}

                SummaryView {}

            }

        }
    }
}
