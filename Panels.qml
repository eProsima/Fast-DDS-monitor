import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Item {
    id: item1
    width: 1600
    height: 900

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        anchors.margins: 5

        rows: 2
        columns: 3

        RowLayout {
            id: rowLayout

            RowLayout {

                id: domainIdLayout

                Text {
                    id: domainIdText
                    text: qsTr("Domain ID")
                    font.pixelSize: 12
                }

                SpinBox {
                    value: 0
                }
            }
        }

        ColumnLayout {
            id: columnLayout

            Layout.row:1
            Layout.column: 0

            TabBar {
                id: logicalViewTabBar

                TabButton {
                    text: "Entity List"
                }

                TabButton {
                    text: "Topic List"
                }
            }

            StackLayout {
                currentIndex: logicalViewTabBar.currentIndex

                EntityList {}

            }

            TabBar {
                id: physicalViewTabBar

                TabButton {
                    text: "Physical List"
                }
            }

            StackLayout {
                currentIndex: physicalViewTabBar.currentIndex

                PhysicalView {}

            }
        }
    }
}
