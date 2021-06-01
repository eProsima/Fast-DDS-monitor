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
        toolBar.visible = true
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
        onInitMonitorButtonHidden: toolBar.isVisibleInitMonitor = !toolBar.isVisibleInitMonitor
        onDispDataButtonHidden: toolBar.isVisibleDispData = !toolBar.isVisibleDispData
        onRefreshButtonHidden: toolBar.isVisibleRefresh = !toolBar.isVisibleRefresh
        onLeftSidebarHidden: panels.showLeftSidebar = !panels.showLeftSidebar
        onRightSidebarHidden: panels.showRightSidebar = !panels.showRightSidebar
        onLastClickedReset: panels.lastClickedReset()
    }

    header: MonitorToolBar {
        id: toolBar
        visible: false
        onLastClickedReset: panels.lastClickedReset()
    }

    Panels {
        id: panels
        visible: false
    }

    InitMonitorDialog {
        id: dialogInitMonitor
    }

    DataKindDialog {
        id: dataKindDialog
        onCreateChart: panels.createChart(dataKind)
    }

    AboutDialog {
        id: aboutDialog
    }
}
