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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.15

import Theme 1.0

Item
{
    id: statusLayout

    // Public properties
    enum Status {Closed, Expanded, Collapsed}
    property int current_status: StatusLayout.Status.Closed
    required property int footer_height

    // Public signals
    signal close_status_layout()
    signal expand_status_layout()
    signal collapse_status_layout()

    // Private properties
    property bool filter_visible_: false

    // Private signals
    signal focus_entity_(int entityId)
    signal clean_filter_()

    // Read only design properties (sizes and colors)
    readonly property int tabs_height_: 30
    readonly property int tabs_width_: 100
    readonly property int elements_spacing_: 8
    readonly property int separator_line_: 2
    readonly property string grey_background_: "#eaeaea"

    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel


    TabView {
        id: tab_view
        anchors.top: parent.top
        anchors.bottom: separator_line.top
        width: parent.width

        Tab {
            title: "Problems"
            Rectangle {

                color: "white"

                StatusTreeView {
                    id: status_tree_view
                    anchors.fill: parent
                    anchors.margins: 1

                    model: entityStatusModel

                    onEntity_status_filtered:{
                        collapse_status_layout()
                    }

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
        }
        style: TabViewStyle {
            frameOverlap: 1
            tab: Rectangle {
                color: styleData.selected ? "white" : Theme.lightGrey
                implicitWidth: Math.max(text.width + 10, tabs_width_)
                implicitHeight: tabs_height_
                radius: 4

                Rectangle {
                    width: parent.width
                    height: parent.height/2
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    color: parent.color
                }
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                }
            }
            tabBar: Rectangle {
                anchors.top: parent.top
                width: parent.width
                height: tabs_height_
                color: grey_background_

                IconSVG {
                    id: close_icon
                    anchors.right: parent.right
                    anchors.rightMargin: elements_spacing_ *2
                    anchors.verticalCenter: parent.verticalCenter
                    name: "cross"
                    size: parent.height - elements_spacing_ *3/2

                    MouseArea {
                        anchors.centerIn: parent
                        width: parent.width + 2*elements_spacing_
                        height: parent.height + 2*elements_spacing_

                        onClicked: {
                            close_status_layout()
                        }
                    }
                }

                Rectangle {
                    id: rect
                    anchors.right: close_icon.left
                    anchors.rightMargin: elements_spacing_ *2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: elements_spacing_/2
                    width: parent.height - elements_spacing_
                    height: parent.height - elements_spacing_
                    color: "transparent"

                    IconSVG {
                        id: expand_icon

                        name: "expand"
                        size: parent.width
                    }

                    MouseArea {
                        anchors.centerIn: parent
                        width: parent.width + 2*elements_spacing_
                        height: parent.height + 2*elements_spacing_

                        onClicked: {
                            if (statusLayout.current_status === StatusLayout.Status.Expanded)
                            {
                                collapse_status_layout()
                                expand_icon.name = "expand"

                            }
                            else if (statusLayout.current_status === StatusLayout.Status.Collapsed)
                            {
                                expand_status_layout()
                                expand_icon.name = "collapse"
                            }
                        }
                    }
                }

                Rectangle {
                    id: filter_rect
                    anchors.right: rect.left
                    anchors.rightMargin: elements_spacing_ *2
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height - elements_spacing_
                    width: parent.height - elements_spacing_
                    color: "transparent"

                    IconSVG {
                        id: filter_empty_icon
                        visible: !statusLayout.filter_visible_
                        anchors.centerIn: parent
                        name: "filter_empty"
                        size: parent.width
                    }

                    IconSVG {
                        id: filter_full_icon
                        visible: statusLayout.filter_visible_
                        anchors.centerIn: parent
                        name: "filter_full"
                        size: parent.width
                    }

                    MouseArea {
                        id: filter_btn
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

        Component.onCompleted: { close_status_layout() }

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
            anchors.leftMargin: elements_spacing_/2
            anchors.verticalCenter: parent.verticalCenter
            text: "0"
        }
        IconSVG {
            id: warning_icon
            anchors.left: error_icon.right
            anchors.leftMargin: elements_spacing_ * 4
            anchors.verticalCenter: parent.verticalCenter
            name: "issues"
            size: parent.height - elements_spacing_
        }
        Label {
            id: warning_value
            anchors.left: warning_icon.right
            anchors.leftMargin: elements_spacing_/2
            anchors.verticalCenter: parent.verticalCenter
            text: "0"
        }

        Connections
        {
            target: controller
            function onUpdate_status_counters(errors, warnings) {
                error_value.text = errors
                warning_value.text = warnings
            }
        }
        /*IconSVG {
            id: info_icon
            anchors.left: warning_value.right
            anchors.leftMargin: elements_spacing_
            name: "info"
            size: parent.height - elements_spacing_ -1
            anchors.verticalCenter: parent.verticalCenter
        }
        Label {
            id: info_value
            anchors.left: info_icon.right
            anchors.leftMargin: elements_spacing_/2
            anchors.verticalCenter: parent.verticalCenter
            text: "19"
        }*/
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
