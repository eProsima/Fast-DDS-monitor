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

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

Item {
    id: spyView
    // Public properties
    property var model: userDataModel                       // User Data JSON model
    property string domain_id                               // ID of the domain where the topic is
    property string topic_id                                // ID of the topic to spy

    // Private properties
    property bool is_active_: false                         // Whether the spy is active or not

    // Read-only design properties
    readonly property int elements_spacing_: 10

    // Used to store expanded/collapsed state of the tree items, all the attemps
    // to use a more sophisticated update method have failed.
    property var expandedState: ({})


    Flickable
    {
        id: userDataView
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
        anchors.fill: parent
        width: parent.width
        height: parent.height
        contentWidth: parent.width
        contentHeight: parent.height

        TreeView {

            id: treeView
            anchors.fill: parent
            anchors.topMargin: buttonContainer.height + buttonContainer.anchors.topMargin + elements_spacing_
            anchors.leftMargin: elements_spacing_
            anchors.rightMargin: elements_spacing_
            model: spyView.model
            headerVisible: false
            frameVisible: false

            Component.onCompleted: expandAll()

            TableViewColumn {
                role: "name"
                title: "JSON view"
                width: 400
            }

            TableViewColumn {
                role: "value"
                title: "JSON view"
                width: 400
            }

            itemDelegate: Text {
                text: styleData.value
            }

            function saveExpanded(parentIndex) {
                for (var i = 0; i < model.rowCount(parentIndex); ++i) {
                    var idx = model.index(i, 0, parentIndex)
                    var key = model.data(idx, Qt.DisplayRole)
                    if (isExpanded(idx)) {
                        spyView.expandedState[idx] = true
                        saveExpanded(idx)
                    }
                }
            }

            function restoreExpanded(parentIndex) {
                for (var i = 0; i < model.rowCount(parentIndex); ++i) {
                    var idx = model.index(i, 0, parentIndex)
                    var key = model.data(idx, Qt.DisplayRole)
                    if (spyView.expandedState[idx]) {
                        expand(idx)
                        restoreExpanded(idx)
                    }
                }
            }

            Connections {
                target: spyView.model
                function onUpdatedData() {
                    // Save current scroll position to restore it later
                    var flick = treeView.flickableItem
                    var oldY = flick.contentY
                    var oldX = flick.contentX
                    // Save collapsed/expanded state
                    treeView.saveExpanded(model.invalidIndex())
                    // Reset the model to force a refresh
                    treeView.model = null
                    treeView.model = spyView.model
                    // Wait for full rebuild before restoring previous state
                    Qt.callLater(function() {
                        // Restore expanded state
                        treeView.restoreExpanded(model.invalidIndex())
                        // Restore scroll position
                        flick.contentY = oldY
                        flick.contentX = oldX
                    })
                }
            }
        }

        Row {
            id: buttonContainer
            spacing: spyView.elements_spacing_
            anchors.top: parent.top; anchors.topMargin: spyView.elements_spacing_
            anchors.right: parent.right; anchors.rightMargin: spyView.elements_spacing_

            Button {
                id: pausePlayButton
                text: "Pause/Play"
                onClicked: {
                    console.log("Pause/Play button clicked")
                    spyView.is_active_ = !spyView.is_active_
                    spyView.is_active_ ? controller.start_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
                                : controller.stop_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
                }
            }
        }
    }
}
