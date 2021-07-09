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
        onLastClickedReset: panels.lastClickedReset()
        onChangeChartboxLayout: {
            panels.changeChartboxLayout(chartsPerRow)
            toolBar.changeChartboxLayoutIcon(chartsPerRow)
        }
    }

    header: MonitorToolBar {
        id: toolBar
        onLastClickedReset: panels.lastClickedReset()
        onChangeChartboxLayout: monitorMenuBar.changeChartboxLayoutViewMenu(chartsPerRow)
    }

    Panels {
        id: panels
        visible: false
    }

    InitMonitorDialog {
        id: dialogInitMonitor
    }

    HistoricDataKindDialog {
        id: dataKindDialog
        onCreateChart: panels.createHistoricChart(dataKind)
    }

    DynamicDataKindDialog {
        id: dynamicDataKindDialog
        onCreateChart: panels.createDynamicChart(dataKind, timeWindowSeconds, updatePeriod)
    }

    AboutDialog {
        id: aboutDialog
    }

    ErrorDialog {
        id: errorDialog
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
}
