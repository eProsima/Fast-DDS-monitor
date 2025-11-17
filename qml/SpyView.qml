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
    property string topic_name                              // Name of the topic to spy

    // Private properties
    property bool is_active_: false                         // Whether the spy is active or not

    // Read-only design properties
    readonly property int elements_spacing_: 10

    // Used to store expanded/collapsed state of the tree items, all the attemps
    // to use a more sophisticated update method have failed.
    property var expandedState: ({})

    function start_spy() {
        if (!spyView.is_active_) {
            controller.start_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
            spyView.is_active_ = true
        }
    }

    function stop_spy() {
        if (spyView.is_active_) {
            controller.stop_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
            spyView.is_active_ = false
        }
    }

    function initialize(domainId, topicId, topicName) {
        stop_spy()
        domain_id = domainId
        topic_id = topicId
        topic_name = topicName
        start_spy()
    }

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
            selectionMode: SelectionMode.NoSelection

            // Component.onCompleted: expandAll()

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

            // Expand all tree items
            function expandAll() {
                expandChilds(treeView.model.invalidIndex())
            }

            // Expand all child items of a given parent
            function expandChilds(parent) {
                for(var i=0; i < model.rowCount(parent); i++) {
                    var index = model.index(i, 0, parent)
                    if (!isExpanded(index)) {
                        expand(index)
                        var path = pathFromIndex(index)
                        spyView.expandedState[path] = true
                    }
                    if (model.rowCount(index) > 0) {
                        expandChilds(index)
                    }
                }
            }

            // Collapse all tree items
            function collapseAll() {
                collapseChilds(treeView.model.invalidIndex())
            }

            // Expand all child items of a given parent
            function collapseChilds(parent) {
                for(var i=0; i < model.rowCount(parent); i++) {
                    var index = model.index(i, 0, parent)
                    if (isExpanded(index)) {
                        if (model.rowCount(index) > 0) {
                            collapseChilds(index)
                        }
                        collapse(index)
                        var path = pathFromIndex(index)
                        delete spyView.expandedState[path]
                    }
                }
            }

            function saveExpanded(parentIndex) {
                for (var i = 0; i < model.rowCount(parentIndex); ++i) {
                    var idx = model.index(i, 0, parentIndex)
                    var key = model.data(idx, model.nameRole())
                    if (isExpanded(idx)) {
                        var path = pathFromIndex(idx)
                        if (path != "") {
                            spyView.expandedState[path] = true
                        }
                        saveExpanded(idx)
                    }
                }
            }

            function restoreExpanded(parentIndex) {
                for (var i = 0; i < model.rowCount(parentIndex); ++i) {
                    var idx  = model.index(i, 0, parentIndex)
                    var key  =  model.data(idx, model.nameRole())
                    var path = pathFromIndex(idx)
                    if (path in spyView.expandedState) {
                        if (spyView.expandedState[path]) {
                            expand(idx)
                        }
                        restoreExpanded(idx)
                    }
                }
            }

            // Computes the complete path of an index in the tree (in the json)
            // concatenating all the keys from root to the index and "/" as separator
            function pathFromIndex(idx) {
                if (!idx || !idx.valid)
                    return ""

                var keys = []
                var current = idx
                while (current.valid) {
                    var key = model.data(current, model.nameRole())
                    keys.unshift(key)
                    current = model.parent(current)
                }
                return keys.join("/")
            }

            // Computes the index in the tree from a complete path in the json
            // returning the invalid index if not found
            function indexFromPath(path) {
                var keys = path.split("/")
                var currentIndex = model.index(0, 0, model.invalidIndex())
                for (var key_i = 0; key_i < keys.length; ++key_i) {
                    var found = false
                    for (var row_j = 0; row_j < model.rowCount(currentIndex); ++row_j) {
                        var childIndex = model.index(row_j, 0, currentIndex)
                        if (model.data(childIndex, model.nameRole()) === keys[key_i]) {
                            currentIndex = childIndex
                            found = true
                            break
                        }
                    }
                    if (!found) {
                        return model.invalidIndex()
                    }
                }
                return currentIndex
            }

            // Copy the current data in json format to clipboard
            function copyData() {
                model.copy_json_to_clipboard()
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

        Text {
            id: rowTitle
            text: topic_name + " Data"
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top; anchors.topMargin: spyView.elements_spacing_
            anchors.left: parent.left; anchors.leftMargin: spyView.elements_spacing_
        }

        Row {
            id: buttonContainer
            spacing: spyView.elements_spacing_
            anchors.top: parent.top; anchors.topMargin: spyView.elements_spacing_
            anchors.right: parent.right; anchors.rightMargin: spyView.elements_spacing_

            Button {
                id: pausePlayButton
                text: spyView.is_active_ ? "Pause" : "Play"
                onClicked: {
                    spyView.is_active_ = !spyView.is_active_
                    spyView.is_active_ ? controller.start_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
                                : controller.stop_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
                }
            }

            Button {
                id: expandButton
                text: "Expand All"
                onClicked: {
                    treeView.expandAll()
                }
            }

            Button {
                id: collapseButton
                text: "Collapse All"
                onClicked: {
                    treeView.collapseAll()
                }
            }

            Button {
                id: copyButton
                text: "Copy JSON"
                onClicked: {
                    treeView.copyData()
                }
            }
        }
    }
}
