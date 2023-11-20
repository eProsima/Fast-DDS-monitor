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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Theme 1.0

Rectangle {
    id: physicalView
    Layout.fillHeight: true
    Layout.fillWidth: true

    enum PhysicalEntity {
        Host,
        User,
        Process
    }

    property int verticalSpacing: 5
    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel
    property int thirdIndentation: secondIndentation + iconSize + spacingIconLabel

    ListView {
        id: hostList
        model: hostModel
        delegate: hostListDelegate
        clip: true
        width: parent.width
        height: parent.height
        spacing: verticalSpacing
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: CustomScrollBar {
            id: scrollBar
        }
    }

    Component {
        id: hostListDelegate

        Item {
            id: hostItem
            width: hostList.width
            height: hostListColumn.childrenRect.height

            property var hostId: id
            property int hostIdx: index
            property var userList: userList

            Column {
                id: hostListColumn

                Rectangle {
                    id: hostHighlightRect
                    width: physicalView.width
                    height: hostIcon.height
                    color: highligthRow(clicked)

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onDoubleClicked: {
                            if(userList.height === userList.collapseHeightFlag) {
                                userList.height = 0;
                            } else {
                                if (userList.childrenRect.height != 0) {
                                    userList.height = userList.collapseHeightFlag;
                                }
                            }
                        }
                        onClicked: {
                            if(mouse.button & Qt.RightButton) {
                                openEntitiesMenu("", id, name, kind)
                            } else {
                                controller.host_click(id)
                            }
                        }
                    }

                    RowLayout {
                        spacing: spacingIconLabel

                        IconSVG {
                            id: hostIcon
                            name: "host"
                            size: iconSize
                            Layout.leftMargin: firstIndentation
                            color: entityLabelColor(clicked, alive)
                        }
                        Label {
                            text: name
                            color: entityLabelColor(clicked, alive)
                        }
                    }
                }

                ListView {
                    id: userList
                    model: hostModel.subModelFromEntityId(hostId)
                    width: hostList.width
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    spacing: verticalSpacing
                    topMargin: verticalSpacing
                    delegate: userListDelegate
                    boundsBehavior: Flickable.StopAtBounds

                    property int collapseHeightFlag: childrenRect.height + userList.topMargin
                }

                Component {
                    id: userListDelegate

                    Item {
                        id: userItem
                        width: parent.width
                        height: userListColumn.childrenRect.height

                        property var userId: id
                        property int userIdx: index
                        property var processList: processList

                        ListView.onAdd: {
                            if(userList.height != 0) {
                                userList.height = userList.collapseHeightFlag;
                            }
                        }

                        Column {
                            id: userListColumn

                            Rectangle {
                                id: userHighlightRect
                                width: physicalView.width
                                height: userIcon.height
                                color: highligthRow(clicked)

                                MouseArea {
                                    anchors.fill: parent
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                                    onDoubleClicked: {
                                        if(processList.height === processList.collapseHeightFlag) {
                                            processList.height = 0;
                                            userList.height =
                                                    userList.height - processList.collapseHeightFlag;
                                        } else {
                                            if (processList.childrenRect.height != 0) {
                                                processList.height = processList.collapseHeightFlag;
                                                userList.height = userList.height + processList.height;
                                            }
                                        }
                                    }
                                    onClicked: {
                                        if(mouse.button & Qt.RightButton) {
                                            openEntitiesMenu("", id, name, kind)
                                        } else {
                                            controller.user_click(id)
                                        }
                                    }
                                }

                                RowLayout {
                                    spacing: spacingIconLabel

                                    IconSVG {
                                        id: userIcon
                                        name: "user"
                                        size: iconSize
                                        Layout.leftMargin: secondIndentation
                                        color: entityLabelColor(clicked, alive)
                                    }
                                    Label {
                                        text: name
                                        color: entityLabelColor(clicked, alive)
                                    }
                                }
                            }

                            ListView {
                                id: processList
                                model: userList.model.subModelFromEntityId(userId)
                                width: hostList.width
                                height: 0
                                contentHeight: contentItem.childrenRect.height
                                clip: true
                                delegate: processListDelegate
                                spacing: verticalSpacing
                                topMargin: verticalSpacing
                                boundsBehavior: Flickable.StopAtBounds

                                property int collapseHeightFlag: childrenRect.height + processList.topMargin
                            }

                            Component {
                                id: processListDelegate

                                Item {
                                    id: processItem
                                    width: parent.width
                                    height: processListColumn.childrenRect.height

                                    property int processIdx: index

                                    ListView.onAdd: {
                                        if(processList.height != 0) {
                                            var prevHeight = processList.height
                                            processList.height = processList.collapseHeightFlag
                                            userList.height = userList.height + processList.height - prevHeight
                                        }
                                    }

                                    Column {
                                        id: processListColumn

                                        Rectangle {
                                            id: processHighlightRect
                                            width: physicalView.width
                                            height: processIcon.height
                                            color: highligthRow(clicked)

                                            MouseArea {
                                                anchors.fill: parent
                                                acceptedButtons: Qt.LeftButton | Qt.RightButton

                                                onClicked: {
                                                    if(mouse.button & Qt.RightButton) {
                                                        openEntitiesMenu("", id, name, kind)
                                                    } else {
                                                        controller.process_click(id)
                                                    }
                                                }
                                            }

                                            RowLayout {
                                                spacing: spacingIconLabel

                                                IconSVG {
                                                    id: processIcon
                                                    name: "process"
                                                    size: iconSize
                                                    Layout.leftMargin: thirdIndentation
                                                    color: entityLabelColor(clicked, alive)
                                                }
                                                Label {
                                                    text: name
                                                    color: entityLabelColor(clicked, alive)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}
