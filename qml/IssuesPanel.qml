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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml.Models
import Theme 1.0

/*
    Sidebar containing the Issues view.
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
                text: "Issues"
                Layout.preferredWidth: parent.width - parent.height
                color: Theme.whiteSmoke
            }
        }
    }

    ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 0

        IssueView {
            id: issueView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
        }
    }
}
