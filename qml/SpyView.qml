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

Item {
    id: spyView

    // Public properties
    property var model: {}                     // User Data JSON model
    property string domain_id                  // ID of the domain where the topic is
    property string topic_id                   // ID of the topic to spy

    // Private properties
    property bool is_active_: false            // Whether the spy is active or not

    // Read-only design properties
    readonly property int elements_spacing_: 10

    Flickable
    {
        id: userDataView
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
        anchors.fill: parent
        width: parent.width
        height: parent.height
        contentWidth: parent.width
        contentHeight: parent.height

        Rectangle {
            id: spyTopicData
            color: "blue"
            anchors.fill: parent
            anchors.margins: 10
        }

        Row {
            id: buttonContainer
            spacing: spyView.elements_spacing_
            anchors.top: parent.top; anchors.topMargin: 10
            anchors.right: parent.right; anchors.rightMargin: 10

            // TODO (Carlosspicur): Add button icons
            Button {
                id: copyButton
                text: "⧉"
                onClicked: {
                    console.log("Copy button clicked")
                }
            }

            Button {
                id: pausePlayButton
                text: "Pause/Play"
                onClicked: {
                    console.log("Pause/Play button clicked")
                    spyView.is_active_ = !spyView.is_active_
                    spyView.is_active_ ? controller.start_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
                                : controller.stop_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
                }
            }
        }
    }
}