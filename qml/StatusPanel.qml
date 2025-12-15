// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
import QtQml.Models 6.8
import Theme 1.0

/*
    Sidebar containing the Status and the Log views.
 */
ColumnLayout {
    id: statusPanel
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
                text: "Monitor Status"
                Layout.preferredWidth: parent.width - parent.height
                color: Theme.whiteSmoke
            }
        }
    }

    ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 0

        TabBar {
            id: logViewTabBar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Status")
            }
            TabButton {
                text: qsTr("Log")
            }
        }

        StackLayout {
            currentIndex: logViewTabBar.currentIndex
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true

            StatusView {
                id: statusView
            }

            LogView {
                id: logView
            }
        }
    }
}
