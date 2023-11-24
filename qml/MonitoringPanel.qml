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

    readonly property int logo_height_: 400
    readonly property int logo_width_: 1080
    readonly property int logo_margin_: 10

    signal explorerDDSEntitiesChanged(bool status)
    signal explorerPhysicalChanged(bool status)
    signal explorerLogicalChanged(bool status)
    signal explorerEntityInfoChanged(bool status)

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
                name: "three_dots_menu"
                Layout.alignment: Qt.AlignRight
                scalingFactor: 2
                color: "white"


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
                        id: contextMenuDDSEntities
                        text: "DDS Entities"
                        checkable: true
                        checked: true
                        onTriggered: {
                            entityListLayout.visible = checked
                            explorerDDSEntitiesChanged(checked)
                        }
                        onCheckedChanged: entityListLayout.visible = checked
                    }
                    Action {
                        id: contextMenuPhysical
                        text: "Physical"
                        checkable: true
                        onTriggered: {
                            physicalViewLayout.visible = checked
                            explorerPhysicalChanged(checked)
                        }
                        onCheckedChanged: physicalViewLayout.visible = checked
                    }
                    Action {
                        id: contextMenuLogical
                        text: "Logical"
                        checkable: true
                        onTriggered: {
                            logicalViewLayout.visible = checked
                            explorerLogicalChanged(checked)
                        }
                        onCheckedChanged: logicalViewLayout.visible = checked
                    }
                    Action {
                        id: contextMenuEntityInfo
                        text: "Entity Info"
                        checkable: true
                        checked: true
                        onTriggered: {
                            entityInfo.visible = checked
                            explorerEntityInfoChanged(checked)
                        }
                        onCheckedChanged: entityInfo.visible = checked
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
                }
            }

            Item {
                id: entityInfo
                visible: true
                SplitView.fillHeight: true
                SplitView.preferredHeight: parent.height / 4
                SplitView.minimumHeight: infoTabBar.height
                clip: true

                TabBar {
                    id: infoTabBar
                    anchors.top: parent.top
                    anchors.left: parent.left
                    width: parent.width
                    TabButton {
                        text: qsTr("Info")
                    }
                    TabButton {
                        text: qsTr("Statistics")
                    }
                }

                Rectangle {
                    id: infoSelectedEntity
                    property string app_id: "UNKNOWN_APP"
                    anchors.top: infoTabBar.bottom
                    anchors.left: parent.left
                    width: parent.width
                    height: infoTabBar.height

                    Rectangle {
                        id: app_logo_rect
                        visible: infoSelectedEntity.app_id != "UNKNOWN_APP"
                        anchors.top: parent.top
                        anchors.left: parent.left
                        width: parent.width
                        height: infoSelectedEntity.app_id != "UNKNOWN_APP" ? (parent.width * logo_height_)/logo_width_ : 0
                        color: "transparent"

                        Image {
                            id: app_logo
                            smooth: true
                            visible: parent.visible
                            source: infoSelectedEntity.app_id != "UNKNOWN_APP"
                                    ? "/resources/images/app_logos/" + infoSelectedEntity.app_id + ".png" : ""
                            anchors.top: parent.top
                            anchors.topMargin: logo_margin_
                            sourceSize.width: parent.width
                            sourceSize.height:parent.height
                        }
                    }

                    Rectangle
                    {
                        color: "transparent"
                        anchors.top: app_logo_rect.bottom
                        height: infoTabBar.height
                        width: parent.width

                        Label {
                            id: infoSelectedEntityLabel
                            text: "No entity selected"
                            font.pointSize: 10
                            font.italic: true
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }


                    Connections {
                        target: qosModel
                        function onEntitySelected(entityKind, entityAlias, entity_app_id) {
                            infoSelectedEntityLabel.text = (entityKind === "INVALID" || entityAlias === "")
                                    ? "No entity selected" : (entityKind.toUpperCase() + ": " + entityAlias)
                            infoSelectedEntity.app_id = entity_app_id
                            infoSelectedEntity.height = entity_app_id != "UNKNOWN_APP"
                                    ? infoTabBar.height + (parent.width * logo_height_)/logo_width_ : infoTabBar.height
                        }
                    }
                }

                StackLayout {
                    currentIndex: infoTabBar.currentIndex
                    anchors.top: infoSelectedEntity.bottom//; anchors.topMargin: -infoTabBar.height
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    width: parent.width

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

    function changeExplorerDDSEntities(status) {
        contextMenuDDSEntities.checked = status
    }

    function changeExplorerPhysical(status) {
        contextMenuPhysical.checked = status
    }

    function changeExplorerLogical(status) {
        contextMenuLogical.checked = status
    }

    function changeExplorerEntityInfo(status) {
        contextMenuEntityInfo.checked = status
    }

    function highligthRow(clicked) {
        return clicked ? Theme.eProsimaLightBlue : "transparent"
    }
}
