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


import QtQuick 6.8
import QtQuick.Window 6.8
import QtQuick.Controls 6.8
import QtQml 6.8

Flickable {
    id: root

    implicitWidth: 400
    implicitHeight: 400
    clip: true

    property var model
    readonly property alias currentIndex: tree.selectedIndex
    readonly property alias currentItem: tree.currentItem
    property var currentData

    property alias handle: tree.handle
    property alias contentItem: tree.contentItem
    property Component highlight: Rectangle {
        color: root.selectedColor
    }

    property alias selectionEnabled: tree.selectionEnabled
    property alias hoverEnabled: tree.hoverEnabled

    // Color properties (do not alias to tree to avoid binding loops)
    property color color: "black"
    property color hoverColor: "lightgray"
    // Themeable colors (defaults); avoid aliasing to prevent binding loops
    property color handleColor: "black"
    property color selectedColor: "silver"
    property color selectedItemColor: "black"

    property alias rowHeight: tree.rowHeight
    property alias rowPadding: tree.rowPadding
    property alias rowSpacing: tree.rowSpacing

    property alias fontMetrics: tree.fontMetrics
    property alias font: tree.font

    enum Handle {
        Triangle,
        TriangleSmall,
        TriangleOutline,
        TriangleSmallOutline,
        Chevron,
        Arrow
    }

    readonly property int filter_all_: -2   // backend::ID_ALL
    property int current_filter_: filter_all_
    signal entity_status_filtered()

    property int handleStyle: StatusTreeView.Handle.TriangleSmallOutline

    contentHeight: tree.height
    contentWidth: width
    boundsBehavior: Flickable.StopAtBounds
    ScrollBar.vertical: ScrollBar {}

    Component.onCompleted:{
        root.clean_filter()
    }

    Connections
    {
        target: root.model
        function onLayoutChanged() {
            root.filter_model_by_id(root.current_filter_)
        }
    }

    Connections {
        function onCurrentIndexChanged() {
            if(currentIndex)
            {
                currentData = model.data(currentIndex)
            }
        }
    }

    StatusTreeViewItem {
        id: tree

        model: root.model
        parentIndex: model.rootIndex()
        childCount: model.rowCount(parentIndex)

        itemLeftPadding: 0
        defaultIndicator: indicatorToString(handleStyle)
        z: 1

        // Only initialize when model is ready
        visible: root.model !== null && root.model !== undefined

        Connections {
            target: root.model
            ignoreUnknownSignals: true
            function onLayoutChanged() {
               tree.childCount = root.model ? root.model.rowCount(tree.parentIndex) : 0
            }
        }
    }

    // Forward theme/color properties to the tree instance (one-way bindings)
    Binding { target: tree; property: "color"; value: root.color; when: true }
    Binding { target: tree; property: "handleColor"; value: root.handleColor; when: true }
    Binding { target: tree; property: "hoverColor"; value: root.hoverColor; when: true }
    Binding { target: tree; property: "selectedColor"; value: root.selectedColor; when: true }
    Binding { target: tree; property: "selectedItemColor"; value: root.selectedItemColor; when: true }

    Loader {
        id: highlightLoader
        sourceComponent: highlight

        width: root.width
        height: root.rowHeight
        z: 0
        visible: root.selectionEnabled && tree.currentItem !== null

        Binding {
            target: highlightLoader.item
            property: "y"
            value: tree.currentItem ? tree.currentItem.mapToItem(tree, 0, 0).y + tree.anchors.topMargin : 0
            when: highlightLoader.status === Loader.Ready
        }
    }

    function indicatorToString(handle){
        switch (handle){
            case StatusTreeView.Handle.Triangle: return "▶";
            case StatusTreeView.Handle.TriangleSmall: return "►";
            case StatusTreeView.Handle.TriangleOutline: return "▷";
            case StatusTreeView.Handle.TriangleSmallOutline: return "⊳";
            case StatusTreeView.Handle.Chevron: return "❱";
            case StatusTreeView.Handle.Arrow: return "➤";
            default: return "▶";
        }
    }


    function clean_filter()
    {
        root.filter_model_by_id(filter_all_)
        tree.unfilter()
    }

    function filter_model_by_id(entityId)
    {
        if (current_filter_ != entityId)
        {
            current_filter_ = entityId
            model.filter_proxy(current_filter_)
            root.entity_status_filtered()
            tree.filter(current_filter_)
        }
    }
}
