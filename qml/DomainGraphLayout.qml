// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

import Theme 1.0

Item
{
    id: domainGraphLayout

    // Public properties
    property var model: {}
    property int entity_id: 0                       // entity id associated to the domain id
    property int domain_id: 0                       // domain id

    // Public signals
    signal update_tab_name(string new_name)

    // Private properties
    property var topic_locations_: {}
    property var endpoint_topic_connections_: {}
    property int max_host_width_: 0
    property int max_user_width_: 0
    property int max_process_width_: 0
    property int max_participant_width_: 0
    property int max_endpoint_width_: 0
    property var entity_painted_: []
    property var topic_painted_: []

    // Private signals
    signal resize_elements_()
    signal topics_updated_()
    signal endpoints_updated_()
    signal participants_updated_()
    signal processes_updated_()
    signal users_updated_()
    signal hosts_updated_()

    // Read only design properties
    readonly property int radius_: 10
    readonly property int connection_thickness_: 5
    readonly property int elements_spacing_: 12
    readonly property int endpoint_height_: 40
    readonly property int first_indentation_: 5
    readonly property int icon_size_: 18
    readonly property int label_height_: 35
    readonly property int spacing_icon_label_: 8
    readonly property int scrollbar_min_size_: 8
    readonly property int scrollbar_max_size_: 12
    readonly property int topic_thickness_: 10
    readonly property string topic_color_: Theme.grey
    readonly property string host_color_: Theme.darkGrey
    readonly property string user_color_: Theme.eProsimaLightBlue
    readonly property string process_color_: Theme.eProsimaDarkBlue
    readonly property string participant_color_: Theme.vulcanexusBlue
    readonly property string reader_color_: Theme.eProsimaYellow
    readonly property string writer_color_: Theme.eProsimaGreen

    Component.onCompleted:
    {
        load_model()
    }

    Flickable {
        id: topicView
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.leftMargin: max_host_width_ + elements_spacing_;
        width: parent.width - max_host_width_ - elements_spacing_
        flickableDirection: Flickable.HorizontalFlick
        boundsBehavior: Flickable.StopAtBounds

        contentWidth: topicsList.contentWidth + 100
        contentHeight: parent.height

        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOff }
        ScrollBar.horizontal: ScrollBar {
            id: horizontal_bar
            anchors.left: parent.left;
            anchors.bottom: parent.bottom
            policy: ScrollBar.AlwaysOn
            visible: topicView.contentWidth > topicView.width
            hoverEnabled: true

            contentItem: Item {
                implicitHeight: scrollbar_min_size_

                Rectangle {
                    anchors.fill: parent
                    anchors.rightMargin: scrollbar_max_size_
                    anchors.leftMargin: 1
                    anchors.topMargin: 2
                    anchors.bottomMargin: 2
                    radius: height / 2
                    color: horizontal_bar.pressed ? Theme.eProsimaLightBlue : Theme.lightGrey
                }
            }

            background: Item {
                implicitHeight: scrollbar_max_size_

                Rectangle {
                    anchors.fill: parent
                    color: horizontal_bar.pressed ? Theme.lightGrey : Theme.grey
                }
            }
        }

        ListView
        {
            id: topicsList
            model: domainGraphLayout.model["topics"]
            anchors.left: parent.left; anchors.leftMargin: 2 * elements_spacing_
            anchors.top: parent.top; anchors.topMargin: elements_spacing_;
            anchors.bottom: parent.bottom;  anchors.bottomMargin: scrollbar_max_size_+ elements_spacing_
            contentWidth: contentItem.childrenRect.width
            spacing: elements_spacing_
            orientation: ListView.Horizontal
            interactive: false

            Connections
            {
                target: domainGraphLayout

                function onResize_elements_()
                {
                    topicsList.onCountChanged()
                }
            }

            onCountChanged:
            {
                var listViewHeight = 0
                var listViewWidth = 0

                // iterate over each element in the list item
                for (var i = 0; i < topicsList.visibleChildren.length; i++) {
                    listViewHeight = topicsList.visibleChildren[i].height
                    listViewWidth += topicsList.visibleChildren[i].width
                }

                for (var c = 0; c < topicsList.count; c++)
                {
                    topicsList.currentIndex = c
                    var globalCoordinates = topicsList.currentItem.mapToItem(mainSpace, 0, 0)
                    topic_locations_[topicsList.currentItem.topic_id] = {
                        "id": topicsList.currentItem.topic_id,
                        "x" : globalCoordinates.x + (topicsList.currentItem.width/2)
                    }
                }
                topicsList.height = listViewHeight
                topicsList.width = listViewWidth + 10* elements_spacing_
                topics_updated_()
            }

            delegate: Rectangle
            {
                property string topic_id: modelData["id"]
                implicitWidth: topic_tag.implicitWidth
                height: topicsList.height
                color: "transparent"


                Rectangle
                {
                    id: topic_tag
                    implicitWidth: topicRowLayout.implicitWidth
                    height: label_height_
                    color: topic_color_
                    radius: radius_

                    RowLayout {
                        id: topicRowLayout
                        spacing: spacing_icon_label_
                        anchors.centerIn: parent

                        IconSVG {
                            name: "topic"
                            color: "white"
                            size: icon_size_
                            Layout.leftMargin: first_indentation_
                        }
                        Label {
                            text: modelData["alias"]
                            Layout.rightMargin: first_indentation_
                            color: "white"
                        }
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            console.log(modelData["alias"] + " clicked!")
                        }
                    }
                }

                Rectangle
                {
                    id: topic_down_bar
                    anchors.top: topic_tag.bottom
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: topic_tag.horizontalCenter
                    width: topic_thickness_
                    color: topic_color_
                }
            }
        }

        Flickable
        {
            id: topicSpace
            anchors.top: parent.top; anchors.topMargin: label_height_ + 2* elements_spacing_
            anchors.left: parent.left
            width: parent.width
            height: parent.height - (label_height_ + 2* elements_spacing_)
            interactive: false
            clip: true

            contentWidth: topicsList.contentWidth + 100
            contentHeight: mainView.contentHeight
            Rectangle {id: topic_connections; anchors.fill:parent; color: "transparent" }


            ScrollBar.vertical: ScrollBar{
                id: custom_bar
                width: 0

                Connections {
                    target: vertical_bar

                    function onPositionChanged(){
                        custom_bar.position = vertical_bar.position
                    }
                }
            }

            MouseArea {
                anchors.fill: parent

                onWheel: {
                    if (wheel.angleDelta.y > 0) {
                        topicView.contentX -= 30// topicView.scrollSpeed;
                        if (topicView.contentX < 0) {
                            topicView.contentX = 0;
                        }
                    } else {
                        topicView.contentX += 30// topicView.scrollSpeed;
                        if (topicView.contentX + topicView.width > topicView.contentWidth) {
                            topicView.contentX = topicView.contentWidth -  topicView.width;
                        }
                    }
                }
                onClicked: mouse.accepted = false;
                onPressed: mouse.accepted = false;
                onReleased: mouse.accepted = false;
                onDoubleClicked: mouse.accepted = false;
                onPositionChanged: mouse.accepted = false;
                onPressAndHold: mouse.accepted = false;
            }

        }

        Connections
        {
            target: domainGraphLayout

            function onTopics_updated_()
            {
                topicView.create_connections()
            }

            function onEndpoints_updated_()
            {
                topicView.create_connections()
            }

            function onParticipants_updated_()
            {
                topicView.create_connections()
            }

            function onProcesses_updated_()
            {
                topicView.create_connections()
            }

            function onUsers_updated_()
            {
                topicView.create_connections()
            }

            function onHosts_updated_()
            {
                topicView.create_connections()
            }
        }

        function create_connections()
        {
            for (var key in endpoint_topic_connections_)
            {
                var topic_id = endpoint_topic_connections_[key]["destination_id"]
                if (topic_locations_[topic_id] != undefined)
                {
                    if (!topic_painted_.includes(key))
                    {
                        //console.log(key)
                        //console.log(endpoint_topic_connections_[key]["y"])
                        var destination_x = topic_locations_[topic_id]["x"]
                        var input = {"x": 0
                            ,"right_direction": endpoint_topic_connections_[key]["right_direction"]
                            ,"y": endpoint_topic_connections_[key]["y"] - (connection_thickness_ / 2)
                            ,"width": destination_x - endpoint_topic_connections_[key]["x"] - 4*elements_spacing_
                            ,"height":connection_thickness_, "z":200, "left_margin": 2*elements_spacing_
                            ,"arrow_color": topic_color_, "background_color": background_color.color }
                        var connection_bar = arrow_component.createObject(topic_connections, input)
                        topic_painted_[topic_painted_.length] = key;
                    }
                }
            }
        }
    }

    Flickable {
        id: mainView
        anchors.left: parent.left ; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: max_host_width_ + elements_spacing_
        anchors.topMargin: 2* elements_spacing_ + label_height_
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        z: 10

        contentWidth: mainSpace.width
        contentHeight: mainSpace.height

        ScrollBar.horizontal: ScrollBar { policy: ScrollBar.AlwaysOff }
        ScrollBar.vertical: ScrollBar {
            id: vertical_bar
            policy: ScrollBar.AlwaysOn
            visible: mainView.contentHeight > mainView.height
            anchors.top: parent.top;        anchors.topMargin: -elements_spacing_
            anchors.right: parent.right;    anchors.rightMargin: parent.width - domainGraphLayout.width
            hoverEnabled: true
            z: 20

            contentItem: Item {
                implicitWidth: scrollbar_min_size_

                Rectangle {
                    anchors.fill: parent
                    anchors.topMargin: 1
                    anchors.rightMargin: 2
                    anchors.leftMargin: 2
                    radius: width / 2
                    color: vertical_bar.pressed ? Theme.eProsimaLightBlue : Theme.lightGrey
                }
            }

            background: Item {
                implicitWidth: scrollbar_max_size_

                Rectangle {
                    anchors.fill: parent
                    color: vertical_bar.pressed ? Theme.lightGrey : Theme.grey
                }
            }

            Rectangle {
                anchors.top: parent.top
                height: 1
                width: parent.width
                color: vertical_bar.pressed ? Theme.lightGrey : Theme.grey
            }
        }


        Rectangle
        {
            id: mainSpace
            anchors.top: parent.top

            width: hostsList.width
            height: hostsList.height < domainGraphLayout.height - (label_height_ + 2*elements_spacing_)
                ? domainGraphLayout.height - (label_height_ + 2*elements_spacing_) : hostsList.height

            Rectangle {
                id: background_color
                anchors.fill: parent
                color: "white"
            }

            Component {
                id: arrow_component
                GraphConnection{

                }
            }

            ListView
            {
                id: hostsList
                model: domainGraphLayout.model["hosts"]
                anchors.top: parent.top
                anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                interactive: false
                spacing: elements_spacing_
                z: 20

                Connections
                {
                    target: domainGraphLayout

                    function onUsers_updated_()
                    {
                        hostsList.onCountChanged()
                    }
                }

                onCountChanged:
                {
                    var listViewHeight = 0
                    var listViewWidth = 0

                    // iterate over each element in the list item
                    for (var i = 0; i < hostsList.visibleChildren.length; i++) {
                        var min_width = hostsList.visibleChildren[i].width
                        for (var j = 0; j < hostsList.visibleChildren[i].visibleChildren.length; j++)
                        {
                            min_width = Math.max(min_width, hostsList.visibleChildren[i].visibleChildren[j].width)
                        }
                        listViewWidth  = Math.max(listViewWidth, min_width)
                        max_host_width_ = Math.max(max_host_width_, listViewWidth)
                        max_host_width_ = Math.max(max_host_width_, (2*elements_spacing_)+max_user_width_)
                        hostsList.visibleChildren[i].width = max_host_width_
                    }

                    for (var c = 0; c < hostsList.count; c++)
                    {
                        hostsList.currentIndex = c
                        if (hostsList.currentItem != null)
                        {
                            listViewHeight += hostsList.currentItem.height + elements_spacing_
                        }
                    }

                    hostsList.height = listViewHeight + elements_spacing_
                    hostsList.width = max_host_width_
                    hosts_updated_()
                }

                delegate: Item
                {
                    height: host_tag.height + usersList.height
                    width: hostRowLayout.implicitWidth > max_host_width_
                        ? hostRowLayout.implicitWidth
                        : max_host_width_ == 0
                            ? hostRowLayout.implicitWidth
                            : max_host_width_

                    Rectangle
                    {
                        id: host_background
                        height: parent.height
                        width: parent.width
                        color: host_color_
                        radius: radius_
                    }

                    Rectangle
                    {
                        id: host_tag
                        anchors.horizontalCenter: parent.horizontalCenter
                        implicitWidth: hostRowLayout.implicitWidth > max_host_width_
                            ? hostRowLayout.implicitWidth
                            : max_host_width_ == 0
                                ? hostRowLayout.implicitWidth
                                : max_host_width_
                        height: label_height_
                        color: host_color_
                        radius: radius_

                        RowLayout {
                            id: hostRowLayout
                            anchors.centerIn: parent

                            IconSVG {
                                visible: modelData["status"] != "ok"
                                name: "issues"
                                color: "white"
                                size: icon_size_
                                Layout.leftMargin: first_indentation_
                            }
                            IconSVG {
                                name: "host"
                                color: "white"
                                size: icon_size_
                                Layout.leftMargin: modelData["status"] != "ok" ? 0 : first_indentation_
                            }
                            Label {
                                text: modelData["alias"]
                                Layout.rightMargin: first_indentation_
                                color: "white"
                            }
                        }
                        Rectangle {
                            visible: host_tag.implicitWidth < max_host_width_
                            anchors.left: host_tag.right
                            anchors.verticalCenter: parent.verticalCenter
                            height: host_tag.height
                            width: max_host_width_ - host_tag.implicitWidth
                            color: host_background.color
                            radius: radius_
                        }
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked:
                            {
                                console.log(modelData["alias"] + " clicked!")
                            }
                        }
                    }

                    ListView
                    {
                        id: usersList
                        model: modelData["users"]
                        anchors.top: host_tag.bottom; anchors.topMargin: elements_spacing_
                        anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                        anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                        interactive: false
                        spacing: elements_spacing_

                        Connections
                        {
                            target: domainGraphLayout

                            function onProcesses_updated_()
                            {
                                usersList.onCountChanged()
                            }
                        }

                        onCountChanged:
                        {
                            var listViewHeight = 0
                            var listViewWidth = 0

                            // iterate over each element in the list item
                            for (var i = 0; i < usersList.visibleChildren.length; i++) {
                                var min_width = usersList.visibleChildren[i].width
                                for (var j = 0; j < usersList.visibleChildren[i].visibleChildren.length; j++)
                                {
                                    min_width = Math.max(min_width, usersList.visibleChildren[i].visibleChildren[j].width)
                                }
                                listViewWidth  = Math.max(listViewWidth, min_width)
                                max_user_width_ = Math.max(max_user_width_, listViewWidth)
                                max_user_width_ = Math.max(max_user_width_, (2*elements_spacing_)+max_process_width_)
                                usersList.visibleChildren[i].width = max_user_width_
                            }

                            for (var c = 0; c < usersList.count; c++)
                            {
                                usersList.currentIndex = c
                                if (usersList.currentItem != null)
                                {
                                    listViewHeight += usersList.currentItem.height + elements_spacing_
                                }
                            }

                            usersList.height = listViewHeight + elements_spacing_
                            usersList.width = max_user_width_
                            users_updated_()
                        }

                        delegate: Item
                        {
                            height: user_tag.height + processesList.height
                            width: userRowLayout.implicitWidth > max_user_width_
                                ? userRowLayout.implicitWidth
                                : max_user_width_ == 0
                                    ? userRowLayout.implicitWidth
                                    : max_user_width_

                            Rectangle
                            {
                                id: user_background
                                height: parent.height
                                width: parent.width
                                color: user_color_
                                radius: radius_
                            }

                            Rectangle
                            {
                                id: user_tag
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                                implicitWidth: userRowLayout.implicitWidth > max_user_width_
                                    ? userRowLayout.implicitWidth
                                    : max_user_width_ == 0
                                        ? userRowLayout.implicitWidth
                                        : max_user_width_
                                height: label_height_
                                color: user_color_
                                radius: radius_

                                RowLayout {
                                    id: userRowLayout
                                    anchors.centerIn: parent

                                    IconSVG {
                                        visible: modelData["status"] != "ok"
                                        name: "issues"
                                        color: "white"
                                        size: icon_size_
                                        Layout.leftMargin: first_indentation_
                                    }
                                    IconSVG {
                                        name: "user"
                                        color: "white"
                                        size: icon_size_
                                        Layout.leftMargin: modelData["status"] != "ok" ? 0 : first_indentation_
                                    }
                                    Label {
                                        text: modelData["alias"]
                                        Layout.rightMargin: first_indentation_
                                        color: "white"
                                    }
                                }
                                Rectangle {
                                    visible: user_tag.implicitWidth < max_user_width_
                                    anchors.left: user_tag.right
                                    anchors.verticalCenter: parent.verticalCenter
                                    height: user_tag.height
                                    width: max_user_width_ - user_tag.implicitWidth
                                    color: user_background.color
                                    radius: radius_
                                }
                                MouseArea
                                {
                                    anchors.fill: parent
                                    onClicked:
                                    {
                                        console.log(modelData["alias"] + " clicked!")
                                    }
                                }
                            }

                            ListView
                            {
                                id: processesList
                                model: modelData["processes"]
                                anchors.top: user_tag.bottom; anchors.topMargin: elements_spacing_
                                anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                                anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                                interactive: false
                                spacing: elements_spacing_

                                Connections
                                {
                                    target: domainGraphLayout

                                    function onParticipants_updated_()
                                    {
                                        processesList.onCountChanged()
                                    }
                                }

                                onCountChanged:
                                {
                                    var listViewHeight = 0
                                    var listViewWidth = 0

                                    // iterate over each element in the list item
                                    for (var i = 0; i < processesList.visibleChildren.length; i++) {
                                        listViewHeight += processesList.visibleChildren[i].height + elements_spacing_
                                        var min_width = processesList.visibleChildren[i].width
                                        for (var j = 0; j < processesList.visibleChildren[i].visibleChildren.length; j++)
                                        {
                                            min_width = Math.max(min_width, processesList.visibleChildren[i].visibleChildren[j].width)
                                        }
                                        listViewWidth  = Math.max(listViewWidth, min_width)
                                        max_process_width_ = Math.max(max_process_width_, listViewWidth)
                                        max_process_width_ = Math.max(max_process_width_, (2*elements_spacing_)+max_participant_width_)
                                        processesList.visibleChildren[i].width = max_process_width_
                                    }

                                    processesList.height = listViewHeight + elements_spacing_
                                    processesList.width = max_process_width_
                                    processes_updated_()
                                }

                                delegate: Item
                                {
                                    height: process_tag.height + participantsList.height
                                    width: processRowLayout.implicitWidth > max_process_width_
                                        ? processRowLayout.implicitWidth
                                        : max_process_width_ == 0
                                            ? processRowLayout.implicitWidth
                                            : max_process_width_

                                    Rectangle
                                    {
                                        id: process_background
                                        height: parent.height
                                        width: parent.width
                                        color: process_color_
                                        radius: radius_
                                    }

                                    Rectangle
                                    {
                                        id: process_tag
                                        anchors.top: parent.top
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        implicitWidth: processRowLayout.implicitWidth > max_process_width_
                                            ? processRowLayout.implicitWidth
                                            : max_process_width_ == 0
                                                ? processRowLayout.implicitWidth
                                                : max_process_width_
                                        height: label_height_
                                        color: process_color_
                                        radius: radius_

                                        RowLayout {
                                            id: processRowLayout
                                            anchors.centerIn: parent

                                            IconSVG {
                                                visible: modelData["status"] != "ok"
                                                name: "issues"
                                                color: "white"
                                                size: icon_size_
                                                Layout.leftMargin: first_indentation_
                                            }
                                            IconSVG {
                                                name: "process"
                                                color: "white"
                                                size: icon_size_
                                                Layout.leftMargin: modelData["status"] != "ok" ? 0 : first_indentation_
                                            }
                                            Label {
                                                text: modelData["alias"]
                                                Layout.rightMargin: first_indentation_
                                                color: "white"
                                            }
                                        }
                                        Rectangle {
                                            visible: process_tag.implicitWidth < max_process_width_
                                            anchors.left: process_tag.right
                                            anchors.verticalCenter: parent.verticalCenter
                                            height: process_tag.height
                                            width: max_process_width_ - process_tag.implicitWidth
                                            color: process_background.color
                                            radius: radius_
                                        }
                                        MouseArea
                                        {
                                            anchors.fill: parent
                                            onClicked:
                                            {
                                                console.log(modelData["alias"] + " clicked!")
                                            }
                                        }
                                    }
                                    ListView
                                    {
                                        id: participantsList
                                        model: modelData["participants"]
                                        anchors.top: process_tag.bottom; anchors.topMargin: elements_spacing_
                                        anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                                        anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                                        interactive: false
                                        spacing: elements_spacing_

                                        Connections
                                        {
                                            target: domainGraphLayout

                                            function onEndpoints_updated_()
                                            {
                                                participantsList.onCountChanged()
                                            }
                                        }

                                        onCountChanged:
                                        {
                                            var listViewHeight = 0
                                            var listViewWidth = 0

                                            // iterate over each element in the list item
                                            for (var i = 0; i < participantsList.visibleChildren.length; i++) {
                                                listViewHeight += participantsList.visibleChildren[i].height + elements_spacing_
                                                var min_width = participantsList.visibleChildren[i].width
                                                for (var j = 0; j < participantsList.visibleChildren[i].visibleChildren.length; j++)
                                                {
                                                    min_width = Math.max(min_width, participantsList.visibleChildren[i].visibleChildren[j].width)
                                                }
                                                listViewWidth  = Math.max(listViewWidth, min_width)
                                                max_participant_width_ = Math.max(max_participant_width_, listViewWidth)
                                                max_participant_width_ = Math.max(max_participant_width_, (2*elements_spacing_)+max_endpoint_width_)
                                                participantsList.visibleChildren[i].width = max_participant_width_
                                            }

                                            participantsList.height = listViewHeight + elements_spacing_
                                            participantsList.width = max_participant_width_
                                            participants_updated_()
                                        }

                                        delegate: Item
                                        {
                                            height: participant_tag.height + endpointsList.height
                                            width: participantRowLayout.implicitWidth > max_participant_width_
                                                ? participantRowLayout.implicitWidth
                                                : max_participant_width_ == 0
                                                    ? participantRowLayout.implicitWidth
                                                    : max_participant_width_

                                            Rectangle
                                            {
                                                id: participant_background
                                                height: parent.height
                                                width: parent.width
                                                color: participant_color_
                                                radius: radius_
                                            }
                                            Rectangle
                                            {
                                                id: participant_tag
                                                anchors.top: parent.top
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                implicitWidth: participantRowLayout.implicitWidth > max_participant_width_
                                                    ? participantRowLayout.implicitWidth
                                                    : max_participant_width_ == 0
                                                        ? participantRowLayout.implicitWidth
                                                        : max_participant_width_
                                                height: label_height_
                                                color: participant_color_
                                                radius: radius_

                                                RowLayout {
                                                    id: participantRowLayout
                                                    anchors.centerIn: parent

                                                    IconSVG {
                                                        visible: modelData["status"] != "ok"
                                                        name: "issues"
                                                        size: modelData["status"] != "ok"? icon_size_ : 0
                                                        Layout.leftMargin: modelData["status"] != "ok" ? first_indentation_ : 0
                                                    }
                                                    IconSVG {
                                                        name: modelData["kind"]
                                                        size: icon_size_
                                                    }
                                                    Label {
                                                        text: modelData["alias"]
                                                        Layout.rightMargin: spacing_icon_label_ + first_indentation_
                                                    }
                                                }
                                                Rectangle {
                                                    visible: participant_tag.implicitWidth < max_participant_width_
                                                    anchors.left: participant_tag.right
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    height: participant_tag.height
                                                    width: max_participant_width_ - participant_tag.implicitWidth
                                                    color: participant_background.color
                                                    radius: radius_
                                                }
                                                MouseArea
                                                {
                                                    anchors.fill: parent
                                                    onClicked:
                                                    {
                                                        console.log(modelData["alias"] + " clicked!")
                                                    }
                                                }
                                            }

                                            ListView
                                            {
                                                id: endpointsList
                                                model: modelData["endpoints"]
                                                anchors.top: participant_tag.bottom; anchors.topMargin: elements_spacing_
                                                anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                                                anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                                                interactive: false
                                                spacing: elements_spacing_

                                                Connections
                                                {
                                                    target: domainGraphLayout

                                                    function onTopics_updated_()
                                                    {
                                                        endpointsList.onCountChanged()
                                                    }
                                                }

                                                onCountChanged:
                                                {
                                                    var listViewHeight = 0

                                                    // iterate over each element in the list item
                                                    for (var i = 0; i < endpointsList.visibleChildren.length; i++) {
                                                        listViewHeight += endpointsList.visibleChildren[i].height + elements_spacing_
                                                        var min_width = endpointsList.visibleChildren[i].width
                                                        for (var j = 0; j < endpointsList.visibleChildren[i].visibleChildren.length; j++)
                                                        {
                                                            min_width = Math.max(min_width, endpointsList.visibleChildren[i].visibleChildren[j].width)
                                                        }
                                                        max_endpoint_width_ = Math.max(max_endpoint_width_, min_width)
                                                        endpointsList.visibleChildren[i].width = max_endpoint_width_
                                                    }

                                                    for (var c = 0; c < endpointsList.count; c++)
                                                    {
                                                        endpointsList.currentIndex = c
                                                        endpointsList.currentItem.record_connection()
                                                    }

                                                    endpointsList.height = listViewHeight + elements_spacing_
                                                    endpointsList.width = max_endpoint_width_
                                                    endpoints_updated_()
                                                }

                                                delegate: Item
                                                {
                                                    id: endpointComponent
                                                    width: endpointRowLayout.implicitWidth > max_endpoint_width_
                                                        ? endpointRowLayout.implicitWidth
                                                        : max_endpoint_width_ == 0
                                                            ? endpointRowLayout.implicitWidth
                                                            : max_endpoint_width_
                                                    height: endpoint_height_

                                                    function record_connection()
                                                    {
                                                        var globalCoordinates = endpointComponent.mapToItem(mainSpace, 0, 0)
                                                        var src_x = globalCoordinates.x + endpointComponent.width
                                                        var src_y = modelData["accum_y"] + (endpointComponent.height / 2)
                                                        var left_direction = modelData["kind"] == "datareader"
                                                        var right_direction = modelData["kind"] == "datawriter"

                                                        endpoint_topic_connections_[modelData["id"]] = {
                                                            "id":  modelData["id"], "left_direction": left_direction,
                                                            "right_direction": right_direction, "x": src_x, "y": src_y,
                                                            "destination_id": modelData["topic"]
                                                        }
                                                    }

                                                    Rectangle
                                                    {
                                                        id: endpoint_background
                                                        width: parent.width
                                                        height: endpoint_height_
                                                        color: modelData["kind"] == "datareader" ? reader_color_ : writer_color_
                                                        radius: radius_
                                                    }
                                                    Rectangle
                                                    {
                                                        id: endpoint_tag
                                                        anchors.top: parent.top
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        implicitWidth: endpointRowLayout.implicitWidth > max_endpoint_width_
                                                            ? endpointRowLayout.implicitWidth
                                                            : max_endpoint_width_ == 0
                                                                ? endpointRowLayout.implicitWidth
                                                                : max_endpoint_width_
                                                        height: endpoint_height_
                                                        color: endpoint_background.color
                                                        radius: radius_

                                                        RowLayout {
                                                            id: endpointRowLayout
                                                            anchors.centerIn: parent

                                                            IconSVG {
                                                                visible: modelData["status"] != "ok"
                                                                name: "issues"
                                                                size: modelData["status"] != "ok"? icon_size_ : 0
                                                                Layout.leftMargin: modelData["status"] != "ok" ? first_indentation_ : 0
                                                            }
                                                            IconSVG {
                                                                name: modelData["kind"]
                                                                size: icon_size_
                                                            }
                                                            Label {
                                                                text: modelData["alias"]
                                                                Layout.rightMargin: spacing_icon_label_ + first_indentation_
                                                            }
                                                        }
                                                        MouseArea
                                                        {
                                                            anchors.fill: parent
                                                            onClicked:
                                                            {
                                                                console.log(modelData["alias"] + " clicked!")
                                                            }
                                                        }
                                                    }
                                                    Rectangle {
                                                        visible: endpoint_tag.implicitWidth < max_endpoint_width_
                                                        anchors.left: endpoint_tag.right
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        height: endpoint_tag.height
                                                        width: max_endpoint_width_ - endpoint_tag.implicitWidth
                                                        color: endpoint_background.color
                                                        radius: radius_
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Connections
            {
                target: domainGraphLayout

                function onTopics_updated_()
                {
                    mainSpace.create_connections()
                }

                function onEndpoints_updated_()
                {
                    mainSpace.create_connections()
                }

                function onParticipants_updated_()
                {
                    mainSpace.create_connections()
                }

                function onProcesses_updated_()
                {
                    mainSpace.create_connections()
                }

                function onUsers_updated_()
                {
                    mainSpace.create_connections()
                }

                function onHosts_updated_()
                {
                    mainSpace.create_connections()
                }
            }

            function create_connections()
            {
                for (var key in endpoint_topic_connections_)
                {
                    var topic_id = endpoint_topic_connections_[key]["destination_id"]
                    if (topic_locations_[topic_id] != undefined)
                    {
                        if (!entity_painted_.includes(key))
                        {
                            //console.log(key)
                            //console.log(JSON.stringify(endpoint_topic_connections_[key], null, 2))
                            var destination_x = topic_locations_[topic_id]["x"]
                            var input = {"x": endpoint_topic_connections_[key]["x"]
                                ,"left_direction": endpoint_topic_connections_[key]["left_direction"]
                                ,"y": endpoint_topic_connections_[key]["y"] - (connection_thickness_ / 2)
                                ,"width": 4*elements_spacing_
                                ,"height":connection_thickness_, "z":200
                                ,"arrow_color": topic_color_, "background_color": background_color.color }
                            var connection_bar = arrow_component.createObject(mainSpace, input)
                            entity_painted_[entity_painted_.length] = key
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        height: 2* elements_spacing_ + label_height_
        width: max_host_width_ +2* elements_spacing_
        color: "white"
        z: 12

        Button{
            width: parent.width /2
            height: label_height_
            anchors.centerIn: parent
            text: "Refresh"

            onClicked:{
                load_model()
            }
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        height: elements_spacing_
        width: max_host_width_ + elements_spacing_
        color: "white"
        z: 14
    }


    function load_model(new_model)
    {
        // remove drawn connections
        for (var i = 0; i < mainSpace.children.length; i++)
        {
            if (mainSpace.children[i].left_margin != undefined)
            {
                mainSpace.children[i].destroy()
            }
        }
        for (var i = 0; i < topic_connections.children.length; i++)
        {
            if (topic_connections.children[i].left_margin != undefined)
            {
                topic_connections.children[i].destroy()
            }
        }
        // clear internal models
        topic_locations_ = {}
        endpoint_topic_connections_ = {}
        entity_painted_ = []
        topic_painted_ = []

        // Obtain model from backend, and parse from string to JSON
        var model_string = controller.get_domain_view_graph(entity_id)
        var new_model = JSON.parse(model_string)

        // transform indexed model to array model (arrays required for the listviews)
        var new_topics = []
        for (var topic in new_model["topics"])
        {
            new_topics[new_topics.length] = {
                "id":topic,
                "kind":new_model["topics"][topic]["kind"],
                "alias":new_model["topics"][topic]["alias"],}
        }
        var accum_y = 0
        var new_hosts = []
        for (var host in new_model["hosts"])
        {
            accum_y += label_height_ + elements_spacing_
            var new_users = []
            for (var user in new_model["hosts"][host]["users"])
            {
                accum_y += label_height_ + elements_spacing_
                var new_processes = []
                for (var process in new_model["hosts"][host]["users"][user]["processes"])
                {
                    accum_y += label_height_ + elements_spacing_
                    var new_participants = []
                    for (var participant in new_model["hosts"][host]["users"][user]["processes"][process]["participants"])
                    {
                        accum_y += label_height_ + elements_spacing_
                        var new_endpoints = []
                        for (var endpoint in new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"])
                        {
                            new_endpoints[new_endpoints.length] = {
                                "id":endpoint,
                                "kind":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["kind"],
                                "alias":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["alias"],
                                "status":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["status"],
                                "topic":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["topic"],
                                "accum_y":accum_y
                            }
                            accum_y += endpoint_height_ + elements_spacing_
                        }
                        new_participants[new_participants.length] = {
                            "id":participant,
                            "kind":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["kind"],
                            "alias":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["alias"],
                            "status":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["status"],
                            "app_id":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["app_id"],
                            "app_metadata":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["app_metadata"],
                            "endpoints":new_endpoints
                        }
                        accum_y += elements_spacing_
                    }
                    new_processes[new_processes.length] = {
                        "id":process,
                        "kind":new_model["hosts"][host]["users"][user]["processes"][process]["kind"],
                        "alias":new_model["hosts"][host]["users"][user]["processes"][process]["alias"],
                        "pid": new_model["hosts"][host]["users"][user]["processes"][process]["pid"],
                        "status":new_model["hosts"][host]["users"][user]["processes"][process]["status"],
                        "participants":new_participants
                    }
                    accum_y += elements_spacing_
                }
                new_users[new_users.length] = {
                    "id":user,
                    "kind":new_model["hosts"][host]["users"][user]["kind"],
                    "alias":new_model["hosts"][host]["users"][user]["alias"],
                    "status":new_model["hosts"][host]["users"][user]["status"],
                    "processes":new_processes
                }
                accum_y += elements_spacing_
            }
            new_hosts[new_hosts.length] = {
                "id":host,
                "kind":new_model["hosts"][host]["kind"],
                "alias":new_model["hosts"][host]["alias"],
                "status":new_model["hosts"][host]["status"],
                "users":new_users
            }
            accum_y += elements_spacing_
        }
        model = {
            "kind": new_model["kind"],
            "domain": new_model["domain"],
            "topics": new_topics,
            "hosts": new_hosts,
        }

        // Update tab name with selected domain id
        domainGraphLayout.update_tab_name("Domain " + new_model["domain"] + " View")

        // Update visual elements
        resize_elements_()
    }

    function remove_connections()
    {

    }
}
