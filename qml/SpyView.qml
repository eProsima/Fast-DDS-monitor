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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml.Models

import Theme 1.0

Item {
    id: spyView
    property var model: userDataModel
    property string domain_id
    property string topic_id
    property string topic_name

    property bool is_active_: false

    readonly property int elements_spacing_: 10

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

    Flickable {
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
            clip: true

            ScrollBar.vertical: CustomScrollBar {}
            ScrollBar.horizontal: CustomScrollBar {}

            delegate: Item {
                id: delegateRoot
                implicitWidth: treeView.width
                implicitHeight: 30

                required property TreeView treeView
                required property bool isTreeNode
                required property bool expanded
                required property bool hasChildren
                required property int depth
                required property int row
                required property int column

                property var modelDisplay: (typeof model.display !== 'undefined' && model.display !== null) ? String(model.display) : ""

                Rectangle {
                    anchors.fill: parent
                    color: "transparent"

                    Row {
                        anchors.fill: parent
                        anchors.leftMargin: depth * 20
                        spacing: 5

                        Item {
                            width: 20
                            height: parent.height
                            visible: column === 0 && isTreeNode && hasChildren

                            IconSVG {
                                anchors.centerIn: parent
                                name: "collapse"
                                size: 10
                                rotation: expanded ? 0 : -90
                                color: "grey"
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: treeView.toggleExpanded(row)
                            }
                        }

                        Text {
                            width: (treeView.width / 2) - (depth * 20) - 30
                            height: parent.height
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                            text: modelDisplay
                            visible: column === 0
                        }

                        Text {
                            width: treeView.width / 2
                            height: parent.height
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                            text: modelDisplay
                            visible: column === 1
                        }
                    }
                }
            }

            function expandAll() {
                expandChilds(treeView.model ? treeView.model.index(0, 0) : null)
            }

            function expandChilds(parent) {
                if (!model || !parent) return

                for(var i = 0; i < model.rowCount(parent); i++) {
                    var index = model.index(i, 0, parent)
                    if (index && index.valid) {
                        expand(index)
                        var path = pathFromIndex(index)
                        spyView.expandedState[path] = true
                        if (model.rowCount(index) > 0) {
                            expandChilds(index)
                        }
                    }
                }
            }

            function collapseAll() {
                collapseChilds(treeView.model ? treeView.model.index(0, 0) : null)
            }

            function collapseChilds(parent) {
                if (!model || !parent) return

                for(var i = 0; i < model.rowCount(parent); i++) {
                    var index = model.index(i, 0, parent)
                    if (index && index.valid) {
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
                if (!model || !parentIndex) return

                for (var i = 0; i < model.rowCount(parentIndex); ++i) {
                    var idx = model.index(i, 0, parentIndex)
                    if (idx && idx.valid && isExpanded(idx)) {
                        var path = pathFromIndex(idx)
                        if (path !== "") {
                            spyView.expandedState[path] = true
                        }
                        saveExpanded(idx)
                    }
                }
            }

            function restoreExpanded(parentIndex) {
                if (!model || !parentIndex) return

                for (var i = 0; i < model.rowCount(parentIndex); ++i) {
                    var idx = model.index(i, 0, parentIndex)
                    if (idx && idx.valid) {
                        var path = pathFromIndex(idx)
                        if (path in spyView.expandedState && spyView.expandedState[path]) {
                            expand(idx)
                        }
                        restoreExpanded(idx)
                    }
                }
            }

            function pathFromIndex(idx) {
                if (!idx || !idx.valid)
                    return ""

                var keys = []
                var current = idx
                while (current.valid) {
                    var key = model.data(current, 0) // Use role 0 for display
                    keys.unshift(key)
                    current = model.parent(current)
                }
                return keys.join("/")
            }

            function copyData() {
                if (model && typeof model.copy_json_to_clipboard === 'function') {
                    model.copy_json_to_clipboard()
                }
            }

            Connections {
                target: spyView.model
                function onUpdatedData() {
                    var flick = treeView.flickableItem
                    if (!flick) return

                    var oldY = flick.contentY
                    var oldX = flick.contentX

                    treeView.saveExpanded(model ? model.index(0, 0) : null)

                    treeView.model = null
                    treeView.model = spyView.model

                    Qt.callLater(function() {
                        treeView.restoreExpanded(model ? model.index(0, 0) : null)
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
            anchors.top: parent.top
            anchors.topMargin: spyView.elements_spacing_
            anchors.left: parent.left
            anchors.leftMargin: spyView.elements_spacing_
        }

        Row {
            id: buttonContainer
            spacing: spyView.elements_spacing_
            anchors.top: parent.top
            anchors.topMargin: spyView.elements_spacing_
            anchors.right: parent.right
            anchors.rightMargin: spyView.elements_spacing_

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
