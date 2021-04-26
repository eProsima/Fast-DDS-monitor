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

import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Rectangle {
    id: physicalView
    Layout.fillHeight: true
    Layout.fillWidth: true

    ListView {
        id: hostList
        model: hostModel
        delegate: hostListDelegate
        clip: true
        leftMargin: 5
        bottomMargin: 5
        width: parent.width
        height: parent.height

        ScrollBar.vertical: ScrollBar { }
    }

    Component {
        id: hostListDelegate

        Item {
            id: hostItem
            width: hostList.width - hostList.leftMargin
            height: hostListColumn.childrenRect.height

            property var item_id: id

            Column {
                id: hostListColumn

                RowLayout {
                    spacing: 8

                    IconSVG {
                        source: "/resources/images/host.svg"
                        scalingFactor: 1.5
                        Layout.bottomMargin: 5
                    }
                    Label {
                        text: name
                        Layout.bottomMargin: 5

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(userList.height === userList.collapseHeightFlag) {
                                    userList.height = 0;
                                }
                                else{
                                    userList.height = userList.collapseHeightFlag;
                                }
                            }
                            onDoubleClicked: {
                                controller.host_click(id)
                            }
                        }
                    }
                }
                ListView {
                    id: userList
                    model: hostModel.subModelFromEntityId(id)
                    leftMargin: 25
                    width: hostList.width - hostList.leftMargin
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    delegate: userListDelegate

                    property int collapseHeightFlag: childrenRect.height
                }

                Component {
                    id: userListDelegate

                    Item {
                        width: parent.width
                        height: userListColumn.childrenRect.height

                        ListView.onAdd: {
                            if(userList.height != 0) {
                                userList.height = userList.collapseHeightFlag;
                            }
                        }

                        Column {
                            id: userListColumn

                            RowLayout {
                                spacing: 8

                                IconSVG {
                                    source: "/resources/images/user.svg"
                                    scalingFactor: 1.5
                                    Layout.bottomMargin: 5
                                }
                                Label {
                                    text: name
                                    Layout.bottomMargin: 5

                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
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
                                        onDoubleClicked: {
                                            controller.host_click(id)
                                        }
                                    }
                                }
                            }
                            ListView {
                                id: processList
                                model: hostModel.subModelFromEntityId(
                                           hostItem.item_id).subModelFromEntityId(id)
                                leftMargin: 25
                                width: hostList.width - hostList.leftMargin
                                height: 0
                                contentHeight: contentItem.childrenRect.height
                                clip: true
                                delegate: processListDelegate

                                property int collapseHeightFlag: childrenRect.height
                            }

                            Component {
                                id: processListDelegate
                                Item {
                                    width: parent.width
                                    height: processListColumn.childrenRect.height

                                    ListView.onAdd: {
                                        if(processList.height != 0) {
                                            var prevHeight = processList.height
                                            processList.height = processList.collapseHeightFlag
                                            userList.height = userList.height + processList.height - prevHeight
                                        }
                                    }

                                    Column {
                                        id: processListColumn
                                        anchors.left: parent.left
                                        anchors.right: parent.right

                                        RowLayout {
                                            spacing: 8

                                            IconSVG {
                                                source: "/resources/images/process.svg"
                                                scalingFactor: 1.5
                                                Layout.bottomMargin: 5
                                            }
                                            Label {
                                                text: name
                                                Layout.bottomMargin: 5

                                                MouseArea {
                                                    anchors.fill: parent
                                                    onDoubleClicked: {
                                                        controller.host_click(id)
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
