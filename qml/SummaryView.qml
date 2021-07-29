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

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQml.Models 2.11


Item {
    id: summary_view
    visible: true

    TreeView {
        id: summary_tree_view
        anchors.fill: parent
        model: summaryModel
        frameVisible: false
        selectionMode: SelectionMode.NoSelection
        selection: ItemSelectionModel {
            id: item_selection_model
            model: summaryModel
        }
        itemDelegate: Item {
            Text {
                anchors.fill: parent
                elide: styleData.elideMode
                text: styleData.value
            }
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

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

        Component.onCompleted: leftPanel.expandAll(summary_tree_view, summaryModel)

        Connections {
            target: summaryModel
            function onUpdatedData() {
                leftPanel.expandAll(summary_tree_view, summaryModel)
            }
        }
    }

    // Timer to refresh summary each 10 seconds
    Timer{
        id: timer
        interval: 10000
        running: true
        repeat: true
        onTriggered: controller.refresh_summary()
    }
}
