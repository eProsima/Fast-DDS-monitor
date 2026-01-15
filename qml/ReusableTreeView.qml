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
import QtQml.Models 6.8

import Theme 1.0

Item {
    id: reusableTreeView
    
    // Public properties that parent views can set
    property var treeModel: null
    property real columnSplitRatio: 0.5
    
    // Internal state
    property string selectedRowName: ""
    property string selectedRowValue: ""
    property bool selectedRowHasChildren: false
    property var rowDataMap: ({})

    property bool expandOnUpdate: true

    function expandAll() {
        treeView.expandRecursively()
    }

    function collapseAll() {
        // Manual collapse is more reliable than collapseRecursively()
        for (var i = treeView.rows - 1; i >= 0; i--) {
            if (treeView.isExpanded(i)) {
                treeView.collapse(i)
            }
        }
    }

    TreeView {
        id: treeView
        anchors.fill: parent
        clip: true
        resizableColumns: true
        boundsBehavior: Flickable.StopAtBounds
        
        reuseItems: false

        model: reusableTreeView.treeModel

        ScrollBar.vertical: CustomScrollBar {}
        ScrollBar.horizontal: CustomScrollBar {}

        Component.onCompleted: {
            Qt.callLater(function () {
                treeView.expandRecursively()
            })
        }

        Timer {
            id: valueColTimer
            interval: 0
            running: false
            repeat: false
            onTriggered: treeView.applyValueColumnWidth()
        }

        function updateValueColumnWidth() {
            valueColTimer.start()
        }

        function applyValueColumnWidth() {
            treeView.setColumnWidth(1, reusableTreeView.width - treeView.columnWidth(0))
        }

        onWidthChanged: updateValueColumnWidth()
        onLayoutChanged: updateValueColumnWidth()

        Connections {
            target: treeView.model
            function onUpdatedData() {
                reusableTreeView.rowDataMap = {}
                if (expandOnUpdate) {
                    Qt.callLater(function () { treeView.expandRecursively() })
                }
            }
        }

        selectionModel: ItemSelectionModel { model: treeView.model }

        delegate: Item {
            id: delegateRoot
            implicitWidth: column === 0 ? reusableTreeView.width * reusableTreeView.columnSplitRatio : reusableTreeView.width - treeView.columnWidth(0)
            implicitHeight: label.implicitHeight * 1.05

            readonly property real indentation: 20
            readonly property real padding: 5
            readonly property real gutter: 10

            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property bool hasChildren
            required property int depth
            required property int row
            required property int column
            required property bool current

            property var modelName: (column === 0 && typeof model.name !== 'undefined' && model.name !== null) ? String(model.name) : ""
            property var modelValue: (column === 1 && typeof model.value !== 'undefined' && model.value !== null) ? String(model.value) : ""

            onExpandedChanged: {
                indicator.rotation = expanded ? 0 : -90
            }
            
            Component.onCompleted: {
                indicator.rotation = expanded ? 0 : -90
                
                if (!reusableTreeView.rowDataMap) {
                    reusableTreeView.rowDataMap = {}
                }
                
                if (!reusableTreeView.rowDataMap[row]) {
                    reusableTreeView.rowDataMap[row] = {depth: depth}
                }
                
                if (column === 0) {
                    reusableTreeView.rowDataMap[row].name = modelName
                    reusableTreeView.rowDataMap[row].hasChildren = hasChildren
                } else if (column === 1) {
                    reusableTreeView.rowDataMap[row].value = modelValue
                }
            }
            
            onModelNameChanged: {
                if (column === 0) {
                    if (!reusableTreeView.rowDataMap) {
                        reusableTreeView.rowDataMap = {}
                    }
                    if (!reusableTreeView.rowDataMap[row]) {
                        reusableTreeView.rowDataMap[row] = {depth: depth}
                    }
                    reusableTreeView.rowDataMap[row].name = modelName
                }
            }

            onModelValueChanged: {
                if (column === 1) {
                    if (!reusableTreeView.rowDataMap) {
                        reusableTreeView.rowDataMap = {}
                    }
                    if (!reusableTreeView.rowDataMap[row]) {
                        reusableTreeView.rowDataMap[row] = {depth: depth}
                    }
                    reusableTreeView.rowDataMap[row].value = modelValue
                }
            }

            Rectangle {
                id: background
                anchors.fill: parent
                color: (treeView.alternatingRows && row % 2 !== 0) ? Theme.whiteSmoke : "white"
                
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                    
                    onClicked: function(mouse) {
                        if (mouse.button === Qt.RightButton) {
                            var rowData = reusableTreeView.rowDataMap[row] || {}
                            reusableTreeView.selectedRowName = rowData.name || ""
                            reusableTreeView.selectedRowValue = rowData.value || ""
                            reusableTreeView.selectedRowHasChildren = rowData.hasChildren || false
                            
                            contextMenu.popup()
                        }
                    }
                }
            }

            IconSVG {
                id: indicator
                x: padding + (column === 0 ? (depth * indentation) : 0)
                anchors.verticalCenter: parent.verticalCenter
                visible: column === 0 && isTreeNode && hasChildren
                name: "collapse"
                color: "grey"
                size: 10
                rotation: expanded ? 0 : -90

                TapHandler {
                    onSingleTapped: {
                        let index = treeView.index(row, column)
                        treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                        treeView.toggleExpanded(row)
                    }
                }
            }

            Text {
                id: label
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: (column === 0)
                                    ? (padding + (isTreeNode ? (depth + 1) * indentation : 0))
                                    : gutter
                anchors.right: parent.right
                anchors.rightMargin: padding
                clip: true
                text: column === 0 ? delegateRoot.modelName : delegateRoot.modelValue
                color: "black"
                
                font.pointSize: Theme.font.pointSize
                elide: Text.ElideRight
                
                MouseArea {
                    id: tooltipArea
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton
                    hoverEnabled: true
                    propagateComposedEvents: true
                }
                
                ToolTip.visible: tooltipArea.containsMouse && label.truncated
                ToolTip.text: text
                ToolTip.delay: 500
            }

            Menu {
                id: contextMenu
                
                MenuItem {
                    text: "Copy Property"
                    visible: true
                    height: visible ? implicitHeight : 0
                    onTriggered: {
                        clipboardHelper.text = reusableTreeView.selectedRowName
                        clipboardHelper.selectAll()
                        clipboardHelper.copy()
                    }
                }
                
                MenuItem {
                    text: "Copy Value"
                    visible: !reusableTreeView.selectedRowHasChildren
                    height: visible ? implicitHeight : 0
                    onTriggered: {
                        clipboardHelper.text = reusableTreeView.selectedRowValue
                        clipboardHelper.selectAll()
                        clipboardHelper.copy()
                    }
                }
                
                MenuItem {
                    text: "Copy Row"
                    visible: !reusableTreeView.selectedRowHasChildren
                    height: visible ? implicitHeight : 0
                    onTriggered: {
                        clipboardHelper.text = reusableTreeView.selectedRowName + ": " + reusableTreeView.selectedRowValue
                        clipboardHelper.selectAll()
                        clipboardHelper.copy()
                    }
                }
            }
        }
        
        TextInput {
            id: clipboardHelper
            visible: false
        }
    }
}
