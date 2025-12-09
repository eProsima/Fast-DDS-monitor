/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Maurizio Ingrassia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

import QtQuick 6.10
import QtQuick.Controls 6.10
import QtQuick.Layouts 6.10

import Theme 1.0

Item {
    id: root

    // model properties

    property var model
    property var parentIndex
    property var childCount

    property var currentItem: null
    property var selectedIndex: null
    property var hoveredIndex: null

    // layout properties

    property bool selectionEnabled: false
    property bool hoverEnabled: false

    property int itemLeftPadding: 0
    property int rowHeight: 24
    property int rowPadding: 30
    property int rowSpacing: 6

    property color color: "black"
    property color inactive: "#808080"
    property color handleColor: color
    property color hoverColor: "lightgray"
    property color selectedColor: "silver"
    property color selectedItemColor: color

    property string defaultIndicator: "▶"
    property FontMetrics fontMetrics: FontMetrics {
        font.pointSize: Theme.font.pointSize
    }
    property alias font: root.fontMetrics.font

    // private (internal) signals
    signal filter_(int entityId)
    signal unfilter_()

    implicitWidth: parent.width
    implicitHeight: childrenRect.height

    // Components

    property Component handle: Rectangle {
        id: handle

        implicitWidth: 20
        implicitHeight: 20
        Layout.leftMargin: parent.spacing
        // 'collapse' icon points DOWN by default
        // We want: expanded -> down (0deg), collapsed -> right (-90deg)
        rotation: currentRow.expanded ? 0 : -90
        opacity: currentRow.hasChildren
        color: "transparent"

        // Smooth rotation when toggling
        Behavior on rotation { NumberAnimation { duration: 100; easing.type: Easing.OutQuart } }

        IconSVG {
            anchors.centerIn: parent
            name: "collapse"
            color: "grey"
            size: 10
        }
    }

    property Component contentItem: Item {
        id: contentData

        IconSVG {
            id: status_icon
            visible: !(currentRow.currentId === "all" && currentRow.currentKind === "INVALID")
                    && currentRow.currentStatus != "OK"
            anchors.left: parent.left; anchors.leftMargin: -5
            anchors.verticalCenter: parent.verticalCenter
            name: currentRow.currentStatus == "ERROR" ? "error"
                    : currentRow.currentStatus == "WARNING" ? "issues" : ""
            color: currentRow.currentAlive ? currentRow.currentStatus == "ERROR" ? "red" :"yellow" : "grey"
            size: 15
        }

        Text {
            id: entity_name
            anchors.left: status_icon.right; anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter

            color:currentRow.currentAlive ? currentRow.isSelectedIndex ? root.selectedItemColor : root.color : root.inactive
            text: currentRow.currentData
            font: root.font
        }

        Text {
            id: id_value
            anchors.left: entity_name.right; anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter

            color:currentRow.currentAlive ? currentRow.isSelectedIndex ? root.selectedItemColor : root.color : root.inactive
            text: currentRow.currentId == undefined || currentRow.currentValue == undefined ? "" :
                    currentRow.currentId != "all" && currentRow.currentKind === "INVALID" ?
                    currentRow.currentId === "all" ? "" : "(" + currentRow.currentValue + ")" : currentRow.currentValue
            font: root.font
        }

        Text {
            id: description
            anchors.left: id_value.right; anchors.leftMargin: 20
            anchors.right: parent.right; anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
            height: parent.height

            color:currentRow.currentAlive ? currentRow.isSelectedIndex ? root.selectedItemColor : root.color : root.inactive
            text: currentRow.currentId != "all" && currentRow.currentKind === "INVALID" ?
                    currentRow.currentId === "all" ? "" :
                    "Entity ID:  " + currentRow.currentId : currentRow.currentDescription
            font.pointSize: Theme.font.pointSize
            font.italic: true
            onLinkActivated: Qt.openUrlExternally(link)

            MouseArea {
                visible: currentRow.currentDescription.includes("href")
                anchors.fill: parent
                acceptedButtons: Qt.NoButton
                cursorShape: Qt.PointingHandCursor
            }
        }
    }

    property Component hoverComponent: Rectangle {
        width: parent.width
        height: parent.height
        color: currentRow.isHoveredIndex && !currentRow.isSelectedIndex ? root.hoverColor : "transparent"
    }

    // Body

    ColumnLayout {
        width: parent.width
        spacing: 0

        Repeater {
            id: repeater
            model: root.model ? childCount : 0  // Only create delegates when model exists
            Layout.fillWidth: true

            delegate: ColumnLayout {
                id: itemColumn

                Layout.leftMargin: itemLeftPadding
                spacing: 0

                QtObject {
                    id: _prop

                    property var currentIndex: root.model.index(index, 0, parentIndex)
                    property var currentData: root.model.data(currentIndex)
                    property var currentId: root.model.id(currentIndex)
                    property var currentStatus: root.model.status(currentIndex)
                    property var currentKind: root.model.kind(currentIndex)
                    property var currentValue: root.model.value(currentIndex)
                    property var currentDescription: root.model.description(currentIndex)
                    property var currentAlive: root.model.alive(currentIndex)
                    property Item currentItem: repeater.itemAt(index)
                    property bool expanded: true
                    property bool selected: false
                    property int itemChildCount: root.model.rowCount(currentIndex)
                    readonly property int depth: root.model.depth(currentIndex)
                    readonly property bool hasChildren: itemChildCount > 0
                    readonly property bool isSelectedIndex: root.selectionEnabled && currentIndex === root.selectedIndex
                    readonly property bool isHoveredIndex: root.hoverEnabled && currentIndex === root.hoveredIndex
                    readonly property bool isSelectedAndHoveredIndex: hoverEnabled && selectionEnabled && isHoveredIndex && isSelectedIndex

                    function toggle(){
                        if(_prop.hasChildren)
                        {
                            _prop.expanded = !_prop.expanded
                        }

                        _prop.focus()
                    }

                    function focus(){
                        controller.endpoint_click(_prop.currentId)
                        controller.participant_click(_prop.currentId)
                    }
                }

                Connections {
                    target: root.model
                    ignoreUnknownSignals: true
                    function onLayoutChanged() {
                        const parent = root.model.index(index, 0, parentIndex)
                        _prop.itemChildCount = root.model.rowCount(parent)
                        // refresh counter
                        var new_value = root.model.value(_prop.currentIndex)
                        if (new_value != undefined)
                        {
                            _prop.currentValue = new_value
                        }
                    }
                }

                Connections {
                    target: root
                    function onFilter_(entityId) {
                        if (_prop.currentId == entityId)
                        {
                            _prop.expanded = true
                        }
                    }

                    function onUnfilter_(){
                        _prop.expanded = false
                    }
                }

                Item {
                id: column

                Layout.fillWidth: true

                width: row.implicitWidth
                height: Math.max(row.implicitHeight, root.rowHeight)

                RowLayout {
                    id: row

                    anchors.fill: parent
                    Layout.fillHeight: true

                    z: 1
                    spacing: root.rowSpacing

                    // handle
                    Loader {
                        id: indicatorLoader
                        sourceComponent: handle

                        Layout.leftMargin: parent.spacing

                        property QtObject currentRow: _prop

                        TapHandler { onSingleTapped: _prop.toggle() }
                    }

                    //  Content
                    Loader {
                        id: contentItemLoader
                        sourceComponent: contentItem

                        Layout.fillWidth: true
                        height: rowHeight

                        property QtObject currentRow: _prop

                        Connections {
                            target: root.model
                            ignoreUnknownSignals: true
                            function onDataChanged(modelIndex) {
                                const changedId = modelIndex.internalId
                                const currentId = _prop.currentIndex.internalId
                                if(changedId === currentId){
                                    contentItemLoader.currentRow.currentData = root.model.data(modelIndex);
                                }
                            }
                        }
                    }

                    TapHandler {
                        onDoubleTapped: _prop.toggle()
                        onSingleTapped: {
                            _prop.focus()
                            root.currentItem = _prop.currentItem
                            root.selectedIndex = _prop.currentIndex
                        }
                    }
                }

                Loader {
                    id: hoverLoader
                    sourceComponent: hoverComponent

                    width: row.width + (1 + _prop.depth * rowPadding)
                    height: parent.height

                    x: -(_prop.depth * rowPadding)
                    z: 0

                    clip: false

                    property QtObject currentRow: _prop

                    HoverHandler {
                        onHoveredChanged: {
                            if(root.hoverEnabled){
                            if(hovered && root.hoveredIndex !== _prop.currentIndex)
                                root.hoveredIndex = _prop.currentIndex
                            if(!hovered && root.hoveredIndex === _prop.currentIndex)
                                root.hoveredIndex = null
                            }
                        }
                    }
                }

                }

                // loader to populate the children row for each node
                Loader {
                    id: loader

                    Layout.fillWidth: true

                    source: "StatusTreeViewItem.qml"
                    visible: _prop.expanded

                    onLoaded: {
                        item.model = root.model
                        item.parentIndex = _prop.currentIndex
                        item.childCount = _prop.itemChildCount
                    }

                    Connections {
                        target: root.model
                        ignoreUnknownSignals: true
                        function onLayoutChanged() {
                            const parent = root.model.index(index, 0, parentIndex)
                            loader.item.childCount = root.model.rowCount(parent)
                        }
                    }

                    Binding { target: loader.item; property: "model"; value: root.model; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "handle"; value: root.handle; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "contentItem"; value: root.contentItem; when: loader.status == Loader.Ready }

                    Binding { target: loader.item; property: "currentItem"; value: root.currentItem; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "selectedIndex"; value: root.selectedIndex; when: loader.status == Loader.Ready }
                    Binding { target: root; property: "currentItem"; value: loader.item.currentItem; when: loader.status == Loader.Ready }
                    Binding { target: root; property: "selectedIndex"; value: loader.item.selectedIndex; when: loader.status == Loader.Ready }

                    Binding { target: loader.item; property: "color"; value: root.color; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "handleColor"; value: root.handleColor; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "hoverEnabled"; value: root.hoverEnabled; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "hoverColor"; value: root.hoverColor; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "selectionEnabled"; value: root.selectionEnabled; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "selectedColor"; value: root.selectedColor; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "selectedItemColor"; value: root.selectedItemColor; when: loader.status == Loader.Ready }

                    Binding { target: loader.item; property: "itemLeftPadding"; value: root.rowPadding; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "rowHeight"; value: root.rowHeight; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "rowPadding"; value: root.rowPadding; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "rowSpacing"; value: root.rowSpacing; when: loader.status == Loader.Ready }
                    Binding { target: loader.item; property: "fontMetrics"; value: root.fontMetrics; when: loader.status == Loader.Ready }
                }
            }
        }
    }

    function filter(entityId) {
        root.filter_(entityId)
    }

    function unfilter() {
        root.unfilter_()
    }
}
