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

    property variant lastClickedIdx: [-1, -1, -1]

    property int verticalSpacing: 5
    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel
    property int thirdIndentation: secondIndentation + iconSize + spacingIconLabel

    signal lastClickedPhysical(int hostIdx, int userIdx, int processIdx, string entityName, string entityKind)

    ListView {
        id: hostList
        model: hostModel
        delegate: hostListDelegate
        clip: true
        width: parent.width
        height: parent.height
        spacing: verticalSpacing

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
            property bool highlight: false
            property var userList: userList

            Column {
                id: hostListColumn

                Rectangle {
                    id: hostHighlightRect
                    width: physicalView.width
                    height: hostIcon.height
                    color: highlight ? Theme.eProsimaLightBlue : "transparent"

                    RowLayout {
                        spacing: spacingIconLabel

                        IconSVG {
                            id: hostIcon
                            name: "host"
                            size: iconSize
                            Layout.leftMargin: firstIndentation
                            color: entityLabelColor(highlight, alive)

                            DifferClickMouseArea {
                                anchors.fill: parent
                                onDoubleClick: {
                                    if(userList.height === userList.collapseHeightFlag) {
                                        userList.height = 0;
                                    }
                                    else{
                                        userList.height = userList.collapseHeightFlag;
                                    }
                                }
                                onSingleClick: {
                                    controller.host_click(id)
                                    lastClickedPhysical(hostIdx, -1, -1, name, kind)
                                }
                                onRightClick: {
                                    openEntitiesMenu(id, name, kind)
                                }
                            }
                        }
                        Label {
                            text: name
                            color: entityLabelColor(highlight, alive)

                            DifferClickMouseArea {
                                anchors.fill: parent
                                onDoubleClick: {
                                    if(userList.height === userList.collapseHeightFlag) {
                                        userList.height = 0;
                                    }
                                    else{
                                        userList.height = userList.collapseHeightFlag;
                                    }
                                }
                                onSingleClick: {
                                    controller.host_click(id)
                                    lastClickedPhysical(hostIdx, -1, -1, name, kind)
                                }
                                onRightClick: {
                                    openEntitiesMenu(id, name, kind)
                                }
                            }
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
                        property bool highlight: false
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
                                color: highlight ? Theme.eProsimaLightBlue : "transparent"

                                RowLayout {
                                    spacing: spacingIconLabel

                                    IconSVG {
                                        id: userIcon
                                        name: "user"
                                        size: iconSize
                                        Layout.leftMargin: secondIndentation
                                        color: entityLabelColor(highlight, alive)

                                        DifferClickMouseArea {
                                            anchors.fill: parent
                                            onDoubleClick: {
                                                if(processList.height === processList.collapseHeightFlag) {
                                                    processList.height = 0;
                                                    userList.height =
                                                            userList.height - processList.collapseHeightFlag;
                                                }
                                                else
                                                {
                                                    processList.height = processList.collapseHeightFlag;
                                                    userList.height = userList.height + processList.height;
                                                }
                                            }
                                            onSingleClick: {
                                                controller.user_click(id)
                                                lastClickedPhysical(hostIdx, userIdx, -1, name, kind)
                                            }
                                            onRightClick: {
                                                openEntitiesMenu(id, name, kind)
                                            }
                                        }
                                    }
                                    Label {
                                        text: name
                                        color: entityLabelColor(highlight, alive)

                                        DifferClickMouseArea {
                                            anchors.fill: parent
                                            onDoubleClick: {
                                                if(processList.height === processList.collapseHeightFlag) {
                                                    processList.height = 0;
                                                    userList.height =
                                                            userList.height - processList.collapseHeightFlag;
                                                }
                                                else
                                                {
                                                    processList.height = processList.collapseHeightFlag;
                                                    userList.height = userList.height + processList.height;
                                                }
                                            }
                                            onSingleClick: {
                                                controller.user_click(id)
                                                lastClickedPhysical(hostIdx, userIdx, -1, name, kind)
                                            }
                                            onRightClick: {
                                                openEntitiesMenu(id, name, kind)
                                            }
                                        }
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

                                property int collapseHeightFlag: childrenRect.height + processList.topMargin
                            }

                            Component {
                                id: processListDelegate

                                Item {
                                    id: processItem
                                    width: parent.width
                                    height: processListColumn.childrenRect.height

                                    property int processIdx: index
                                    property bool highlight: false

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
                                            color: highlight ? Theme.eProsimaLightBlue : "transparent"

                                            RowLayout {
                                                spacing: spacingIconLabel

                                                IconSVG {
                                                    id: processIcon
                                                    name: "process"
                                                    size: iconSize
                                                    Layout.leftMargin: thirdIndentation
                                                    color: entityLabelColor(highlight, alive)

                                                    DifferClickMouseArea {
                                                        anchors.fill: parent
                                                        onSingleClick: {
                                                            controller.process_click(id)
                                                            lastClickedPhysical(hostIdx, userIdx, processIdx, name, kind)
                                                        }
                                                        onRightClick: {
                                                            openEntitiesMenu(id, name, kind)
                                                        }
                                                    }
                                                }
                                                Label {
                                                    text: name
                                                    color: entityLabelColor(highlight, alive)

                                                    DifferClickMouseArea {
                                                        anchors.fill: parent
                                                        onSingleClick: {
                                                            controller.process_click(id)
                                                            lastClickedPhysical(hostIdx, userIdx, processIdx, name, kind)
                                                        }
                                                        onRightClick: {
                                                            openEntitiesMenu(id, name, kind)
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

    }

    function updateLastEntityClicked(hostIdx, userIdx, processIdx, update = true) {
        if (lastClickedIdx[PhysicalView.PhysicalEntity.Host] !== -1) {
            if (lastClickedIdx[PhysicalView.PhysicalEntity.User] !== -1) {
                if (lastClickedIdx[PhysicalView.PhysicalEntity.Process] !== -1) {
                    hostList.itemAtIndex(lastClickedIdx[PhysicalView.PhysicalEntity.Host])
                        .userList.itemAtIndex(lastClickedIdx[PhysicalView.PhysicalEntity.User])
                            .processList.itemAtIndex(lastClickedIdx[PhysicalView.PhysicalEntity.Process])
                                .highlight = !update
                } else {
                    hostList.itemAtIndex(lastClickedIdx[PhysicalView.PhysicalEntity.Host])
                        .userList.itemAtIndex(lastClickedIdx[PhysicalView.PhysicalEntity.User])
                            .highlight = !update
                }
            } else {
                hostList.itemAtIndex(lastClickedIdx[PhysicalView.PhysicalEntity.Host]).highlight = !update

            }
        }

        if (update) {
            lastClickedIdx = [hostIdx, userIdx, processIdx]
            updateLastEntityClicked(hostIdx, userIdx, processIdx, false)
        }
    }

    function resetLastEntityClicked() {
        updateLastEntityClicked(-1, -1, -1, true)
    }
}
