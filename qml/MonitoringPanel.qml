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

/*
    Sidebar containing the DDS Entities, Logical, Physical, and Information elements of the backend entities.
 */
ColumnLayout {
    id: monitoringPanel
    spacing: 0

    Rectangle {
        Layout.fillWidth: true
        height: 20
        color: Theme.grey

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            spacing: 0
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            Label {
                text: "Explorer"
                Layout.preferredWidth: parent.width - parent.height
                color: Theme.whiteSmoke
            }
            IconSVG {
                source: "/resources/images/three_dots_menu.svg"
                Layout.alignment: Qt.AlignRight
                scalingFactor: 2
                dye: true
                color: Theme.whiteSmoke


                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        contextMenu.y = parent.y + parent.height;
                        contextMenu.open()
                    }
                }

                Menu {
                    id: contextMenu

                    Action {
                        text: "DDS Entities"
                        checkable: true
                        checked: true
                        onTriggered: entityListLayout.visible = checked
                    }
                    Action {
                        text: "Physical"
                        checkable: true
                        onTriggered: physicalViewLayout.visible = checked
                    }
                    Action {
                        text: "Logical"
                        checkable: true
                        onTriggered: logicalViewLayout.visible = checked
                    }
                    Action {
                        text: "Entity Info"
                        checkable: true
                        checked: true
                        onTriggered: entityInfo.visible = checked
                    }
                    delegate: MenuItem {
                        id: menuItem
                        implicitWidth: 150
                        implicitHeight: 30

                        indicator: Item {
                            implicitWidth: 30
                            implicitHeight: 30
                            Rectangle {
                                width: 16
                                height: 16
                                anchors.centerIn: parent
                                visible: menuItem.checkable
                                border.color: menuItem.highlighted ? Theme.eProsimaLightBlue :
                                              !menuItem.checked ? Theme.grey : "black"
                                radius: 3
                                Rectangle {
                                    width: 10
                                    height: 10
                                    anchors.centerIn: parent
                                    visible: menuItem.checked
                                    color: Theme.eProsimaLightBlue
                                    radius: 2
                                }
                            }
                        }

                        contentItem: Text {
                            leftPadding: 15
                            text: menuItem.text
                            opacity: enabled ? 1.0 : 0.3
                            color: menuItem.highlighted ? Theme.eProsimaLightBlue :
                                   !menuItem.checked ? Theme.grey : "black"
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true

        SplitView {
            orientation: Qt.Vertical
            anchors.fill: parent

            ColumnLayout {
                id: entityListLayout
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: entityListTitle.height
                spacing: 10
                visible: true
                clip: true

                Rectangle {
                    id: entityListTitle
                    Layout.fillWidth: true
                    height: infoTabBar.height
                    Label {
                        text: "DDS Entities"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Rectangle {
                        color: Theme.eProsimaLightBlue
                        height: 2
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                    }
                }

                EntityList {
                    id: entityList
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    Layout.bottomMargin: 1
                    onLastClickedDDSEntity: {
                        updateLastClickedDDSEntity(participantIdx, endpointIdx, locatorIdx)
                        infoSelectedEntityLabel.text = entityKind + ": " + entityName
                    }
                }
            }

            ColumnLayout {
                id: physicalViewLayout
                SplitView.fillHeight: true
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: physicalViewTitle.height
                spacing: 10
                visible: false
                clip: true

                Rectangle {
                    id: physicalViewTitle
                    Layout.fillWidth: true
                    height: infoTabBar.height
                    Label {
                        text: "Physical"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Rectangle {
                        color: Theme.eProsimaLightBlue
                        height: 2
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                    }
                }

                PhysicalView {
                    id: physicalView
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    Layout.bottomMargin: 1
                    onLastClickedPhysical: {
                        updateLastClickedPhysical(hostIdx, userIdx, processIdx)
                        infoSelectedEntityLabel.text = entityKind + ": " + entityName
                    }
                }
            }

            ColumnLayout {
                id: logicalViewLayout
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: logicalViewTitle.height
                spacing: 10
                visible: false
                clip: true

                Rectangle {
                    id: logicalViewTitle
                    Layout.fillWidth: true
                    height: infoTabBar.height
                    Label {
                        text: "Logical"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Rectangle {
                        color: Theme.eProsimaLightBlue
                        height: 2
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                    }
                }

                LogicalView {
                    id: logicalView
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    Layout.bottomMargin: 1
                    onLastClickedLogical: {
                        updateLastClickedLogical(domainIdx, topicIdx)
                        infoSelectedEntityLabel.text = entityKind + ": " + entityName
                    }
                }
            }

            ColumnLayout {
                id: entityInfo
                visible: true
                SplitView.fillHeight: true
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: infoTabBar.height
                spacing: 0
                clip: true

                TabBar {
                    id: infoTabBar
                    TabButton {
                        text: qsTr("Info")
                    }
                    TabButton {
                        text: qsTr("Statistics")
                    }
                    Layout.fillWidth: true
                }

                Rectangle {
                    id: infoSelectedEntity
                    Layout.fillWidth: true
                    height: infoTabBar.height
                    Label {
                        id: infoSelectedEntityLabel
                        text: "No entity selected"
                        font.pointSize: 10
                        font.italic: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                StackLayout {
                    currentIndex: infoTabBar.currentIndex
                    Layout.alignment: Qt.AlignTop
                    Layout.fillHeight: true

                    QosView {
                        id: qosView
                    }

                    SummaryView {
                        id: summaryView
                    }
                }
            }

        }
    }

    function updateLastClickedDDSEntity(participantIdx, endpointIdx, locatorIdx) {
        entityList.updateLastEntityClicked(participantIdx, endpointIdx, locatorIdx)
    }

    function updateLastClickedPhysical(hostIdx, userIdx, processIdx) {
        entityList.resetLastEntityClicked()
        logicalView.resetLastEntityClicked()
        physicalView.updateLastEntityClicked(hostIdx, userIdx, processIdx)
    }

    function updateLastClickedLogical(domainIdx, topicIdx) {
        entityList.resetLastEntityClicked()
        physicalView.resetLastEntityClicked()
        logicalView.updateLastEntityClicked(domainIdx, topicIdx)
    }

    function resetLastClicked() {
        entityList.resetLastEntityClicked()
        physicalView.resetLastEntityClicked()
        logicalView.resetLastEntityClicked()
        infoSelectedEntityLabel.text = "No entity selected"
    }
}
