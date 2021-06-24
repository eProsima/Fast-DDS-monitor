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
import Theme 1.0

SplitView {
    id: rightPanels
    orientation: Qt.Vertical

    ColumnLayout {
        SplitView.fillHeight: true
        SplitView.minimumHeight: parent.height / 4
        spacing: 0

        TabBar {
            id: logViewTabBar
            TabButton {
                text: qsTr("Status")
            }
            TabButton {
                text: qsTr("Log")
            }
            TabButton {
                text: qsTr("Issues")
            }
            Layout.fillWidth: true
        }

        StackLayout {
            currentIndex: logViewTabBar.currentIndex
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true

            StatusView {
                id: statusView
            }

            LogView {
                id: logView
            }

            IssueView {
                id: issueView
            }
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
}
