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
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12
import Theme 1.0

SplitView {
    id: leftPanels
    orientation: Qt.Vertical

    signal leftSidebarHidden

    property int viewsCount: 0
    property variant views: []
    property variant comboBoxIdx: []

    Component.onCompleted: {
        addView("ddsEntities")
        addView("physical")
        addView("logical")
    }

    Repeater {
        id: viewsRepeater
        model: viewsCount


        delegate: ColumnLayout {
            SplitView.preferredHeight: parent.height / 4
            SplitView.minimumHeight: settingsViewTabBar.height
            Layout.fillWidth: true

            visible: true

            property int comboBoxIndex: comboBoxIdx[index]
            property var listStackItem: listStack

            Rectangle {
                Layout.fillWidth: true
                height: settingsViewTabBar.height
                color: settingsViewTabBar.background.color

                RowLayout {
                    spacing: 0
                    anchors.left: parent.left
                    anchors.right: parent.right

                    ComboBox {
                        id: settingsViewTabBar
                        model: ["DDS Entities", "Physical", "Logical"]
                        Layout.fillWidth: true
                        currentIndex: comboBoxIndex
                        property int modelIdx: index
                        onActivated: {
                            comboBoxIdx[modelIdx] = currentIndex
                        }
                    }

                    Rectangle {
                        id: separator
                        height: settingsViewTabBar.height
                        width: 2
                        color: Theme.grey
                    }

                    Rectangle {
                        id: addSplitView
                        width: settingsViewTabBar.height/2
                        height: settingsViewTabBar.height/2
                        radius: settingsViewTabBar.height/2
                        Layout.alignment: Qt.AlignVCenter
                        Layout.leftMargin: settingsViewTabBar.height/5
                        Layout.rightMargin: settingsViewTabBar.height/5
                        color: Theme.lightGrey

                        IconSVG {
                            size: settingsViewTabBar.height/3
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            source: "/resources/images/plus.svg"
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                contextMenu.x = parent.x - settingsViewTabBar.height/5
                                contextMenu.y = parent.y + addSplitView.height/2 + settingsViewTabBar.height/2
                                contextMenu.open()
                            }
                            onEntered: {
                                parent.color = Theme.whiteSmoke
                            }
                            onExited: {
                                parent.color = Theme.lightGrey
                            }
                        }
                    }

                    Rectangle {
                        id: closeSplitView
                        width: settingsViewTabBar.height/2
                        height: settingsViewTabBar.height/2
                        radius: settingsViewTabBar.height/2
                        Layout.alignment: Qt.AlignVCenter
                        Layout.leftMargin: settingsViewTabBar.height/5
                        Layout.rightMargin: settingsViewTabBar.height/5
                        color: Theme.lightGrey


                        IconSVG {
                            size: settingsViewTabBar.height/3
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            source: index === 0 ? "/resources/images/lessthan.svg" : "/resources/images/cross.svg"
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                if (index == 0) {
                                    leftSidebarHidden()
                                } else {
                                    removeView(index)
                                }
                            }
                            onEntered: {
                                parent.color = Theme.whiteSmoke
                            }
                            onExited: {
                                parent.color = Theme.lightGrey
                            }
                        }
                    }
                }
            }

            Menu {
                id: contextMenu
                MenuItem {
                    text: "DDS Entities"
                    onTriggered: {
                        addView("ddsEntities")
                    }
                }
                MenuItem {
                    text: "Physical"
                    onTriggered: {
                        addView("physical")
                    }
                }
                MenuItem {
                    text: "Logical"
                    onTriggered: {
                        addView("logical")
                    }
                }
            }

            StackLayout {
                id: listStack
                currentIndex: settingsViewTabBar.currentIndex
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                property var entityListItem: entityList
                property var physicalViewItem: physicalView
                property var logicalViewItem: logicalView

                EntityList {
                    id: entityList
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }

                PhysicalView {
                    id: physicalView
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    onLastClickedPhysical: updateLastClickedPhysical(hostIdx, userIdx, processIdx)
                }

                LogicalView {
                    id: logicalView
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    onLastClickedLogical: updateLastClickedLogical(domainIdx, topicIdx)
                }
            }
        }
    }

    function updateLastClickedPhysical(hostIdx, userIdx, processIdx) {
        for(var i=0; i<viewsRepeater.count; i++){
            viewsRepeater.itemAt(i).listStackItem.entityListItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.logicalViewItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.physicalViewItem.updateLastEntityClicked(hostIdx, userIdx, processIdx)
        }
    }

    function updateLastClickedLogical(domainIdx, topicIdx) {
        for(var i=0; i<viewsRepeater.count; i++){
            viewsRepeater.itemAt(i).listStackItem.entityListItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.physicalViewItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.logicalViewItem.updateLastEntityClicked(domainIdx, topicIdx)
        }
    }

    function resetLastClicked() {
        for(var i=0; i<viewsRepeater.count; i++){
            viewsRepeater.itemAt(i).listStackItem.physicalViewItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.logicalViewItem.resetLastEntityClicked()
        }
    }

    function addView(viewKind) {
        views[viewsCount] = viewKind
        comboBoxIdx[viewsCount] = (viewKind === "ddsEntities") ? 0 :
                          (viewKind === "physical") ? 1 :
                          (viewKind === "logical") ? 2 : 0
        viewsCount++
    }

    function removeView(idx) {
        views.splice(idx, 1)
        comboBoxIdx.splice(idx, 1)
        viewsCount--
    }
}
