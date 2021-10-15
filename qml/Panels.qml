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

    signal openCloseLeftSideBar
    signal changeChartboxLayout(int chartsPerRow)
    signal explorerDDSEntitiesChanged(bool status)
    signal explorerPhysicalChanged(bool status)
    signal explorerLogicalChanged(bool status)
    signal explorerEntityInfoChanged(bool status)

    onOpenCloseLeftSideBar: {
        if (panels.showLeftSidebar) {
            iconsVBar.iconClicked(iconsVBar.selected)
        } else {
            iconsVBar.iconClicked(0)
        }
    }
    onChangeChartboxLayout: {
        chartsLayout.boxesPerRow = chartsPerRow
        chartsLayout.exitFullScreen()
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

        ChartsLayout {
            id: chartsLayout
            SplitView.fillWidth: true
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
        }
    }

    function createHistoricChart(dataKind){
        chartsLayout.createHistoricChart(dataKind)
    }

    function createDynamicChart(dataKind, timeWindowSeconds, updatePeriod){
        chartsLayout.createDynamicChart(dataKind, timeWindowSeconds, updatePeriod)
    }

    function saveAllCSV() {
        chartsLayout.saveAllCSV()
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
}


