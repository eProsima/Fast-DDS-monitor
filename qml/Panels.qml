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

import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

RowLayout {
    id: panels
    anchors.fill: parent
    spacing: 0

    property bool showLeftSidebar: true

    signal lastClickedReset
    signal openCloseLeftSideBar
    signal changeChartboxLayout(int chartsPerRow)

    onLastClickedReset: leftPanel.resetLastClicked()
    onOpenCloseLeftSideBar: {
        if (panels.showLeftSidebar) {
            iconsVBar.iconClicked(iconsVBar.selected)
        } else {
            iconsVBar.iconClicked(0)
        }
    }
    onChangeChartboxLayout: chartsLayout.boxesPerRow = chartsPerRow

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
        }

        ChartsLayout {
            id: chartsLayout
            SplitView.fillWidth: true
            clip: true
        }
    }

    function createChart(dataKind){
        chartsLayout.createChart(dataKind)
    }

    function createDynamicChart(dataKind, timeWindowSeconds, updatePeriod){
        chartsLayout.createDynamicChart(dataKind, timeWindowSeconds, updatePeriod)
    }
}


