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

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

Item {
    id: statusView
    visible: true

    TreeView {
        id: statusTreeView
        anchors.fill: parent
        model: statusModel
        selectionMode: SelectionMode.NoSelection
        itemDelegate: Item {
            Text {
                anchors.fill: parent
                elide: styleData.elideMode
                text: styleData.value
            }
        }

        TableViewColumn {
            width: parent.width / 2
            role: "name"
            title: "Name"
        }

        TableViewColumn {
            width: parent.width / 2
            role: "value"
            title: "Value"
        }

        Component.onCompleted: leftPanel.expandAll(statusTreeView, statusModel)

        Connections {
            target: statusModel
            function onUpdatedData() {
                leftPanel.expandAll(statusTreeView, statusModel)
            }
        }
    }
}
