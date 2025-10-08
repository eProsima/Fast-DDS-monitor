// Copyright 2025 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.15
import Theme 1.0


Rectangle {

    id: alertListRect
    Layout.fillHeight: true
    Layout.fillWidth: true

    property int verticalSpacing: 5
    property int spacingIconLabel: 8
    property int iconSize: 18
    property int firstIndentation: 5
    property int secondIndentation: firstIndentation + iconSize + spacingIconLabel
    property int thirdIndentation: secondIndentation + iconSize + spacingIconLabel

    ListView {
        id: alertList
        model: alertModel
        delegate: alertListDelegate
        clip: true
        anchors.fill : parent
        spacing: verticalSpacing
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: CustomScrollBar {
            id: scrollBar
        }
    }

    Component {
        id: alertListDelegate

        Item {
            id: alertItem
            width: alertListRect.width
            height: alertHighlightRect.height
            property var alertId: id
            property int alertIdx: index

            Rectangle {

                id: alertHighlightRect
                width: alertList.width
                height: alertIcon.height
                color: clicked ? Theme.eProsimaLightBlue : "transparent"
                property bool clicked : false

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: {
                        alertHighlightRect.clicked = !alertHighlightRect.clicked
                        controller.alert_click(id)
                    }
                }

                RowLayout {
                    spacing: spacingIconLabel

                    IconSVG {
                        id: alertIcon
                        name: "alert"
                        size: iconSize
                        Layout.leftMargin: firstIndentation
                        color: entityLabelColor(alertHighlightRect.clicked, alive)
                    }
                    Label {
                        text: name
                        color: entityLabelColor(alertHighlightRect.clicked, alive)
                    }
                }
            }
        }
    }
}
