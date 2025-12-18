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

import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

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
    property int selectedIndex: -1

    ListView {
        id: alertList
        model: alertModel
        delegate: alertListDelegate
        clip: true
        anchors.fill: parent
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

            required property var id
            required property int index
            required property string name
            required property bool alive

            Rectangle {
                id: alertHighlightRect
                width: alertList.width
                height: alertIcon.height + 10
                color: alertListRect.selectedIndex === alertItem.index ? Theme.eProsimaLightBlue : "transparent"

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: function(mouse) {
                        if (mouse.button & Qt.RightButton) {
                            alertListRect.selectedIndex = alertItem.index
                            openAlertsMenu(alertItem.id)
                        } else {
                            if (alertListRect.selectedIndex === alertItem.index) {
                                alertListRect.selectedIndex = -1
                            } else {
                                alertListRect.selectedIndex = alertItem.index
                            }
                            controller.alert_click(alertItem.id)
                        }
                    }
                }

                RowLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: spacingIconLabel

                    IconSVG {
                        id: alertIcon
                        name: "alert"
                        size: iconSize
                        Layout.leftMargin: firstIndentation
                        color: entityLabelColor(alertListRect.selectedIndex === alertItem.index, alertItem.alive)
                    }

                    Label {
                        text: alertItem.name
                        color: entityLabelColor(alertListRect.selectedIndex === alertItem.index, alertItem.alive)
                    }
                }
            }
        }
    }
}
