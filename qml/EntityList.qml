// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

        ScrollBar.vertical: ScrollBar { }
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
                            source: "/resources/images/participant.svg"
                            size: iconSize
                            Layout.leftMargin: firstIndentation
                            dye: highlight ? true : false
                            color: highlight ? Theme.whiteSmoke : "black"

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if(endpointList.height === endpointList.collapseHeightFlag) {
                                        endpointList.height = 0;
                                    }
                                    else {
                                        endpointList.height = endpointList.collapseHeightFlag;
                                    }
                                }
                            }
                        }
                        Label {
                            text: name
                            color: highlight ? Theme.whiteSmoke : "black"

                            DifferClickMouseArea {
                                anchors.fill: parent
                                onSingleClick: {
                                    if(endpointList.height === endpointList.collapseHeightFlag) {
                                        endpointList.height = 0;
                                    }
                                    else{
                                        endpointList.height = endpointList.collapseHeightFlag;
                                    }
                                }
                                onDoubleClick: {
                                    controller.participant_click(id)
                                    lastClickedDDSEntity(participantIdx, -1, -1, name, kind)
                                }
                                onRightClick: {
                                    changeAlias(id, name, kind)
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
                                        source: (kind == "DATAREADER") ? "/resources/images/datareader.svg" : "/resources/images/datawriter.svg"
                                        size: iconSize
                                        Layout.leftMargin: secondIndentation
                                        dye: highlight ? true : false
                                        color: highlight ? Theme.whiteSmoke : "black"

                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                if(locatorList.height === locatorList.collapseHeightFlag) {
                                                    locatorList.height = 0;
                                                    endpointList.height =
                                                            endpointList.height - locatorList.collapseHeightFlag;
                                                } else {
                                                    locatorList.height = locatorList.collapseHeightFlag;
                                                    endpointList.height = endpointList.height + locatorList.height;
                                                }
                                            }
                                        }
                                    }
                                    Label {
                                        text: name
                                        color: highlight ? Theme.whiteSmoke : "black"

                                        DifferClickMouseArea {
                                            anchors.fill: parent
                                            onSingleClick: {
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
                                            onDoubleClick: {
                                                controller.endpoint_click(id)
                                                lastClickedDDSEntity(participantIdx, endpointIdx, -1, name, kind)
                                            }
                                            onRightClick: {
                                                changeAlias(id, name, kind)
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
                                                    source: "/resources/images/locator.svg"
                                                    size: iconSize
                                                    Layout.leftMargin: thirdIndentation
                                                    dye: highlight ? true : false
                                                    color: highlight ? Theme.whiteSmoke : "black"
                                                }
                                                Label {
                                                    text: name
                                                    color: highlight ? Theme.whiteSmoke : "black"

                                                    DifferClickMouseArea {
                                                        anchors.fill: parent
                                                        onDoubleClicked: {
                                                            controller.locator_click(id)
                                                            lastClickedDDSEntity(participantIdx, endpointIdx, locatorIdx, name, kind)
                                                        }
                                                        onRightClick: {
                                                            changeAlias(id, name, kind)
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
