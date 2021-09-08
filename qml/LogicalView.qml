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
            property bool highlight: false
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
                    color: highlight ? Theme.eProsimaLightBlue : "transparent"

                    MouseArea {
                        anchors.fill: parent
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
                                lastClickedLogical(domainIdx, -1, name, kind)
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
                            color: entityLabelColor(highlight, alive)
                        }
                        Label {
                            text: name
                            color: entityLabelColor(highlight, alive)
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
                        property bool highlight: false

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
                                color: highlight ? Theme.eProsimaLightBlue : "transparent"

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if(mouse.button & Qt.RightButton) {
                                            openEntitiesMenu(id, name, kind)
                                        } else {
                                            controller.domain_click(id)
                                            lastClickedLogical(domainIdx, topicIdx, name, kind)
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
                                        color: entityLabelColor(highlight, alive)
                                    }
                                    Label {
                                        text: name
                                        color: entityLabelColor(highlight, alive)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    function updateLastEntityClicked(domainIdx, topicIdx, update = true) {
        if (lastClickedIdx[LogicalView.LogicalEntity.Domain] !== -1) {
            if (lastClickedIdx[LogicalView.LogicalEntity.Topic] !== -1) {
                domainList.itemAtIndex(lastClickedIdx[LogicalView.LogicalEntity.Domain])
                    .topicList.itemAtIndex(lastClickedIdx[LogicalView.LogicalEntity.Topic])
                        .highlight = !update
            } else if (domainList.itemAtIndex(lastClickedIdx[LogicalView.LogicalEntity.Domain]) !== null) {
                domainList.itemAtIndex(lastClickedIdx[LogicalView.LogicalEntity.Domain]).highlight = !update
            }
        }

        if (update) {
            lastClickedIdx = [domainIdx, topicIdx]
            updateLastEntityClicked(domainIdx, topicIdx, false)
        }
    }

    function resetLastEntityClicked() {
        updateLastEntityClicked(-1, -1, true)
    }
}
