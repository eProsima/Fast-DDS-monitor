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
import QtQuick.Controls 2.15
import Theme 1.0

Item {
    anchors.fill: parent
    property string text: ""
    ToolTip {
        id: tooltip
        text: parent.text
        delay: 250
        visible: ma.containsMouse
        contentItem: Text{
            color: Theme.whiteSmoke
            text: tooltip.text
        }
        background: Rectangle {
            color: Theme.eProsimaLightBlue
            border.color: Theme.eProsimaLightBlue
        }
    }
    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
    }
}
