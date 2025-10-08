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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Theme 1.0

Item {
    id: statusLayout

    // Public properties
    enum Status { Closed, Expanded, Collapsed }
    property int current_status: StatusLayout.Status.Closed
    required property int footer_height

    // Public signals
    signal close_status_layout()
    signal expand_status_layout()
    signal collapse_status_layout()

    // Private properties
    property bool filter_visible_: false
    property bool alert_icon_state: false

    // Private signals
    signal focus_entity_(int entityId)
    signal clean_filter_()

    // Read only design properties (sizes and colors)
    readonly property int tabs_height_: 30
    readonly property int elements_spacing_: 8
    readonly property int separator_line_: 2
    readonly property string grey_background_: "#eaeaea"

    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel

    Rectangle {
        id: tab_header
        anchors.top: parent.top
        width: parent.width
        height: tabs_height_
        color: "white"

        // Left-aligned TabBar
        TabBar {
            id: headerTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            spacing: elements_spacing_

            TabButton {
                text: qsTr("Problems")
                width: implicitWidth
                onClicked: pages.currentIndex = 0
            }
        }

        // Right-side icons row (same-line as tabs)
        Row {
            id: iconsRow
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: elements_spacing_
            spacing: elements_spacing_
            height: tab_header.height - elements_spacing_ * 3 / 2

            IconSVG {
                id: filter_icon;
                name: statusLayout.filter_visible_ ? "filter_full" : "filter_empty"
                size: parent.height;
                MouseArea {
                    anchors.fill: parent;
                    onClicked: statusLayout.clean_filter_()
                }
            }
            // connections to update filter icons
            Connections {
                target: statusLayout

                function onFocus_entity_(entityId) {
                    statusLayout.filter_visible_ = true
                }

                function onClean_filter_() {
                    statusLayout.filter_visible_ = false
                }
            }

            IconSVG {
                id: expand_icon
                name: statusLayout.current_status === StatusLayout.Status.Expanded ? "collapse" : "expand"
                size: parent.height
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (statusLayout.current_status === StatusLayout.Status.Expanded) {
                            collapse_status_layout()
                        }
                        else if (statusLayout.current_status === StatusLayout.Status.Collapsed) {
                            expand_status_layout()
                        }
                    }
                }
            }

            IconSVG {
                id: close_icon
                name: "cross"
                size: parent.height
                MouseArea {
                    anchors.fill: parent
                    onClicked: close_status_layout()
                }
            }
        }
    }

    // Main Alerts tab
    Tab {
        title: "Alerts"
        Rectangle {

            color: "white"

            // Main content of alerts tab: alert tree view with alerts per entity
            TreeView {
                id: alertMessagesView
                anchors.fill: parent
                model: alertMessageModel
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
            }
        }
    }


//        // Tab main stlye
//        style: TabViewStyle {
//            frameOverlap: 1
//            // Each tab style: simple rounded rect header with text
//            tab: Rectangle {
//                color: styleData.selected ? "white" : Theme.lightGrey
//                implicitWidth: Math.max(text.width + 10, tabs_width_)
//                implicitHeight: tabs_height_
//                radius: 4
    // Pages area controlled by the TabBar

    Rectangle {
        id: separator_line
        anchors.bottom: icon_section.top
        width: parent.width
        height: separator_line_
        color: Theme.grey
    }

    // footer (and ALWAYS displayed) error, warning and alerts counters bar section
    Rectangle {
        id: icon_section
        anchors.bottom: parent.bottom
        height: footer_height
        width: parent.width
        color: grey_background_

        // Close status so only this section is displayed, when component is loaded
        Component.onCompleted: {
            close_status_layout()
        }

        IconSVG {
            id: error_icon
            anchors.left: parent.left
            anchors.leftMargin: elements_spacing_
            anchors.verticalCenter: parent.verticalCenter
            name: "error"
            size: parent.height - elements_spacing_
        }

        Label {
            id: error_value
            anchors.left: error_icon.right
            anchors.leftMargin: elements_spacing_ / 2
            anchors.verticalCenter: parent.verticalCenter
            text: "0"
        }

        IconSVG {
            id: warning_icon
            anchors.left: error_value.right
            anchors.leftMargin: elements_spacing_
            anchors.verticalCenter: parent.verticalCenter
            name: "issues"
            size: parent.height - elements_spacing_
        }

        Label {
            id: warning_value
            anchors.left: warning_icon.right
            anchors.leftMargin: elements_spacing_ / 2
            anchors.verticalCenter: parent.verticalCenter
            text: "0"
        }
        IconSVG {
            id: alert_icon
            anchors.left: warning_value.right
            anchors.leftMargin: elements_spacing_
            anchors.verticalCenter: parent.verticalCenter
            name: alert_icon_state > 0 ? "alert_on" : "alert_off"
            size: parent.height - elements_spacing_
            Connections {
                target: alertMessageModel
                function onUpdatedData() {
                    // Re-evaluate manually when model changes
                    alert_icon_state = alertMessageModel.rowCount() > 0 ? true : false
                }
            }
        }

        Connections {
            target: controller
            function onUpdate_status_counters(errors, warnings) {
                error_value.text = errors
                warning_value.text = warnings
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (current_status === StatusLayout.Status.Collapsed)
                {
                    close_status_layout()
                }
                else
                {
                    collapse_status_layout()
                }
            }
        }
    }

    function filter_entity_status_log(entityId) {
        statusLayout.focus_entity_(entityId)
    }
}
