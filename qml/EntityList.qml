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

    property int verticalSpacing: 5
    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel
    property int thirdIndentation: secondIndentation + iconSize + spacingIconLabel

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
            property var endpointList: endpointList

            Column {
                id: participantListColumn

                Rectangle {
                    id: participantHighlightRect
                    width: entityList.width
                    height: participantIcon.height
                    color: highligthRow(clicked)

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onDoubleClicked: {
                            if(endpointList.height === endpointList.collapseHeightFlag) {
                                endpointList.height = 0;
                            } else {
                                if (endpointList.childrenRect.height != 0) {
                                    endpointList.height = endpointList.collapseHeightFlag;
                                }
                            }
                        }
                        onClicked: {
                            if(mouse.button & Qt.RightButton) {
                                openEntitiesMenu("", id, name, kind)
                            } else  {
                                controller.participant_click(id)
                            }
                        }
                    }

                    RowLayout {
                        spacing: spacingIconLabel

                        IconSVG {
                            id: participantIcon
                            name: "participant"
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
                                color: highligthRow(clicked)

                                MouseArea {
                                    anchors.fill: parent
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                                    onDoubleClicked: {
                                        if(locatorList.height === locatorList.collapseHeightFlag) {
                                            locatorList.height = 0;
                                            endpointList.height =
                                                    endpointList.height - locatorList.collapseHeightFlag;
                                        } else {
                                            if (locatorList.childrenRect.height != 0) {
                                                locatorList.height = locatorList.collapseHeightFlag;
                                                endpointList.height = endpointList.height + locatorList.height;
                                            }
                                        }
                                    }
                                    onClicked: {
                                        if(mouse.button & Qt.RightButton) {
                                            openEntitiesMenu("", id, name, kind)
                                        } else {
                                            controller.endpoint_click(id)
                                        }
                                    }
                                }

                                RowLayout {
                                    spacing: spacingIconLabel

                                    IconSVG {
                                        id: endpointIcon
                                        name: (kind == "DataReader") ? "datareader" : "datawriter"
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
                                            color: highligthRow(clicked)

                                            MouseArea {
                                                anchors.fill: parent
                                                acceptedButtons: Qt.LeftButton | Qt.RightButton

                                                onClicked: {
                                                    if(mouse.button & Qt.RightButton) {
                                                        openEntitiesMenu("", id, name, kind)
                                                    } else {
                                                        controller.locator_click(id)
                                                    }
                                                }
                                            }

                                            RowLayout {
                                                spacing: spacingIconLabel

                                                IconSVG {
                                                    id: locatorIcon
                                                    name: "locator"
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
