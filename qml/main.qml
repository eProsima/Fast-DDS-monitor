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
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtQuick.Dialogs

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
        onCreateAlertButtonHidden: toolBar.isVisibleCreateAlert = !toolBar.isVisibleCreateAlert
        onRefreshButtonHidden: toolBar.isVisibleRefresh = !toolBar.isVisibleRefresh
        onClearLogButtonHidden: toolBar.isVisibleClearLog = !toolBar.isVisibleClearLog
        onDashboardLayoutButtonHidden: toolBar.isVisibleDashboardLayout = !toolBar.isVisibleDashboardLayout
        onClearIssuesButtonHidden: toolBar.isVisibleClearIssues = !toolBar.isVisibleClearIssues
        onLeftSidebarHidden: panels.openCloseLeftSideBar()
        onChangeChartboxLayout: function(chartsPerRow) {
            panels.changeChartboxLayout(chartsPerRow)
            toolBar.changeChartboxLayoutIcon(chartsPerRow)
        }
        onSaveAllCSV: {
            panels.saveAllCSV()
        }
        onExplorerDDSEntitiesChanged: function(status) { panels.changeExplorerDDSEntities(status) }
        onExplorerPhysicalChanged: function(status) { panels.changeExplorerPhysical(status) }
        onExplorerLogicalChanged: function(status) { panels.changeExplorerLogical(status) }
        onExplorerEntityInfoChanged: function(status) { panels.changeExplorerEntityInfo(status) }
    }

    header: MonitorToolBar {
        id: toolBar
        onChangeChartboxLayout: function(chartsPerRow) { monitorMenuBar.changeChartboxLayoutViewMenu(chartsPerRow) }
    }

    Panels {
        id: panels
        visible: false
        onExplorerDDSEntitiesChanged: function(status) { monitorMenuBar.changeExplorerDDSEntities(status) }
        onExplorerPhysicalChanged: function(status) { monitorMenuBar.changeExplorerPhysical(status) }
        onExplorerLogicalChanged: function(status) { monitorMenuBar.changeExplorerLogical(status) }
        onExplorerEntityInfoChanged: function(status) { monitorMenuBar.changeExplorerEntityInfo(status) }
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
        onCreateChart: function(dataKind) {
            panels.createHistoricChart(dataKind)
        }
    }

    DynamicDataKindDialog {
        id: dynamicDataKindDialog
        onCreateChart: function(dataKind, timeWindowSeconds, updatePeriod, maxPoints) {
            panels.createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints)
        }
    }

    AlertDialog {
        id: alertDialog
        onCreateAlert: function(alert_name, domain_name, host_name, user_name, topic_name, alert_type,
                                t_between_triggers, threshold, alert_timeout, script_path) {
            panels.createAlert(alert_name, domain_name, host_name, user_name, topic_name, alert_type,
                            t_between_triggers, threshold, alert_timeout, script_path)
        }
    }

    AlertsSettingsDialog {
        id: alertsSettingsDialog
        onSetAlertsPollingTime: function(pollingTime) {
            controller.set_alerts_polling_time(pollingTime)
        }
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
