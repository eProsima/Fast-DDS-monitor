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

import QtQuick.Window

Item {
    id: logView
    visible: true

    TreeView {
        id: logTreeView
        anchors.fill: parent
        model: logModel
        selectionMode: SelectionMode.NoSelection
        frameVisible: false
        itemDelegate: Item {
            Text {
                anchors.fill: parent
                elide: styleData.elideMode
                text: {
                    // Error when undefined value.
                    // Do not know when this could happen, but happens
                    styleData.value ? styleData.value : ""
                }
            }
        }

        TableViewColumn {
            width: parent.width / 2
            role: "name"
            title: "Name"
        }

        TableViewColumn {
            width: parent.width / 2
            role: "value"
            title: "Value"
        }

        Component.onCompleted: leftPanel.expandAll(logTreeView, logModel)

        Connections {
            target: logModel
            function onUpdatedData() {
                leftPanel.expandAll(logTreeView, logModel)
            }
        }
    }
}
