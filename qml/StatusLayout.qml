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
    property int current_status: Closed
    required property int footer_height

    // Public signals
    signal close_status_layout()
    signal expand_status_layout()
    signal collapse_status_layout()

    // Private properties
    property bool filter_visible_: true
    property int expand_btn_rotation_angle: expand_rotation_angle_

    // Private signals

    // Read only design properties (sizes and colors)
    readonly property int tabs_height_: 30
    readonly property int tabs_width_: 100
    readonly property int elements_spacing_: 8
    readonly property int separator_line_: 2
    readonly property string grey_background_: "#eaeaea"
    readonly property int expand_rotation_angle_: 90
    readonly property int collapse_rotation_angle_: -90


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

                /*Text {
                    anchors.top: parent.top; anchors.topMargin: elements_spacing_
                    anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                    text: "There are no issues"
                }

                ListView {
                    id: entityList
                    model: domainModel
                    delegate: entityListDelegate
                    clip: true
                    width: parent.width
                    height: parent.height
                    spacing: elements_spacing_
                    boundsBehavior: Flickable.StopAtBounds

                    ScrollBar.vertical: CustomScrollBar {
                        id: scrollBar
                    }

                    Component {
                        id: entityListDelegate

                        Item {
                            id: entityItem
                            width: entityList.width
                            height: entityListColumn.childrenRect.height

                            property var entityId: id
                            property var entityName: name
                            property int entityIdx: index
                            property var problemList: problemList

                            Column {
                                id: entityListColumn

                                Rectangle {
                                    id: entityHighlightRect
                                    width: statusLayout.width
                                    height: entityIcon.height

                                    MouseArea {
                                        anchors.fill: parent
                                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                                        onDoubleClicked: {
                                            if(problemList.height === problemList.collapseHeightFlag) {
                                                problemList.height = 0;
                                            } else {
                                                if (problemList.childrenRect.height != 0) {
                                                    problemList.height = problemList.collapseHeightFlag;
                                                }
                                            }
                                        }
                                        onClicked: {
                                            if(mouse.button & Qt.LeftButton) {
                                                //controller.domain_click(id)
                                            }
                                        }
                                    }

                                    RowLayout {
                                        spacing: spacingIconLabel

                                        IconSVG {
                                            id: entityIcon
                                            name: "issues"
                                            size: iconSize
                                            Layout.leftMargin: firstIndentation
                                        }
                                        Label {
                                            text: name
                                        }
                                    }
                                }

                                ListView {
                                    id: problemList
                                    model: entityList.model.subModelFromEntityId(entityId)
                                    width: entityList.width
                                    height: 0
                                    contentHeight: contentItem.childrenRect.height
                                    clip: true
                                    spacing: elements_spacing_
                                    topMargin: elements_spacing_
                                    delegate: problemListDelegate
                                    boundsBehavior: Flickable.StopAtBounds

                                    property int collapseHeightFlag: childrenRect.height + problemList.topMargin
                                }

                                Component {
                                    id: problemListDelegate

                                    Item {
                                        id: problemItem
                                        width: problemListColumn.width
                                        height: problemListColumn.childrenRect.height

                                        property int problemIdx: index

                                        ListView.onAdd: {
                                            if(problemList.height != 0) {
                                                problemList.height = problemList.collapseHeightFlag
                                            }
                                        }

                                        Column {
                                            id: problemListColumn

                                            Rectangle {
                                                id: problemHighlightRect
                                                width: statusLayout.width
                                                height: problemIcon.height

                                                MouseArea {
                                                    anchors.fill: parent
                                                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                                                    onClicked: {
                                                        if(mouse.button & Qt.RightButton) {
                                                            openTopicMenu(entityId, entityName, id, name, kind)
                                                        } else {
                                                            controller.problem_click(id)
                                                        }
                                                    }
                                                }

                                                RowLayout {
                                                    spacing: spacingIconLabel

                                                    IconSVG {
                                                        id: problemIcon
                                                        name: "issues"
                                                        size: iconSize
                                                        Layout.leftMargin: secondIndentation
                                                    }
                                                    Label {
                                                        text: name
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }*/

                TreeView {
                    id: status_tree_view
                    anchors.fill: parent
                    model: qosModel
                    selectionMode: SelectionMode.NoSelection
                    frameVisible: false
                    /*selection: ItemSelectionModel {
                        id: item_selection_model
                        model: qosModel
                    }*/
                    itemDelegate: Item {
                        Text {
                            anchors.fill: parent
                            elide: styleData.elideMode
                            text: styleData.value
                        }
                    }
                    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

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

                    Component.onCompleted: leftPanel.expandAll(qos_tree_view, qosModel)

                    Connections {
                        target: qosModel
                        function onUpdatedData() {
                            leftPanel.expandAll(qos_tree_view, qosModel)
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
                    id: rotation_rect
                    anchors.right: close_icon.left
                    anchors.rightMargin: elements_spacing_ *2
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.height - elements_spacing_
                    height: parent.height - elements_spacing_
                    transform: Rotation {
                        origin.x: rotation_rect.width/2
                        origin.y: rotation_rect.height/2
                        angle: expand_btn_rotation_angle
                    }
                    color: "transparent"

                    IconSVG {
                        id: expand_icon

                        name: "lessthan"
                        size: parent.width
                    }

                    MouseArea {
                        anchors.centerIn: parent
                        width: parent.width + 2*elements_spacing_
                        height: parent.height + 2*elements_spacing_

                        onClicked: {
                            if (statusLayout.current_status === StatusLayout.Status.Expanded)
                            {
                                expand_btn_rotation_angle = expand_rotation_angle_
                                collapse_status_layout()
                            }
                            else if (statusLayout.current_status === StatusLayout.Status.Collapsed)
                            {
                                expand_btn_rotation_angle = collapse_rotation_angle_
                                expand_status_layout()
                            }
                        }
                    }
                }

                IconSVG {
                    id: filter_icon
                    visible: statusLayout.filter_visible_
                    anchors.right: rotation_rect.left
                    anchors.rightMargin: elements_spacing_ *2
                    anchors.verticalCenter: parent.verticalCenter
                    name: "status"
                    size: parent.height - elements_spacing_
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

        IconSVG {
            id: error_icon
            anchors.left: parent.left
            anchors.leftMargin: elements_spacing_
            anchors.verticalCenter: parent.verticalCenter
            name: "cross"
            size: parent.height - elements_spacing_ -3
        }
        Label {
            id: error_value
            anchors.left: error_icon.right
            anchors.leftMargin: elements_spacing_/2
            anchors.verticalCenter: parent.verticalCenter
            text: "1"
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
            anchors.leftMargin: elements_spacing_/2
            anchors.verticalCenter: parent.verticalCenter
            text: "5"
        }
        IconSVG {
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
}
