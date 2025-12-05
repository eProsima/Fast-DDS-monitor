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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml.Models

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
    onChangeChartboxLayout: function(chartsPerRow) {
        tabs.chartsLayout_boxesPerRow(chartsPerRow)
        tabs.chartsLayout_exitFullScreen()
    }

    IconsVBar {
        id: iconsVBar
        Layout.fillHeight: true
        width: 50
                onIconClicked: function(icon) {
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
            onExplorerDDSEntitiesChanged: function(status) { panels.explorerDDSEntitiesChanged(status) }
            onExplorerPhysicalChanged: function(status) { panels.explorerPhysicalChanged(status) }
            onExplorerLogicalChanged: function(status) { panels.explorerLogicalChanged(status) }
            onExplorerEntityInfoChanged: function(status) { panels.explorerEntityInfoChanged(status) }
            onOpen_topic_view: function(domainEntityId, domainId, entityId) { tabs.open_topic_view(domainEntityId, domainId, entityId) }
            onRefresh_domain_graph_view: function(domainEntityId, entityId) { tabs.refresh_domain_graph_view(domainEntityId, entityId) }
            onFilter_entity_status_log: function(entityId) { statusLayout.filter_entity_status_log(entityId) }
            onOpen_idl_view: function(entityId) { tabs.open_idl_view(entityId) }
            onRemove_alert: function(alertId) { panels.removeAlert(alertId) }
            onOpen_spy_view: function(entityId) { tabs.open_spy_view(entityId) }
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
                    onOpenEntitiesMenu: function(domainEntityId, entityId, currentAlias, entityKind, caller) {
                        panels.openEntitiesMenu(domainEntityId, entityId, currentAlias, entityKind, caller)
                    }
                    onOpenTopicMenu: function(domainEntityId, domainId, entityId, currentAlias, entityKind, caller) {
                        panels.openTopicMenu(domainEntityId, domainId, entityId, currentAlias, entityKind, caller)
                    }
                    onOpenAlertsMenu: {
                        panels.openAlertsMenu(alertId)
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

    // Expose LeftPanel openMenuCaller enum to be used in other children components (e.g: DomainGraphView.qml)
    property alias openMenuCaller: leftPanel.openMenuCaller

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

    function openEntitiesMenu(domainEntityId, entityId, currentAlias, entityKind, caller) {
        leftPanel.openEntitiesMenu(domainEntityId, entityId, currentAlias, entityKind, caller)
    }

    function openTopicMenu(domainEntityId, domainId, entityId, currentAlias, entityKind, caller) {
        leftPanel.openTopicMenu(domainEntityId, domainId, entityId, currentAlias, entityKind, caller)
    }

    function openAlertsMenu(alertId) {
        leftPanel.openAlertsMenu(alertId)
    }

    function createAlert(name, domainId, hostId, userId, topicId, alert_type, t_between_triggers, threshold, alert_timeout, script_path){
        leftPanel.createAlert(name, domainId, hostId, userId, topicId, alert_type, t_between_triggers, threshold, alert_timeout, script_path)
    }

    function removeAlert(alertId){
        leftPanel.removeAlert(alertId)
    }
}
