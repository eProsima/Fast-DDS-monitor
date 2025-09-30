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

RowLayout {
    id: leftPanel
    height: parent.height
    spacing: 0

    enum LeftSubPanel {
        Explorer,
        Alerts,
        Status,
        Issues
    }

    // Enum exposed in Panels.qml for Menu items message customization
    readonly property var openMenuCaller: ({
        leftPanel: 0,
        domainGraph: 1
    })

    property variant panelItem: [monitoringPanel, alertsPanel, statusPanel, issuesPanel]

    property variant visiblePanel: panelItem[LeftPanel.LeftSubPanel.Explorer]

    signal explorerDDSEntitiesChanged(bool status)
    signal explorerPhysicalChanged(bool status)
    signal explorerLogicalChanged(bool status)
    signal explorerEntityInfoChanged(bool status)
    signal open_topic_view(string domainEntityId, string domainId, string entityId)
    signal open_idl_view(string entityId)
    signal open_spy_view(string domainId, string entityId)
    signal refresh_domain_graph_view(string domainEntityId, string entityId)
    signal filter_entity_status_log(string entityId)
    signal remove_alert(string alertId)

    MonitoringPanel {
        id: monitoringPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Explorer]) ? true : false
        onExplorerDDSEntitiesChanged: leftPanel.explorerDDSEntitiesChanged(status)
        onExplorerPhysicalChanged: leftPanel.explorerPhysicalChanged(status)
        onExplorerLogicalChanged: leftPanel.explorerLogicalChanged(status)
        onExplorerEntityInfoChanged: leftPanel.explorerEntityInfoChanged(status)
    }

    StatusPanel {
        id: statusPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Status]) ? true : false
    }

    AlertsPanel {
        id: alertsPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Alerts]) ? true : false
    }

    ChangeAliasDialog {
        id: aliasDialog
    }

    EntitiesMenu {
        id: entitiesMenu
        onChangeAlias: leftPanel.changeAlias(domainEntityId, entityId, currentAlias, entityKind)
        onFilterEntityStatusLog: leftPanel.filterEntityStatusLog(entityId)
        onOpenTopicView: leftPanel.openTopicView(domainEntityId, domainId, topicId)
    }

    AlertsMenu {
        id: alertsMenu
        onRemoveAlert: leftPanel.removeAlert(alertsMenu.alertId)
    }

    TopicMenu {
        id: topicMenu
    }

    IssuesPanel {
        id: issuesPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Issues]) ? true : false
    }

    function changeAlias(domainEntityId, entityId, currentAlias, entityKind) {
        aliasDialog.domainEntityId = domainEntityId
        aliasDialog.entityId = entityId
        aliasDialog.currentAlias = currentAlias
        aliasDialog.entityKind = entityKind
        aliasDialog.open()
    }

    function openAlertDialogWithTopic(domainEntityId, topicId) {
        alertDialog.open_with_topic(domainEntityId, topicId)
    }

    function openEntitiesMenu(domainEntityId, entityId, currentAlias, entityKind, caller) {
        entitiesMenu.domainEntityId = domainEntityId
        entitiesMenu.entityId = entityId
        entitiesMenu.currentAlias = currentAlias
        entitiesMenu.entityKind = entityKind

        if (caller === openMenuCaller.domainGraph) {
            entitiesMenu.showGraphButtonName = "Filter topic graph"
        }
        else {
            entitiesMenu.showGraphButtonName = "Show topic graph"
        }

        entitiesMenu.popup()
    }

    function openAlertsMenu(alertId) {
        alertsMenu.alertId = alertId
        alertsMenu.popup()
    }

    function openTopicMenu(domainEntityId, domainId, entityId, currentAlias, entityKind, caller) {
        topicMenu.domainEntityId = domainEntityId
        topicMenu.domainId = domainId
        topicMenu.entityId = entityId
        topicMenu.currentAlias = currentAlias
        topicMenu.entityKind = entityKind

        if (caller === openMenuCaller.domainGraph) {
            topicMenu.showGraphButtonName = "Filter topic graph"
        }
        else {
            topicMenu.showGraphButtonName = "Show topic graph"
        }

        topicMenu.popup()
    }

    function openTopicView(domainEntityId, domainId, entityId) {
        leftPanel.open_topic_view(domainEntityId, domainId, entityId)
    }

    function openIDLView(entityId) {
        leftPanel.open_idl_view(entityId)
    }

    function openSpyView(domainId, entityId) {
        // __FLAG__
        console.log("[openSpyView] domainId: " + domainId + " entityId: " + entityId)
        /////////////////////
        leftPanel.open_spy_view(domainId, entityId)
    }

    function refreshDomainGraphView(domainEntityId, entityId) {
        leftPanel.refresh_domain_graph_view(domainEntityId, entityId)
    }
    function filterEntityStatusLog(entityId){
        leftPanel.filter_entity_status_log(entityId)
    }

    function expandAll(view, model) {
        for(var i=0; i < model.rowCount(); i++) {
            var index = model.index(i, 0)
            if (!view.isExpanded(index)) {
                view.expand(index)
            }
            if (model.rowCount(index) > 0) {
                expandChilds(view, model, index)
            }
        }
    }

    function expandChilds(view, model, parent) {
        for(var i=0; i < model.rowCount(parent); i++) {
            var index = model.index(i, 0, parent)
            if (!view.isExpanded(index)) {
                view.expand(index)
            }
            if (model.rowCount(index) > 0) {
                expandChilds(view, model, index)
            }
        }
    }

    function entityLabelColor(highlight, alive) {
        return highlight ? "white" :
               alive ? "black" : "grey"
    }

    function changeExplorerDDSEntities(status) {
        monitoringPanel.changeExplorerDDSEntities(status)
    }

    function changeExplorerPhysical(status) {
        monitoringPanel.changeExplorerPhysical(status)
    }

    function changeExplorerLogical(status) {
        monitoringPanel.changeExplorerLogical(status)
    }

    function changeExplorerEntityInfo(status) {
        monitoringPanel.changeExplorerEntityInfo(status)
    }

    function createAlert(name, domainId, hostId, userId, topicId, alert_type, t_between_triggers, threshold, alert_timeout, script_path) {
        controller.set_alert(name, domainId, hostId, userId, topicId, alert_type, threshold, t_between_triggers, alert_timeout, script_path);
    }

    function removeAlert(alertId) {
        controller.remove_alert(alertId)
    }
}
