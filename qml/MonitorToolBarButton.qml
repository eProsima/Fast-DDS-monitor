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

import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8
import Theme 1.0

Rectangle {
    id: monitorToolBarButton
    height: 28
    width: 28
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
