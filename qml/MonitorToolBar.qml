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

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

ToolBar {
    id: toolBar

    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: "Init new monitor"
            onClicked: {
                dialogInitMonitor.open()
            }
        }

        ToolSeparator {}

        ToolButton {
            text: "Display new data"
            onClicked: {
                dataKindDialog.open()
            }
        }

        ToolSeparator {}

        ToolButton {
            text: "Refresh"
            onClicked: {
                controller.refresh_click()
            }
        }

        ToolSeparator {}

        Item {
            Layout.fillWidth: true
        }
    }
}
