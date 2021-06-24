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

        ScrollBar.vertical: ScrollBar { }
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

                    RowLayout {
                        spacing: spacingIconLabel

                        IconSVG {
                            id: domainIcon
                            source: "/resources/images/domain.svg"
                            size: iconSize
                            Layout.leftMargin: firstIndentation
                            dye: highlight ? true : false
                            color: highlight ? Theme.whiteSmoke : "black"

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if(topicList.height === topicList.collapseHeightFlag) {
                                        topicList.height = 0;
                                    }
                                    else {
                                        topicList.height = topicList.collapseHeightFlag;
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
                                    if(topicList.height === topicList.collapseHeightFlag) {
                                        topicList.height = 0;
                                    }
                                    else{
                                        topicList.height = topicList.collapseHeightFlag;
                                    }
                                }
                                onDoubleClick: {
                                    controller.domain_click(id)
                                    lastClickedLogical(domainIdx, -1, name, kind)
                                }
                            }
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
                        height: topicListColumn.childrenRect.height

                        property int topicIdx: index
                        property bool highlight: false

                        ListView.onAdd: {
                            if(topicList.height != 0) {
                                var prevHeight = topicList.height
                                topicList.height = topicList.collapseHeightFlag
                                domainList.height = domainList.height + topicList.height - prevHeight
                            }
                        }

                        Column {
                            id: topicListColumn

                            Rectangle {
                                id: topicHighlightRect
                                width: logicalView.width
                                height: topicIcon.height
                                color: highlight ? Theme.eProsimaLightBlue : "transparent"

                                RowLayout {
                                    spacing: spacingIconLabel

                                    IconSVG {
                                        id: topicIcon
                                        source: "/resources/images/topic.svg"
                                        size: iconSize
                                        Layout.leftMargin: secondIndentation
                                        dye: highlight ? true : false
                                        color: highlight ? Theme.whiteSmoke : "black"
                                    }
                                    Label {
                                        text: name
                                        color: highlight ? Theme.whiteSmoke : "black"

                                        MouseArea {
                                            anchors.fill: parent
                                            onDoubleClicked: {
                                                controller.domain_click(id)
                                                lastClickedLogical(domainIdx, topicIdx, name, kind)
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
