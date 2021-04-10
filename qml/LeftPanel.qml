import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

SplitView {
    id: leftPanels
    orientation: Qt.Vertical

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
