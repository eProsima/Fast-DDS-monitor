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

SplitView {
    id: panels
    anchors.fill: parent

    property bool showLeftSidebar: true
    property bool showRightSidebar: true

    signal lastClickedReset

    onLastClickedReset: leftPanel.resetLastClicked()

    LeftPanel {
        id: leftPanel
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6
        visible: showLeftSidebar
        onLeftSidebarHidden: panels.showLeftSidebar = false
        clip: true
    }

    ChartsLayout {
        id: chartsLayout
        SplitView.fillWidth: true
        clip: true
    }

    RightPanel {
        id: rightPanel
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6
        visible: showRightSidebar
        clip: true
    }

    function createChart(dataKind){
        chartsLayout.createChart(dataKind)
    }
}

