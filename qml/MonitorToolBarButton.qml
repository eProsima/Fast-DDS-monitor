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
import QtQuick.Layouts 1.1
import Theme 1.0

Rectangle {
    id: monitorToolBarButton
    height: 23
    width: 23
    radius: 5
    Layout.alignment: Qt.AlignVCenter
    color: mouseArea.containsMouse ? Theme.grey : "transparent"

    property string iconName: ""
    property string tooltipText: ""

    signal clicked(variant mouse)

    ToolTip {
        id: tooltip
        text: parent.tooltipText
        delay: 250
        visible: mouseArea.containsMouse
        contentItem: Text{
            color: Theme.whiteSmoke
            text: tooltip.text
        }
        background: Rectangle {
            color: Theme.eProsimaLightBlue
            border.color: Theme.eProsimaLightBlue
        }
    }

    IconSVG {
        id: icon
        name: iconName
        size: parent.width - 6
        anchors.centerIn: parent
        color: mouseArea.containsMouse ? "white" : "black"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    Connections {
        target: mouseArea
        function onClicked(mouse) {
            monitorToolBarButton.clicked(mouse)
        }
    }
}
