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
    id: statusLayout

    enum Status { Closed, Expanded, Collapsed }
    property int current_status: StatusLayout.Status.Closed
    required property int footer_height

    signal close_status_layout()
    signal expand_status_layout()
    signal collapse_status_layout()

    property bool filter_visible_: false
    property bool alert_icon_state: false

    signal focus_entity_(int entityId)
    signal clean_filter_()

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

            TabButton {
                text: qsTr("Alerts")
                width: implicitWidth
                onClicked: pages.currentIndex = 1
            }
        }

        Row {
            id: iconsRow
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: elements_spacing_
            spacing: elements_spacing_
            height: tab_header.height - elements_spacing_ * 3 / 2

            IconSVG {
                id: filter_icon
                name: statusLayout.filter_visible_ ? "filter_full" : "filter_empty"
                size: parent.height
                MouseArea {
                    anchors.fill: parent
                    onClicked: statusLayout.clean_filter_()
                }
            }

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
                size: parent.height - 3
                MouseArea {
                    anchors.fill: parent
                    onClicked: close_status_layout()
                }
            }
        }
    }

    StackLayout {
        id: pages
        anchors.top: tab_header.bottom
        anchors.bottom: separator_line.top
        anchors.left: parent.left
        anchors.right: parent.right
        currentIndex: headerTabBar.currentIndex

        // Problems Tab (index 0)
        Rectangle {
            color: "white"

            StatusTreeView {
                id: status_tree_view
                anchors.fill: parent
                anchors.margins: 1

                model: entityStatusModel

                // Display if hidden when problems filtered (from right-click dialog)
                onEntity_status_filtered: {
                    collapse_status_layout()
                }

                // Filter and clean filter signal-slots management
                Connections {
                    target: statusLayout

                    function onClean_filter_() {
                        status_tree_view.clean_filter()
                    }

                    function onFocus_entity_(entityId) {
                        status_tree_view.filter_model_by_id(entityId)
                    }
                }
            }
        }

        // Alerts Tab (index 1)
        Rectangle {
            color: "white"
            
            ReusableTreeView {
                anchors.fill: parent
                treeModel: alertMessageModel
                columnSplitRatio: 0.5
                expandOnUpdate: false
            }
        }
    }

    Rectangle {
        id: separator_line
        anchors.bottom: icon_section.top
        width: parent.width
        height: separator_line_
        color: Theme.grey
    }

    Rectangle {
        id: icon_section
        anchors.bottom: parent.bottom
        height: footer_height
        width: parent.width
        color: grey_background_

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
            name: alert_icon_state ? "alert_on" : "alert_off"
            size: parent.height - elements_spacing_

            Connections {
                target: alertMessageModel
                function onUpdatedData() {
                    alert_icon_state = alertMessageModel.rowCount() > 0
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
                if (current_status === StatusLayout.Status.Collapsed) {
                    close_status_layout()
                }
                else {
                    collapse_status_layout()
                }
            }
        }
    }

    function filter_entity_status_log(entityId) {
        statusLayout.focus_entity_(entityId)
    }
}
