import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

SplitView {
    id: panels
    anchors.fill: parent

    SplitView {
        id: leftPanels
        orientation: Qt.Vertical
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6

        ColumnLayout {
            SplitView.preferredHeight: parent.height / 2
            SplitView.minimumHeight: parent.height / 4

            Label {
                id: entityLabel
                text: qsTr("DDS ENTITIES")
                font.pixelSize: 15
                font.bold: true
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 5
            }

            EntityList {
                id: entityList
                anchors.top: entityLabel.bottom
                anchors.left: parent.left
                anchors.margins: 5
            }
        }

        ColumnLayout {
            SplitView.fillHeight: true
            SplitView.minimumHeight: parent.height / 4

            TabBar {
                id: physicalViewTabBar
                Layout.fillWidth: true
                Layout.alignment: parent.top | parent.left

                TabButton {
                    text: "Physical List"
                }

                TabButton {
                    text: "Logical List"
                }
            }

            StackLayout {
                currentIndex: physicalViewTabBar.currentIndex

                PhysicalView {
                    id: physicalView
                    anchors.top: entityLabel.bottom
                    anchors.left: parent.left
                    anchors.margins: 5
                }

                LogicalView {
                    id: logicalView
                    anchors.top: entityLabel.bottom
                    anchors.left: parent.left
                    anchors.margins: 5
                }
            }
        }
    }


    ColumnLayout {
        id: chartsLayout
        SplitView.fillWidth: true
    }

    ColumnLayout {
        id: rightColumnLayout
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6

        TabBar {
            id: settingsViewTabBar
            Layout.fillWidth: true

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

    function createChart(dataKind){
        var chartBox = Qt.createComponent("StatisticsChartBox.qml")

        if (chartBox.status === Component.Ready) {
            chartBox.createObject(chartsLayout, {"chartTitle": dataKind})
        }
    }
}

