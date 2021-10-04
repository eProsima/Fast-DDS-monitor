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
    id: logicalView
    Layout.fillHeight: true
    Layout.fillWidth: true

    enum LogicalEntity {
        Domain,
        Topic
    }

    property variant lastClickedIdx: [-1, -1]

    property variant knownDomains: []

    property int verticalSpacing: 5
    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel

    signal lastClickedLogical(int domainIdx, int topicIdx, string entityName, string entityKind)

    ListView {
        id: domainList
        model: domainModel
        delegate: domainListDelegate
        clip: true
        width: parent.width
        height: parent.height
        spacing: verticalSpacing

        ScrollBar.vertical: CustomScrollBar {
            id: scrollBar
        }
    }

    Component {
        id: domainListDelegate

        Item {
            id: domainItem
            width: domainList.width
            height: domainListColumn.childrenRect.height

            property var domainId: id
            property int domainIdx: index
            property var topicList: topicList

            ListView.onAdd: {
                if (knownDomains.indexOf(id) < 0) {
                    knownDomains.push(id)
                    lastClickedLogical(domainIdx, -1, name, kind)
                }
            }

            Column {
                id: domainListColumn

                Rectangle {
                    id: domainHighlightRect
                    width: logicalView.width
                    height: domainIcon.height
                    color: highligthRow(clicked)

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onDoubleClicked: {
                            if(topicList.height === topicList.collapseHeightFlag) {
                                topicList.height = 0;
                            } else {
                                if (topicList.childrenRect.height != 0) {
                                    topicList.height = topicList.collapseHeightFlag;
                                }
                            }
                        }
                        onClicked: {
                            if(mouse.button & Qt.RightButton) {
                                openEntitiesMenu(id, name, kind)
                            } else {
                                controller.domain_click(id)
                            }
                        }
                    }

                    RowLayout {
                        spacing: spacingIconLabel

                        IconSVG {
                            id: domainIcon
                            name: "domain"
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
                    id: topicList
                    model: domainList.model.subModelFromEntityId(domainId)
                    width: domainList.width
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    spacing: verticalSpacing
                    topMargin: verticalSpacing
                    delegate: topicListDelegate

                    property int collapseHeightFlag: childrenRect.height + topicList.topMargin
                }

                Component {
                    id: topicListDelegate

                    Item {
                        id: topicItem
                        width: parent.width
                        height: topicListColumn.childrenRect.height

                        property int topicIdx: index

                        ListView.onAdd: {
                            if(topicList.height != 0) {
                                topicList.height = topicList.collapseHeightFlag
                            }
                        }

                        Column {
                            id: topicListColumn

                            Rectangle {
                                id: topicHighlightRect
                                width: logicalView.width
                                height: topicIcon.height
                                color: highligthRow(clicked)

                                MouseArea {
                                    anchors.fill: parent
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                                    onClicked: {
                                        if(mouse.button & Qt.RightButton) {
                                            openEntitiesMenu(id, name, kind)
                                        } else {
                                            controller.topic_click(id)
                                        }
                                    }
                                }

                                RowLayout {
                                    spacing: spacingIconLabel

                                    IconSVG {
                                        id: topicIcon
                                        name: "topic"
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
                        }
                    }
                }
            }
        }
    }
}
