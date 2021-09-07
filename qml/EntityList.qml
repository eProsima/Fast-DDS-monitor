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
    id: entityList
    Layout.fillHeight: true
    Layout.fillWidth: true

    enum DDSEntity {
        Participant,
        Endpoint,
        Locator
    }

    property variant lastClickedIdx: [-1, -1, -1]

    property int verticalSpacing: 5
    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel
    property int thirdIndentation: secondIndentation + iconSize + spacingIconLabel

    signal lastClickedDDSEntity(int participantIdx, int endpointIdx, int locatorIdx, string entityName, string entityKind)

    ListView {
        id: participantList
        model: participantModel
        delegate: participantListDelegate
        clip: true
        width: parent.width
        height: parent.height
        spacing: verticalSpacing

        ScrollBar.vertical: CustomScrollBar {
            id: scrollBar
        }
    }

    Component {
        id: participantListDelegate

        Item {
            id: participantItem
            width: participantList.width
            height: participantListColumn.childrenRect.height

            property var participantId: id
            property int participantIdx: index
            property bool highlight: false
            property var endpointList: endpointList

            Column {
                id: participantListColumn

                Rectangle {
                    id: participantHighlightRect
                    width: entityList.width
                    height: participantIcon.height
                    color: highlight ? Theme.eProsimaLightBlue : "transparent"

                    RowLayout {
                        spacing: spacingIconLabel

                        IconSVG {
                            id: participantIcon
                            name: "participant"
                            size: iconSize
                            Layout.leftMargin: firstIndentation
                            color: entityLabelColor(highlight, alive)

                            DifferClickMouseArea {
                                anchors.fill: parent
                                onDoubleClick: {
                                    if(endpointList.height === endpointList.collapseHeightFlag) {
                                        endpointList.height = 0;
                                    }
                                    else{
                                        endpointList.height = endpointList.collapseHeightFlag;
                                    }
                                }
                                onSingleClick: {
                                    controller.participant_click(id)
                                    lastClickedDDSEntity(participantIdx, -1, -1, name, kind)
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
                                    if(endpointList.height === endpointList.collapseHeightFlag) {
                                        endpointList.height = 0;
                                    }
                                    else{
                                        endpointList.height = endpointList.collapseHeightFlag;
                                    }
                                }
                                onSingleClick: {
                                    controller.participant_click(id)
                                    lastClickedDDSEntity(participantIdx, -1, -1, name, kind)
                                }
                                onRightClick: {
                                    openEntitiesMenu(id, name, kind)
                                }
                            }
                        }
                    }
                }

                ListView {
                    id: endpointList
                    model: participantModel.subModelFromEntityId(participantId)
                    width: participantList.width
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    spacing: verticalSpacing
                    topMargin: verticalSpacing
                    delegate: endpointListDelegate

                    property int collapseHeightFlag: childrenRect.height + endpointList.topMargin
                }

                Component {
                    id: endpointListDelegate

                    Item {
                        id: endpointItem
                        height: endpointListColumn.childrenRect.height

                        property var endpointId: id
                        property int endpointIdx: index
                        property bool highlight: false
                        property var locatorList: locatorList

                        ListView.onAdd: {
                            if(endpointList.height != 0) {
                                endpointList.height = endpointList.collapseHeightFlag;
                            }
                        }

                        Column {
                            id: endpointListColumn

                            Rectangle {
                                id: endpointHighlightRect
                                width: entityList.width
                                height: endpointIcon.height
                                color: highlight ? Theme.eProsimaLightBlue : "transparent"

                                RowLayout {
                                    spacing: spacingIconLabel

                                    IconSVG {
                                        id: endpointIcon
                                        name: (kind == "DataReader") ? "datareader" : "datawriter"
                                        size: iconSize
                                        Layout.leftMargin: secondIndentation
                                        color: entityLabelColor(highlight, alive)

                                        DifferClickMouseArea {
                                            anchors.fill: parent
                                            onDoubleClick: {
                                                if(locatorList.height === locatorList.collapseHeightFlag) {
                                                    locatorList.height = 0;
                                                    endpointList.height =
                                                            endpointList.height - locatorList.collapseHeightFlag;
                                                }
                                                else
                                                {
                                                    locatorList.height = locatorList.collapseHeightFlag;
                                                    endpointList.height = endpointList.height + locatorList.height;
                                                }
                                            }
                                            onSingleClick: {
                                                controller.endpoint_click(id)
                                                lastClickedDDSEntity(participantIdx, endpointIdx, -1, name, kind)
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
                                                if(locatorList.height === locatorList.collapseHeightFlag) {
                                                    locatorList.height = 0;
                                                    endpointList.height =
                                                            endpointList.height - locatorList.collapseHeightFlag;
                                                }
                                                else
                                                {
                                                    locatorList.height = locatorList.collapseHeightFlag;
                                                    endpointList.height = endpointList.height + locatorList.height;
                                                }
                                            }
                                            onSingleClick: {
                                                controller.endpoint_click(id)
                                                lastClickedDDSEntity(participantIdx, endpointIdx, -1, name, kind)
                                            }
                                            onRightClick: {
                                                openEntitiesMenu(id, name, kind)
                                            }
                                        }
                                    }
                                }
                            }

                            ListView {
                                id: locatorList
                                model: endpointList.model.subModelFromEntityId(endpointId)
                                width: participantList.width
                                height: 0
                                contentHeight: contentItem.childrenRect.height
                                clip: true
                                delegate: locatorListDelegate
                                spacing: verticalSpacing
                                topMargin: verticalSpacing

                                property int collapseHeightFlag: childrenRect.height + locatorList.topMargin
                            }

                            Component {
                                id: locatorListDelegate

                                Item {
                                    id: locatorItem
                                    width: parent.width
                                    height: locatorListColumn.childrenRect.height

                                    property int locatorIdx: index
                                    property bool highlight: false

                                    ListView.onAdd: {
                                        if(locatorList.height != 0) {
                                            var prevHeight = locatorList.height
                                            locatorList.height = locatorList.collapseHeightFlag
                                            endpointList.height = endpointList.height + locatorList.height - prevHeight
                                        }
                                    }

                                    Column {
                                        id: locatorListColumn

                                        Rectangle {
                                            id: locatorHighlightRect
                                            width: entityList.width
                                            height: locatorIcon.height
                                            color: highlight ? Theme.eProsimaLightBlue : "transparent"

                                            RowLayout {
                                                spacing: spacingIconLabel

                                                IconSVG {
                                                    id: locatorIcon
                                                    name: "locator"
                                                    size: iconSize
                                                    Layout.leftMargin: thirdIndentation
                                                    color: entityLabelColor(highlight, alive)

                                                    DifferClickMouseArea {
                                                        anchors.fill: parent
                                                        onSingleClick: {
                                                            controller.locator_click(id)
                                                            lastClickedDDSEntity(participantIdx, endpointIdx, locatorIdx, name, kind)
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
                                                            controller.locator_click(id)
                                                            lastClickedDDSEntity(participantIdx, endpointIdx, locatorIdx, name, kind)
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

    function updateLastEntityClicked(participantIdx, endpointIdx, locatorIdx, update = true) {
        if (lastClickedIdx[EntityList.DDSEntity.Participant] !== -1) {
            if (lastClickedIdx[EntityList.DDSEntity.Endpoint] !== -1) {
                if (lastClickedIdx[EntityList.DDSEntity.Locator] !== -1) {
                    participantList.itemAtIndex(lastClickedIdx[EntityList.DDSEntity.Participant])
                        .endpointList.itemAtIndex(lastClickedIdx[EntityList.DDSEntity.Endpoint])
                            .locatorList.itemAtIndex(lastClickedIdx[EntityList.DDSEntity.Locator])
                                .highlight = !update
                } else {
                    participantList.itemAtIndex(lastClickedIdx[EntityList.DDSEntity.Participant])
                        .endpointList.itemAtIndex(lastClickedIdx[EntityList.DDSEntity.Endpoint])
                            .highlight = !update
                }
            } else {
                participantList.itemAtIndex(lastClickedIdx[EntityList.DDSEntity.Participant]).highlight = !update

            }
        }

        if (update) {
            lastClickedIdx = [participantIdx, endpointIdx, locatorIdx]
            updateLastEntityClicked(participantIdx, endpointIdx, locatorIdx, false)
        }
    }

    function resetLastEntityClicked() {
        updateLastEntityClicked(-1, -1, -1, true)
    }
}
