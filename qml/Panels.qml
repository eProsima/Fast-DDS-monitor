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
            spacing: 0

            Rectangle {
                id: entityLabel
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                height: 25
                color: "grey"
                z: entityList.z + 1

                Label {
                    text: qsTr("DDS Entities")
                    color: "white"
                    font.pixelSize: 15
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            EntityList {
                id: entityList
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            }
        }

        ColumnLayout {
            SplitView.fillHeight: true
            SplitView.minimumHeight: parent.height / 4
            spacing: 0

            TabBar {
                id: physicalViewTabBar
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                z: phisicalViewStackLayout.z + 1

                TabButton {
                    text: "Physical List"
                }

                TabButton {
                    text: "Logical List"
                }
            }

            StackLayout {
                id: phisicalViewStackLayout
                currentIndex: physicalViewTabBar.currentIndex
                Layout.alignment: Qt.AlignTop

                PhysicalView {
                    id: physicalView
                }

                LogicalView {
                    id: logicalView
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

            QosView {
                id: qosView
            }

            SummaryView {
                id: summaryView
            }

            IssueView {
                id: issueView
            }
        }

        function expand_all(view, model) {
            for(var i=0; i < model.rowCount(); i++) {
                var index = model.index(i, 0)
                if (!view.isExpanded(index)) {
                    view.expand(index)
                }
                if (model.rowCount(index) > 0) {
                    expand_childs(view, model, index)
                }
            }
        }

        function expand_childs(view, model, parent) {
            for(var i=0; i < model.rowCount(parent); i++) {
                var index = model.index(i, 0, parent)
                if (!view.isExpanded(index)) {
                    view.expand(index)
                }
                if (model.rowCount(index) > 0) {
                    expand_childs(view, model, index)
                }
            }
        }
    }

    function createChart(dataKind){
        chartsLayout.createChart(dataKind)
    }
}

