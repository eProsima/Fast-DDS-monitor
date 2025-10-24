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
import QtQml.Models

import Theme 1.0

Item {
    id: qos_view
    // Fill the parent Item in MonitoringPanel. MonitoringPanel now uses a
    // plain Item to host this view (not a Layout-managed container), so using
    // anchors is safe and avoids layout recursion.
    anchors.fill: parent
    // Column width properties used by header and delegate

    TreeView {
        id: treeView
        anchors.fill: parent
        clip: true
        resizableColumns: true
        boundsBehavior: Flickable.StopAtBounds

        model: qosModel

        ScrollBar.vertical: CustomScrollBar {}
        ScrollBar.horizontal: CustomScrollBar {}

        Component.onCompleted: {
            Qt.callLater(function () {
                treeView.expandRecursively()
            })
        }

        // Debounced resize of the Value column (column 1) to fill remaining space
        Timer {
            id: valueColTimer
            interval: 0
            running: false
            repeat: false
            onTriggered: treeView.applyValueColumnWidth()
        }

        function updateValueColumnWidth() {
            // Schedule for next tick to avoid re-entrant polish loops
            valueColTimer.start()
        }

        function applyValueColumnWidth() {
            treeView.setColumnWidth(1, qos_view.width - treeView.columnWidth(0))
        }

        onWidthChanged: updateValueColumnWidth()
        // This is a TreeView property signal; in case it fires during polish, debounce avoids loops
        onLayoutChanged: updateValueColumnWidth()

        Connections {
            target: treeView.model
            function onUpdatedData() {
                Qt.callLater(function () { treeView.expandRecursively() })
            }
        }

        // Bind selection model to the same model so selection works reliably
        selectionModel: ItemSelectionModel { model: treeView.model }

        delegate: Item {
            implicitWidth: column === 0 ? qos_view.width / 2 : qos_view.width - treeView.columnWidth(0)
            implicitHeight: label.implicitHeight * 1.05

            readonly property real indentation: 20
            readonly property real padding: 5

            // Assigned to by TreeView:
            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property bool hasChildren
            required property int depth
            required property int row
            required property int column
            required property bool current

            // Rotate indicator when expanded by the user
            // (requires TreeView to have a selectionModel)
            property Animation indicatorAnimation: NumberAnimation {
                target: indicator
                property: "rotation"
                // Icon 'collapse' points down by default. We want:
                // - expanded: down (0 deg)
                // - collapsed: right (-90 deg)
                from: expanded ? -90 : 0
                to: expanded ? 0 : -90
                duration: 100
                easing.type: Easing.OutQuart
            }
            TableView.onPooled: indicatorAnimation.complete()
            TableView.onReused: if (current) indicatorAnimation.start()
            onExpandedChanged: indicator.rotation = expanded ? 0 : -90

            Rectangle {
                id: background
                anchors.fill: parent
                color: row === treeView.currentRow ? Theme.lightBlueProxy : ((treeView.alternatingRows && row % 2 !== 0) ? Theme.whiteSmoke : "white")
            }

            IconSVG {
                id: indicator
                // Show expand/collapse indicator only in first column
                x: padding + (column === 0 ? (depth * indentation) : 0)
                anchors.verticalCenter: parent.verticalCenter
                visible: column === 0 && isTreeNode && hasChildren
                name: "collapse"
                color: "grey"
                size: 10

                TapHandler {
                    onSingleTapped: {
                        let index = treeView.index(row, column)
                        treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                        treeView.toggleExpanded(row)
                    }
                }
            }

            // Make cell text selectable with a read-only TextInput
            TextInput {
                id: label
                // Indent only in column 0 so column 1 (value) uses the full width
                anchors.verticalCenter: parent.verticalCenter
                // Always anchor left; add indentation only for column 0
                anchors.left: parent.left
                anchors.leftMargin: (column === 0)
                                      ? (padding + (isTreeNode ? (depth + 1) * indentation : 0))
                                      : padding
                clip: true
                readOnly: true
                selectByMouse: true
                // Keep single line behavior similar to Label
                echoMode: TextInput.Normal
                selectionColor: Theme.eProsimaLightBlue
                // Avoid stealing focus when not selecting
                focus: false
                // Use explicit role names when available: name/value.
                // and default to empty to avoid assigning undefined to QString.
                text: {
                    if (column === 0 && typeof model.name !== 'undefined' && model.name !== null)
                        return String(model.name)
                    if (column === 1 && typeof model.value !== 'undefined' && model.value !== null)
                        return String(model.value)
                    return ""
                }
            }
        }
    }
}
