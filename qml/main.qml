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

import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Dialogs 1.2

import Theme 1.0

ApplicationWindow {
    id: mainApplicationView
    visible: true
    width: 1600
    height: 900
    title: qsTr("Fast DDS Monitor")

    signal startMonitoring

    // This property holds the current number of initialized monitors
    property int monitors: 0

    onStartMonitoring: {
        mainStartView.visible = false
        monitorMenuBar.visible = true
        toolBar.isVisible = true
        panels.visible = true
        dialogInitMonitor.open()
    }

    MainStartView {
        id: mainStartView
        visible: true
    }

    menuBar: MonitorMenuBar {
        id: monitorMenuBar
        visible: false
        onToolBarHidden: toolBar.isVisible = !toolBar.isVisible
        onDispDataButtonHidden: toolBar.isVisibleDispData = !toolBar.isVisibleDispData
        onDispDynDataButtonHidden: toolBar.isVisibleDispDynData = !toolBar.isVisibleDispDynData
        onRefreshButtonHidden: toolBar.isVisibleRefresh = !toolBar.isVisibleRefresh
        onClearLogButtonHidden: toolBar.isVisibleClearLog = !toolBar.isVisibleClearLog
        onDashboardLayoutButtonHidden: toolBar.isVisibleDashboardLayout = !toolBar.isVisibleDashboardLayout
        onClearIssuesButtonHidden: toolBar.isVisibleClearIssues = !toolBar.isVisibleClearIssues
        onLeftSidebarHidden: panels.openCloseLeftSideBar()
        onChangeChartboxLayout: {
            panels.changeChartboxLayout(chartsPerRow)
            toolBar.changeChartboxLayoutIcon(chartsPerRow)
        }
        onSaveAllCSV: {
            panels.saveAllCSV()
        }
        onExplorerDDSEntitiesChanged: panels.changeExplorerDDSEntities(status)
        onExplorerPhysicalChanged: panels.changeExplorerPhysical(status)
        onExplorerLogicalChanged: panels.changeExplorerLogical(status)
        onExplorerEntityInfoChanged: panels.changeExplorerEntityInfo(status)
    }

    header: MonitorToolBar {
        id: toolBar
        onChangeChartboxLayout: monitorMenuBar.changeChartboxLayoutViewMenu(chartsPerRow)
    }

    Panels {
        id: panels
        visible: false
        onExplorerDDSEntitiesChanged: monitorMenuBar.changeExplorerDDSEntities(status)
        onExplorerPhysicalChanged: monitorMenuBar.changeExplorerPhysical(status)
        onExplorerLogicalChanged: monitorMenuBar.changeExplorerLogical(status)
        onExplorerEntityInfoChanged: monitorMenuBar.changeExplorerEntityInfo(status)
    }

    InitMonitorDialog {
        id: dialogInitMonitor
    }

    InitDSMonitorDialog {
        id: dialogDSInitMonitor
    }

    InitMonitorWithProfileDialog {
        id: initMonitorWithProfileDialog
    }

    DumpFileDialog {
        id: dumpDialog
        clear: false
    }

    DumpFileDialog {
        id: dumpDialogClear
        clear: true
    }

    HistoricDataKindDialog {
        id: dataKindDialog
        onCreateChart: panels.createHistoricChart(dataKind)
    }

    DynamicDataKindDialog {
        id: dynamicDataKindDialog
        onCreateChart: panels.createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints)
    }

    ScheduleClearDialog {
        id: scheduleClear
    }

    AboutDialog {
        id: aboutDialog
    }

    ErrorDialog {
        id: errorDialog
    }

    SeriesSetMaxPointsDialog {
        id: seriesSetMaxPointsDialog
    }

    LoadXmlProfilesDialog {
        id: loadXmlProfilesDialog
    }

    // Creates a connection between Controller::error(QString, int) signal and ErrorDialog
    Connections {
        target: controller
        function onError(errorMsg, errorType) {
            errorDialog.text = errorMsg
            errorDialog.errorType = errorType
            errorDialog.open()
        }
    }

    // Creates a connection between Controller::monitorInitialized() signal and qml
    Connections {
        target: controller
        function onMonitorInitialized() {
            monitors++
        }
    }
}
