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

        Rectangle{
            id: entityListBox
            SplitView.preferredHeight: parent.height / 2
            SplitView.minimumHeight: parent.height / 4

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {

                Rectangle {
                    id: entityLabel
                    width: entityListBox.width
                    Layout.alignment: Qt.AlignTop
                    height: 25
                    color: "grey"

                    Label {
                        text: qsTr("DDS Entities")
                        font.pixelSize: 15
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                EntityList {
                    id: entityList
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    Layout.leftMargin: 5
                }
            }
        }

        Rectangle {
            id: physicalViewBox
            SplitView.fillHeight: true
            SplitView.minimumHeight: parent.height / 4

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {

                TabBar {
                    id: physicalViewTabBar
                    width: physicalViewBox.width
                    Layout.alignment: Qt.AlignTop

                    TabButton {
                        text: "Physical List"
                    }

                    TabButton {
                        text: "Logical List"
                    }
                }

                StackLayout {
                    currentIndex: physicalViewTabBar.currentIndex

                    Layout.alignment: Qt.AlignTop
                    Layout.leftMargin: 5

                    PhysicalView {
                        id: physicalView
                    }

                    LogicalView {
                        id: logicalView
                    }
                }
            }
        }
    }

    ChartsLayout {
        id: chartsLayout
        SplitView.fillWidth: true
    }

    ColumnLayout {
        id: rightColumnLayout
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6
        spacing: 0

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
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true

            QosView {}

            SummaryView {}

            IssueView {}
        }
    }

    function createChart(dataKind){
        chartsLayout.createChart(dataKind)
    }
}

