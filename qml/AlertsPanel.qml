// Copyright 2025 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

import Theme 1.0

ColumnLayout {
    id: alertsPanel
    spacing: 0

    Rectangle {
        Layout.fillWidth: true
        height: 20
        color: Theme.grey

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            spacing: 0
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            Label {
                text: "Alerts"
                Layout.preferredWidth: parent.width - parent.height
                color: Theme.whiteSmoke
            }

            IconSVG {
                name: "plus"
                Layout.alignment: Qt.AlignRight
                scalingFactor: 1.4
                color: "white"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        alertDialog.open()
                    }
                }
            }
        }
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true

        SplitView {
            orientation: Qt.Vertical
            anchors.fill: parent

            ColumnLayout {
                id: alertListLayout
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: alertListTitle.height
                spacing: 10
                visible: true
                clip: true

                Rectangle {
                    id: alertListTitle
                    Layout.fillWidth: true
                    height: infoTabBar.height

                    Label {
                        text: "Alert List"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        color: Theme.eProsimaLightBlue
                        height: 2
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                    }
                }

                AlertList {
                    id: alertList
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    Layout.bottomMargin: 1
                }
            }

            Item {
                id: alertInfoLayout
                visible: true
                SplitView.fillHeight: true
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: infoTabBar.height
                clip: true

                TabBar {
                    id: infoTabBar
                    anchors.top: parent.top
                    anchors.left: parent.left
                    width: parent.width

                    TabButton {
                        text: qsTr("Info")
                    }
                }

                StackLayout {
                    currentIndex: infoTabBar.currentIndex
                    anchors.top: infoTabBar.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    width: parent.width

                    AlertsSummaryView {
                        id: alertsSummaryView
                    }
                }
            }
        }
    }
}
