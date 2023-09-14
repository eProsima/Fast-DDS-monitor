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

RowLayout {
    id: panels
    anchors.fill: parent
    spacing: 0

    property bool showLeftSidebar: true
    // This property save the state of the left sidebar after entering the full screen mode.
    // If is set to true, the left sidebar was opened, and false if it was closed.
    property bool prevFullScreenLeftSidebarState: true

    // private properties
    property int status_layout_height: status_layout_min_height_

    signal openCloseLeftSideBar
    signal changeChartboxLayout(int chartsPerRow)
    signal explorerDDSEntitiesChanged(bool status)
    signal explorerPhysicalChanged(bool status)
    signal explorerLogicalChanged(bool status)
    signal explorerEntityInfoChanged(bool status)

    // Read only design properties
    readonly property int status_layout_min_height_: 24


    onOpenCloseLeftSideBar: {
        if (panels.showLeftSidebar) {
            iconsVBar.iconClicked(iconsVBar.selected)
        } else {
            iconsVBar.iconClicked(0)
        }
    }
    onChangeChartboxLayout: {
        tabs.chartsLayout_boxesPerRow(chartsPerRow)
        tabs.chartsLayout_exitFullScreen()
    }

    IconsVBar {
        id: iconsVBar
        Layout.fillHeight: true
        width: 50

        onIconClicked: {
            if (panels.showLeftSidebar) {
                if (leftPanel.visiblePanel === leftPanel.panelItem[icon]) {
                    leftPanel.visiblePanel.visible = false
                    panels.showLeftSidebar = false
                    iconsVBar.updateSelectedSubPanel(icon, false)
                } else {
                    leftPanel.visiblePanel.visible = false
                    leftPanel.visiblePanel = leftPanel.panelItem[icon]
                    leftPanel.visiblePanel.visible = true
                    iconsVBar.updateSelectedSubPanel(icon, true)
                }
            } else {
                panels.showLeftSidebar = true
                leftPanel.visiblePanel = leftPanel.panelItem[icon]
                leftPanel.visiblePanel.visible = true
                iconsVBar.updateSelectedSubPanel(icon, true)
            }
        }
    }

    SplitView {
        id: panelsSplitView
        Layout.fillHeight: true
        Layout.fillWidth: true

        LeftPanel {
            id: leftPanel
            SplitView.preferredWidth: parent.width / 4
            SplitView.minimumWidth: parent.width / 6
            visible: panels.showLeftSidebar
            clip: true
            onExplorerDDSEntitiesChanged: panels.explorerDDSEntitiesChanged(status)
            onExplorerPhysicalChanged: panels.explorerPhysicalChanged(status)
            onExplorerLogicalChanged: panels.explorerLogicalChanged(status)
            onExplorerEntityInfoChanged: panels.explorerEntityInfoChanged(status)
        }

        Rectangle {
            SplitView.fillWidth: true

            SplitView {
                id: tabsSplitView
                anchors.fill: parent
                orientation: Qt.Vertical

                TabLayout {
                    id: tabs
                    SplitView.fillWidth: true
                    SplitView.fillHeight: true
                    SplitView.preferredHeight: parent.height - parent.height / 5
                    clip: true

                    onFullScreenChanged: {
                        if (fullScreen) {
                            if (showLeftSidebar) {
                                openCloseLeftSideBar()
                                prevFullScreenLeftSidebarState = true
                            } else {
                                prevFullScreenLeftSidebarState = false
                            }
                        } else {
                            if (!showLeftSidebar && prevFullScreenLeftSidebarState) {
                                openCloseLeftSideBar()
                            }
                        }
                    }
                    onOpenEntitiesMenu: {
                        panels.openEntitiesMenu(entityId, currentAlias, entityKind)
                    }
                    onOpenTopicMenu: {
                        panels.openTopicMenu(entityId, currentAlias, entityKind)
                    }
                }
                StatusLayout {
                    id: statusLayout
                    SplitView.preferredHeight: status_layout_height
                    SplitView.minimumHeight: status_layout_min_height_
                    clip: true
                    current_status: StatusLayout.Status.Collapsed
                    footer_height: status_layout_min_height_

                    onClose_status_layout: {
                        status_layout_height = status_layout_min_height_
                        statusLayout.current_status = StatusLayout.Status.Closed
                    }
                    onCollapse_status_layout: {
                        status_layout_height = tabsSplitView.height / 5
                        statusLayout.current_status = StatusLayout.Status.Collapsed
                    }
                    onExpand_status_layout: {
                        status_layout_height = tabsSplitView.height
                        statusLayout.current_status = StatusLayout.Status.Expanded
                    }
                }
            }
        }
    }

    function createHistoricChart(dataKind){
        tabs.chartsLayout_createHistoricChart(dataKind)
    }

    function createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints){
        tabs.chartsLayout_createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints)
    }

    function createScheduleClear(entities, data, updateData, updateClear){
        tabs.chartsLayout_createScheduleClear(entities, data, updateData, updateClear)
    }

    function saveAllCSV() {
        tabs.chartsLayout_saveAllCSV()
    }

    function changeExplorerDDSEntities(status) {
        leftPanel.changeExplorerDDSEntities(status)
    }

    function changeExplorerPhysical(status) {
        leftPanel.changeExplorerPhysical(status)
    }

    function changeExplorerLogical(status) {
        leftPanel.changeExplorerLogical(status)
    }

    function changeExplorerEntityInfo(status) {
        leftPanel.changeExplorerEntityInfo(status)
    }

    function openEntitiesMenu(entityId, currentAlias, entityKind) {
        leftPanel.openEntitiesMenu(entityId, currentAlias, entityKind)
    }

    function openTopicMenu(entityId, currentAlias, entityKind) {
        leftPanel.openTopicMenu(entityId, currentAlias, entityKind)
    }
}
