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
        Status,
        Issues
    }

    property variant panelItem: [monitoringPanel, statusPanel, issuesPanel]

    property variant visiblePanel: panelItem[LeftPanel.LeftSubPanel.Explorer]

    signal resetLastClicked()

    onResetLastClicked: monitoringPanel.resetLastClicked()

    MonitoringPanel {
        id: monitoringPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Explorer]) ? true : false
    }

    StatusPanel {
        id: statusPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Status]) ? true : false
    }

    ChangeAliasDialog {
        id: aliasDialog
    }

    EntitiesMenu {
        id: entitiesMenu
    }

    IssuesPanel {
        id: issuesPanel
        Layout.fillHeight: true
        visible: (visiblePanel ===  panelItem[LeftPanel.LeftSubPanel.Issues]) ? true : false
    }

    function changeAlias(entityId, currentAlias, entityKind) {
        aliasDialog.entityId = entityId
        aliasDialog.currentAlias = currentAlias
        aliasDialog.entityKind = entityKind
        aliasDialog.open()
    }

    function openEntitiesMenu(entityId, currentAlias, entityKind) {
        entitiesMenu.entityId = entityId
        entitiesMenu.currentAlias = currentAlias
        entitiesMenu.entityKind = entityKind
        entitiesMenu.popup()
    }

    function updateLastClickedPhysical(hostIdx, userIdx, processIdx) {
        for(var i=0; i<viewsRepeater.count; i++){
            viewsRepeater.itemAt(i).listStackItem.entityListItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.logicalViewItem.resetLastEntityClicked()
            viewsRepeater.itemAt(i).listStackItem.physicalViewItem.updateLastEntityClicked(hostIdx, userIdx, processIdx)
        }
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
}
