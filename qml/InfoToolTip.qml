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

import QtQuick 6.10
import QtQuick.Controls 6.10
import Theme 1.0


/*
    Object to create information boxes about a Label.
    This box appears automatically when the mouse is hovered over the Label object that contains it.
    The text property defines the text to be displayed in the info box.
 */
Item {
    anchors.fill: parent
    // Text to show in the tooltip
    property string text: ""
    ToolTip {
        id: tooltip
        text: parent.text
        delay: 250
        visible: ma.containsMouse

        topMargin: 1 // avoid the ToolTip to exceed the parent top

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
        acceptedButtons: Qt.NoButton
    }
}
