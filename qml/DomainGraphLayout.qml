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
    property var model: {}                          // domain view graph JSON model
    property int entity_id                          // entity id associated to the domain id
    property int domain_id                          // domain id
    required property string component_id           // mandatory to be included when object created

    // Public signals
    signal update_tab_name(string new_name)         // Update tab name based on selected domain id

    // Private properties
    property var topic_locations_: {}               // topic information needed for connection representation
    property var endpoint_topic_connections_: {}    // endpoint information needed for connection representation
    property var topic_painted_: []                 // already painted topic connection references
    property var endpoint_painted_: []              // already painted endpoint connection references
    property int entity_box_width_: 0               // entities box width management

    // Private (resize) signals               resize_elements_ will trigger a bunch of resize methods per entities and
    //    HOST       TOPIC ─┐                 topics, when 2 iterations are performed. The first one is aimed  to
    //  3↓ ... ↑2    1│ ↑  5└─>CONNECTIONS    resize "parents" based on max "child" size, and then the second one takes
    //   ENDPOINT <───┘ │                     place to ensure the well format if a "parent" has a size longer than a
    //   4└─────────────┘                     "child". After that, with the final results, connections between topics
    //                                        and endpoints are generated
    signal resize_elements_()
    signal update_endpoints_()
    signal update_participants_()
    signal update_processes_()
    signal update_users_()
    signal update_hosts_()
    signal topics_updated_()
    signal endpoints_updated_()
    signal participants_updated_()
    signal processes_updated_()
    signal users_updated_()
    signal hosts_updated_()
    signal generate_connections_()

    // Read only design properties (sizes and colors)
    readonly property int radius_: 10
    readonly property int connection_thickness_: 5
    readonly property int elements_spacing_: 12
    readonly property int containers_spacing_: 100
    readonly property int endpoint_height_: 40
    readonly property int first_indentation_: 5
    readonly property int icon_size_: 18
    readonly property int label_height_: 35
    readonly property int spacing_icon_label_: 8
    readonly property int scrollbar_min_size_: 8
    readonly property int scrollbar_max_size_: 12
    readonly property int topic_thickness_: 10
    readonly property int wheel_displacement_: 30
    readonly property string topic_color_: Theme.grey
    readonly property string host_color_: Theme.darkGrey
    readonly property string user_color_: Theme.eProsimaLightBlue
    readonly property string process_color_: Theme.eProsimaDarkBlue
    readonly property string participant_color_: Theme.whiteSmoke
    readonly property string reader_color_: Theme.eProsimaYellow
    readonly property string writer_color_: Theme.eProsimaGreen

    // Obtain given domain id graph
    Component.onCompleted:
    {
        load_model()
    }

    // Horizontal scroll view for topics section. This will contain also a Flickable that replicates entities height
    // and will move accordingly to display the connections
    Flickable {
        id: topicView
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.leftMargin: entity_box_width_ + elements_spacing_
        width: parent.width - entity_box_width_ - 2*elements_spacing_
        flickableDirection: Flickable.HorizontalFlick
        boundsBehavior: Flickable.StopAtBounds

        contentWidth: topicsList.contentWidth + containers_spacing_
        contentHeight: parent.height

        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOff }
        ScrollBar.horizontal: ScrollBar {
            id: horizontal_bar
            anchors.left: parent.left; anchors.leftMargin: elements_spacing_
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

        // List view of topics model
        ListView
        {
            id: topicsList
            model: domainGraphLayout.model ? domainGraphLayout.model["topics"] : undefined
            anchors.left: parent.left; anchors.leftMargin: 2 * elements_spacing_
            anchors.top: parent.top; anchors.topMargin: elements_spacing_;
            anchors.bottom: parent.bottom
            contentWidth: contentItem.childrenRect.width
            spacing: elements_spacing_
            orientation: ListView.Horizontal
            interactive: false

            // Resizing management connections
            Connections
            {
                target: domainGraphLayout

                function onResize_elements_()
                {
                    topicsList.resize()
                    update_endpoints_()
                }

                function onEndpoints_updated_()
                {
                    topicsList.create_connections()
                }
            }

            // Resize performed also when new element included in the model
            onCountChanged:
            {
                topicsList.resize()
            }

            // Calculates the list height based on the number of contained entities, and width based on their widths
            function resize()
            {
                var listViewHeight = 0
                var listViewWidth = 0

                // iterate over each element in the list item
                for (var c = 0; c < topicsList.count; c++)
                {
                    topicsList.currentIndex = c
                    if (topicsList.currentItem != null)
                    {
                        listViewHeight = topicsList.currentItem.height
                        listViewWidth += topicsList.currentItem.width + elements_spacing_
                    }
                }
                topicsList.height = listViewHeight
                topicsList.width = listViewWidth
            }

            function create_connections()
            {
                var draw_width = 2*elements_spacing_

                // load topic sizes
                topicsList.resize()

                // iterate over each element in the list item
                for (var c = 0; c < topicsList.count; c++)
                {
                    topicsList.currentIndex = c
                    topic_locations_[topicsList.currentItem.topic_id] = {
                        "id": topicsList.currentItem.topic_id,
                        "width" : draw_width + topicsList.currentItem.width/2
                    }
                    draw_width += topicsList.currentItem.width + elements_spacing_
                }

                // announce topics are ready
                topics_updated_()
            }

            // Topic delegated item box with vertical line
            delegate: Rectangle
            {
                property string topic_id: modelData["id"]
                implicitWidth: topic_tag.implicitWidth
                height: topicsList.height
                color: "transparent"

                // Topic name and icon
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
                            Layout.rightMargin: 2* first_indentation_
                            color: "white"
                        }
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            controller.topic_click(modelData["id"])
                        }
                    }
                }

                // Topic vertical line
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

        // Section where connections are represented
        Flickable
        {
            id: topicSpace
            anchors.top: parent.top; anchors.topMargin: label_height_ + 2* elements_spacing_
            anchors.left: parent.left
            width: parent.width
            height: parent.height - (label_height_ + 2* elements_spacing_)
            interactive: false
            clip: true

            contentWidth: topicsList.contentWidth + containers_spacing_
            contentHeight: mainView.contentHeight
            Rectangle {id: topic_connections; anchors.fill:parent; color: "transparent" }

            // Not visible scroll bar
            ScrollBar.vertical: ScrollBar{
                id: custom_bar
                visible: false

                // connection to move vertically the view when entities view moves vertically
                Connections {
                    target: vertical_bar

                    function onPositionChanged(){
                        custom_bar.position = vertical_bar.position
                    }
                }
            }

            // Overriding mouse area to scroll horizontally on wheel event
            MouseArea {
                anchors.fill: parent
                preventStealing: true

                onWheel: {
                    if (topicView.contentWidth > topicView.width)
                    {
                        if (wheel.angleDelta.y > 0) {
                            topicView.contentX -= wheel_displacement_
                            if (topicView.contentX < 0) {
                                topicView.contentX = 0;
                            }
                        } else {
                            topicView.contentX += wheel_displacement_
                            if (topicView.contentX + topicView.width > topicView.contentWidth) {
                                topicView.contentX = topicView.contentWidth -  topicView.width;
                            }
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

        // Resizing management connections
        Connections
        {
            target: domainGraphLayout

            function onTopics_updated_()
            {
                topicView.create_connections()
            }
        }

        // Generate connections in topic side
        function create_connections()
        {
            for (var key in endpoint_topic_connections_)
            {
                var topic_id = endpoint_topic_connections_[key]["destination_id"]
                if (topic_locations_[topic_id] != undefined)
                {
                    if (!topic_painted_.includes(key))
                    {
                        var input = {"x": 0
                            ,"right_direction": endpoint_topic_connections_[key]["right_direction"]
                            ,"y": endpoint_topic_connections_[key]["y"] - (connection_thickness_ / 2)
                            ,"width": topic_locations_[topic_id]["width"]
                            ,"height":connection_thickness_, "z":200, "left_margin": 2*elements_spacing_
                            ,"arrow_color": topic_color_, "background_color": background_color.color }
                        var connection_bar = arrow_component.createObject(topic_connections, input)
                        topic_painted_[topic_painted_.length] = key;
                    }
                }
            }
        }
    }

    // Entities vertical flickable (left section)
    Flickable {
        id: mainView
        anchors.left: parent.left ; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: entity_box_width_ + elements_spacing_
        anchors.topMargin: 2* elements_spacing_ + label_height_
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

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

        // Scpace where entities will be represented
        Rectangle
        {
            id: mainSpace
            anchors.top: parent.top

            width: hostsList.width + 2*elements_spacing_
            height: hostsList.height < domainGraphLayout.height - (label_height_ + 2*elements_spacing_)
                ? domainGraphLayout.height - (label_height_ + 2*elements_spacing_) : hostsList.height

            // Entities background
            Rectangle {
                id: background_color
                anchors.fill: parent
                color: "white"
            }

            // Graph connection component definition for object creation purposes
            Component {
                id: arrow_component
                GraphConnection{

                }
            }

            // List view of hosts model (which would contain remain entities nested)
            ListView
            {
                id: hostsList
                model: domainGraphLayout.model ? domainGraphLayout.model["hosts"] : undefined
                anchors.top: parent.top
                anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                interactive: false
                spacing: elements_spacing_

                // Resizing management connections
                Connections
                {
                    target: domainGraphLayout

                    function onUpdate_hosts_()
                    {
                        hostsList.resize()
                        hosts_updated_()
                    }
                }

                // Resize performed also when new element included in the model
                onCountChanged:
                {
                    hostsList.resize()
                }

                // Calculates the list height based on the number of contained entities, and width based on their widths
                function resize()
                {
                    var listViewHeight = 0
                    var aux_width = entity_box_width_

                    // iterate over each element in the list item
                    for (var c = 0; c < hostsList.count; c++)
                    {
                        hostsList.currentIndex = c
                        if (hostsList.currentItem != null)
                        {
                            listViewHeight += hostsList.currentItem.height + elements_spacing_
                            aux_width = Math.max(aux_width, hostsList.currentItem.width)
                        }
                    }

                    hostsList.height = listViewHeight

                    // update if necessary
                    if (aux_width > entity_box_width_)
                    {
                        clear_graph()
                        entity_box_width_ = aux_width
                        resize_elements_()
                    }
                }

                // Host delegated item box
                delegate: Item
                {
                    height: host_tag.height + usersList.height
                    width: hostRowLayout.implicitWidth > entity_box_width_
                        ? hostRowLayout.implicitWidth
                        : entity_box_width_

                    // background
                    Rectangle
                    {
                        id: host_background
                        height: parent.height
                        width: parent.width
                        color: host_color_
                        radius: radius_
                    }

                    // host name and icons
                    Rectangle
                    {
                        id: host_tag
                        anchors.horizontalCenter: parent.horizontalCenter
                        implicitWidth: hostRowLayout.implicitWidth > entity_box_width_
                            ? hostRowLayout.implicitWidth
                            : entity_box_width_
                        height: label_height_
                        color: host_color_
                        radius: radius_

                        RowLayout {
                            id: hostRowLayout
                            spacing: spacing_icon_label_
                            anchors.centerIn: parent

                            Rectangle {
                                color: "transparent"
                                width: modelData["status"] != "OK"
                                    ? first_indentation_ : 0
                            }
                            IconSVG {
                                visible: modelData["status"] != "OK"
                                name: "issues"
                                color: "white"
                                size: modelData["status"] != "OK"? icon_size_ : 0
                            }
                            Rectangle {
                                color: "transparent"
                                width: first_indentation_ /2
                            }
                            IconSVG {
                                name: "host"
                                color: "white"
                                size: icon_size_
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
                                controller.host_click(modelData["id"])
                            }
                        }
                    }

                    // List view of users model (which would contain remain entities nested)
                    ListView
                    {
                        id: usersList
                        model: modelData["users"]
                        anchors.top: host_tag.bottom; anchors.topMargin: elements_spacing_
                        anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                        anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                        interactive: false
                        spacing: elements_spacing_

                        // Resizing management connections
                        Connections
                        {
                            target: domainGraphLayout

                            function onUpdate_users_()
                            {
                                usersList.resize()
                                update_hosts_()
                            }
                            function onHosts_updated_()
                            {
                                usersList.resize()
                                users_updated_()
                            }
                        }

                        // Resize performed also when new element included in the model
                        onCountChanged:
                        {
                            usersList.resize()
                        }

                        // Calculates the list height based on the number of contained entities, and width based on
                        // their widths
                        function resize()
                        {
                            var listViewHeight = 0
                            var aux_width = entity_box_width_

                            // iterate over each element in the list item
                            for (var c = 0; c < usersList.count; c++)
                            {
                                usersList.currentIndex = c
                                if (usersList.currentItem != null)
                                {
                                    listViewHeight += usersList.currentItem.height + elements_spacing_
                                    aux_width = Math.max(aux_width, usersList.currentItem.width+(2*elements_spacing_))
                                }
                            }

                            usersList.height = listViewHeight + elements_spacing_

                            // update if necessary
                            if (aux_width > entity_box_width_)
                            {
                                clear_graph()
                                entity_box_width_ = aux_width
                                resize_elements_()
                            }
                        }

                        // User delegated item box
                        delegate: Item
                        {
                            height: user_tag.height + processesList.height
                            width: userRowLayout.implicitWidth > (entity_box_width_-(2*elements_spacing_))
                                ? userRowLayout.implicitWidth
                                : entity_box_width_-(2*elements_spacing_)

                            // background
                            Rectangle
                            {
                                id: user_background
                                height: parent.height
                                width: parent.width
                                color: user_color_
                                radius: radius_
                            }

                            // user name and icons
                            Rectangle
                            {
                                id: user_tag
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                                implicitWidth: userRowLayout.implicitWidth > (entity_box_width_-(2*elements_spacing_))
                                    ? userRowLayout.implicitWidth
                                    : entity_box_width_-(2*elements_spacing_)
                                height: label_height_
                                color: user_color_
                                radius: radius_

                                RowLayout {
                                    id: userRowLayout
                                    spacing: spacing_icon_label_
                                    anchors.centerIn: parent

                                    Rectangle {
                                        color: "transparent"
                                        width: modelData["status"] != "OK"
                                            ? first_indentation_ : 0
                                    }
                                    IconSVG {
                                        visible: modelData["status"] != "OK"
                                        name: "issues"
                                        color: "white"
                                        size: modelData["status"] != "OK"? icon_size_ : 0
                                    }
                                    Rectangle {
                                        color: "transparent"
                                        width: first_indentation_ /2
                                    }
                                    IconSVG {
                                        name: "user"
                                        color: "white"
                                        size: icon_size_
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
                                        controller.user_click(modelData["id"])
                                    }
                                }
                            }

                            // List view of processes model (which would contain remain entities nested)
                            ListView
                            {
                                id: processesList
                                model: modelData["processes"]
                                anchors.top: user_tag.bottom; anchors.topMargin: elements_spacing_
                                anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                                anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                                interactive: false
                                spacing: elements_spacing_

                                // Resizing management connections
                                Connections
                                {
                                    target: domainGraphLayout

                                    function onUpdate_processes_()
                                    {
                                        processesList.resize()
                                        update_users_()
                                    }

                                    function onUsers_updated_()
                                    {
                                        processesList.resize()
                                        processes_updated_()
                                    }
                                }

                                // Resize performed also when new element included in the model
                                onCountChanged:
                                {
                                    processesList.resize()
                                }

                                // Calculates the list height based on the number of contained entities,
                                // and width based on their widths
                                function resize()
                                {
                                    var listViewHeight = 0
                                    var aux_width = entity_box_width_

                                    // iterate over each element in the list item
                                    for (var c = 0; c < processesList.count; c++)
                                    {
                                        processesList.currentIndex = c
                                        if (processesList.currentItem != null)
                                        {
                                            listViewHeight += processesList.currentItem.height + elements_spacing_
                                            aux_width = Math.max(aux_width, processesList.currentItem.width+(4*elements_spacing_))
                                        }
                                    }

                                    processesList.height = listViewHeight + elements_spacing_

                                    // update if necessary
                                    if (aux_width > entity_box_width_)
                                    {
                                        clear_graph()
                                        entity_box_width_ = aux_width
                                        resize_elements_()
                                    }
                                }

                                // Process delegated item box
                                delegate: Item
                                {
                                    height: process_tag.height + participantsList.height
                                    width: processRowLayout.implicitWidth > (entity_box_width_-(4*elements_spacing_))
                                        ? processRowLayout.implicitWidth
                                        : entity_box_width_-(4*elements_spacing_)

                                    // background
                                    Rectangle
                                    {
                                        id: process_background
                                        height: parent.height
                                        width: parent.width
                                        color: process_color_
                                        radius: radius_
                                    }

                                    // process name and icons
                                    Rectangle
                                    {
                                        id: process_tag
                                        anchors.top: parent.top
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        implicitWidth: processRowLayout.implicitWidth > (entity_box_width_-(4*elements_spacing_))
                                            ? processRowLayout.implicitWidth
                                            : entity_box_width_-(4*elements_spacing_)
                                        height: label_height_
                                        color: process_color_
                                        radius: radius_

                                        RowLayout {
                                            id: processRowLayout
                                            spacing: spacing_icon_label_
                                            anchors.centerIn: parent

                                            Rectangle {
                                                color: "transparent"
                                                width: modelData["status"] != "OK"
                                                    ? first_indentation_ : 0
                                            }
                                            IconSVG {
                                                visible: modelData["status"] != "OK"
                                                name: "issues"
                                                color: "white"
                                                size: modelData["status"] != "OK"? icon_size_ : 0
                                            }
                                            Rectangle {
                                                color: "transparent"
                                                width: first_indentation_ /2
                                            }
                                            IconSVG {
                                                name: "process"
                                                color: "white"
                                                size: icon_size_
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
                                                controller.process_click(modelData["id"])
                                            }
                                        }
                                    }

                                    // List view of participants model (which would contain remain endpoints nested)
                                    ListView
                                    {
                                        id: participantsList
                                        model: modelData["participants"]
                                        anchors.top: process_tag.bottom; anchors.topMargin: elements_spacing_
                                        anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                                        anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                                        interactive: false
                                        spacing: elements_spacing_

                                        // Resizing management connections
                                        Connections
                                        {
                                            target: domainGraphLayout

                                            function onUpdate_participants_()
                                            {
                                                participantsList.resize()
                                                update_processes_()
                                            }
                                            function onProcesses_updated_()
                                            {
                                                participantsList.resize()
                                                participants_updated_()
                                            }
                                        }

                                        // Resize performed also when new element included in the model
                                        onCountChanged:
                                        {
                                            participantsList.resize()
                                        }

                                        // Calculates the list height based on the number of contained entities,
                                        // and width based on their widths
                                        function resize()
                                        {
                                            var listViewHeight = 0
                                            var aux_width = entity_box_width_

                                            // iterate over each element in the list item
                                            for (var c = 0; c < participantsList.count; c++)
                                            {
                                                participantsList.currentIndex = c
                                                if (participantsList.currentItem != null)
                                                {
                                                    listViewHeight += participantsList.currentItem.height + elements_spacing_
                                                    aux_width = Math.max(aux_width, participantsList.currentItem.width+(6*elements_spacing_))
                                                }
                                            }

                                            participantsList.height = listViewHeight + elements_spacing_

                                            // update if necessary
                                            if (aux_width > entity_box_width_)
                                            {
                                                clear_graph()
                                                entity_box_width_ = aux_width
                                                resize_elements_()
                                            }
                                        }

                                        // Participant delegated item box
                                        delegate: Item
                                        {
                                            height: participant_tag.height + endpointsList.height
                                            width: participantRowLayout.implicitWidth > (entity_box_width_-(6*elements_spacing_))
                                                ? participantRowLayout.implicitWidth
                                                : entity_box_width_-(6*elements_spacing_)

                                            // background
                                            Rectangle
                                            {
                                                id: participant_background
                                                height: parent.height
                                                width: parent.width
                                                color: participant_color_
                                                radius: radius_
                                            }

                                            // participant name and icons
                                            Rectangle
                                            {
                                                id: participant_tag
                                                anchors.top: parent.top
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                implicitWidth: participantRowLayout.implicitWidth > (entity_box_width_-(6*elements_spacing_))
                                                    ? participantRowLayout.implicitWidth
                                                    : entity_box_width_-(6*elements_spacing_)
                                                height: label_height_
                                                color: participant_color_
                                                radius: radius_

                                                RowLayout {
                                                    id: participantRowLayout
                                                    spacing: spacing_icon_label_
                                                    anchors.centerIn: parent

                                                    Rectangle {
                                                        color: "transparent"
                                                        width: modelData["status"] != "OK"
                                                            ? first_indentation_ : 0
                                                    }
                                                    IconSVG {
                                                        visible: modelData["status"] != "OK"
                                                        name: "issues"
                                                        size: modelData["status"] != "OK"? icon_size_ : 0
                                                    }
                                                    Rectangle {
                                                        color: "transparent"
                                                        width: first_indentation_ /2
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
                                                        controller.participant_click(modelData["id"])
                                                    }
                                                }
                                            }

                                            // List view of endpoint model
                                            ListView
                                            {
                                                id: endpointsList
                                                model: modelData["endpoints"]
                                                anchors.top: participant_tag.bottom; anchors.topMargin: elements_spacing_
                                                anchors.left: parent.left; anchors.leftMargin: elements_spacing_
                                                anchors.right: parent.right; anchors.rightMargin: elements_spacing_
                                                interactive: false
                                                spacing: elements_spacing_

                                                // Resizing management connections
                                                Connections
                                                {
                                                    target: domainGraphLayout

                                                    function onUpdate_endpoints_()
                                                    {
                                                        endpointsList.resize()
                                                        update_participants_()
                                                    }

                                                    function onParticipants_updated_()
                                                    {
                                                        endpointsList.resize()
                                                        endpoints_updated_()
                                                    }

                                                    function onTopics_updated_()
                                                    {
                                                        endpointsList.record_connections()
                                                    }
                                                }

                                                // Resize performed also when new element included in the model
                                                onCountChanged:
                                                {
                                                    endpointsList.resize()
                                                }

                                                // Calculates the list height based on the number of contained entities,
                                                // and width based on their widths
                                                function resize()
                                                {
                                                    var listViewHeight = 0
                                                    var aux_width = entity_box_width_

                                                    // iterate over each element in the list item
                                                    for (var c = 0; c < endpointsList.count; c++)
                                                    {
                                                        endpointsList.currentIndex = c
                                                        if (endpointsList.currentItem != null)
                                                        {
                                                            listViewHeight += endpointsList.currentItem.height + elements_spacing_
                                                            aux_width = Math.max(aux_width, endpointsList.currentItem.width+(8*elements_spacing_))
                                                        }
                                                    }

                                                    endpointsList.height = listViewHeight + elements_spacing_

                                                    // update if necessary
                                                    if (aux_width > entity_box_width_)
                                                    {
                                                        clear_graph()
                                                        entity_box_width_ = aux_width
                                                        resize_elements_()
                                                    }
                                                }

                                                function record_connections()
                                                {
                                                    for (var c = 0; c < endpointsList.count; c++)
                                                    {
                                                        endpointsList.currentIndex = c
                                                        endpointsList.currentItem.record_connection()
                                                    }
                                                    generate_connections_()
                                                }

                                                // Endpoint delegated item box
                                                delegate: Item
                                                {
                                                    id: endpointComponent
                                                    width: endpointRowLayout.implicitWidth > (entity_box_width_-(8*elements_spacing_))
                                                        ? endpointRowLayout.implicitWidth
                                                        : entity_box_width_-(8*elements_spacing_)
                                                    height: endpoint_height_

                                                    // Saves the endpoint needed info for connection representation
                                                    function record_connection()
                                                    {
                                                        var globalCoordinates = endpointComponent.mapToItem(mainSpace, 0, 0)
                                                        var src_x = globalCoordinates.x + entity_box_width_-(8*elements_spacing_)
                                                        var src_y = modelData["accum_y"] + (endpointComponent.height / 2)
                                                        var left_direction = modelData["kind"] == "datareader"
                                                        var right_direction = modelData["kind"] == "datawriter"

                                                        endpoint_topic_connections_[modelData["id"]] = {
                                                            "id":  modelData["id"], "left_direction": left_direction,
                                                            "right_direction": right_direction, "x": src_x, "y": src_y,
                                                            "destination_id": modelData["topic"]
                                                        }
                                                    }

                                                    // background
                                                    Rectangle
                                                    {
                                                        id: endpoint_background
                                                        width: parent.width
                                                        height: endpoint_height_
                                                        color: modelData["kind"] == "datareader" ? reader_color_ : writer_color_
                                                        radius: radius_
                                                    }

                                                    // endpoint name and icons
                                                    Rectangle
                                                    {
                                                        id: endpoint_tag
                                                        anchors.top: parent.top
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        implicitWidth: endpointRowLayout.implicitWidth > (entity_box_width_-(8*elements_spacing_))
                                                            ? endpointRowLayout.implicitWidth
                                                            : entity_box_width_-(8*elements_spacing_)
                                                        height: endpoint_height_
                                                        color: endpoint_background.color
                                                        radius: radius_

                                                        RowLayout {
                                                            id: endpointRowLayout
                                                            spacing: spacing_icon_label_
                                                            anchors.centerIn: parent

                                                            Rectangle {
                                                                color: "transparent"
                                                                width: modelData["status"] != "OK"
                                                                    ? first_indentation_ : 0
                                                            }
                                                            IconSVG {
                                                                visible: modelData["status"] != "OK"
                                                                name: "issues"
                                                                size: modelData["status"] != "OK"? icon_size_ : 0
                                                            }
                                                            Rectangle {
                                                                color: "transparent"
                                                                width: first_indentation_ /2
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
                                                                controller.endpoint_click(modelData["id"])
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
                }
            }

            // Resizing management connections
            Connections
            {
                target: domainGraphLayout

                function onGenerate_connections_()
                {
                    mainSpace.generate_connections()
                }
            }

            // Saves the topic needed info for connection representation
            function generate_connections()
            {
                for (var key in endpoint_topic_connections_)
                {
                    var topic_id = endpoint_topic_connections_[key]["destination_id"]
                    if (topic_locations_[topic_id] != undefined)
                    {
                        if (!endpoint_painted_.includes(key))
                        {
                            var input = {"x": endpoint_topic_connections_[key]["x"]
                                ,"y": endpoint_topic_connections_[key]["y"] - (connection_thickness_ / 2)
                                ,"left_direction": endpoint_topic_connections_[key]["left_direction"]
                                ,"width": 5*elements_spacing_
                                ,"height":connection_thickness_, "z":200
                                ,"arrow_color": topic_color_, "background_color": background_color.color }
                            var connection_bar = arrow_component.createObject(mainSpace, input)
                            endpoint_painted_[endpoint_painted_.length] = key
                        }
                    }
                }
            }
        }
    }

    // top section to cut entities layout and display the REFRESH butotn
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        height: 2* elements_spacing_ + label_height_
        width: entity_box_width_ + 2*elements_spacing_
        color: "white"

        // Refresh button
        Button{
            id: refresh_button
            width: parent.width /2 < 150 ? 150 : parent.width /2
            height: label_height_
            anchors.top: parent.top; anchors.topMargin: elements_spacing_
            anchors.left:  parent.left
            anchors.leftMargin: entity_box_width_/2 + elements_spacing_ - refresh_button.width /2 < 40
                ? 5* elements_spacing_ : (entity_box_width_/2) + elements_spacing_ - (refresh_button.width /2)
            text: "Refresh"

            onClicked:{
                load_model()
            }
        }
    }

    // footer section to cut entities layout
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        height: elements_spacing_
        width: entity_box_width_ + 2*elements_spacing_
        color: "white"
        z: 14
    }

    // Empty screen message
    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Text {
            id: emptyScreenLabel
            visible: true
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pointSize: 20
            font.bold: true
            color: Theme.x11Grey
            text: "Oops... no data to display"
        }
    }

    // Obtain given domain id graph JSON model
    function load_model()
    {
        // clear internal models
        clear_graph()

        // Obtain model from backend
        var model_string = controller.get_domain_view_graph(entity_id)

        // declare obtained hosts and topics variables
        var new_topics = []
        var new_hosts = []

        // Check if obtained graph is not empty
        if (model_string.length !== 0 && model_string !== "null")
        {
            // Parse model from string to JSON
            var new_model = JSON.parse(model_string)

            // Ensure expected graph was received
            if (new_model["domain"] == domain_id)
            {
                var is_metatraffic_visible_ = controller.metatraffic_visible();

                // transform indexed model to array model (arrays required for the listviews)
                for (var topic in new_model["topics"])
                {
                    var metatraffic_ = new_model["topics"][topic]["metatraffic"]
                    if (metatraffic_ != true || is_metatraffic_visible_)
                    {
                        new_topics[new_topics.length] = {
                            "id":topic,
                            "kind":new_model["topics"][topic]["kind"],
                            "alias":new_model["topics"][topic]["alias"]
                        }
                    }
                }
                var accum_y = 0
                for (var host in new_model["hosts"])
                {
                    var metatraffic_ = new_model["hosts"][host]["metatraffic"]
                    if (metatraffic_ != true || is_metatraffic_visible_)
                    {
                        accum_y += label_height_ + elements_spacing_
                        var new_users = []
                        for (var user in new_model["hosts"][host]["users"])
                        {
                            var metatraffic_ = new_model["hosts"][host]["users"][user]["metatraffic"]
                            if (metatraffic_ != true || is_metatraffic_visible_)
                            {
                                accum_y += label_height_ + elements_spacing_
                                var new_processes = []
                                for (var process in new_model["hosts"][host]["users"][user]["processes"])
                                {
                                    var metatraffic_ = new_model["hosts"][host]["users"][user]["processes"][process]["metatraffic"]
                                    if (metatraffic_ != true || is_metatraffic_visible_)
                                    {
                                        accum_y += label_height_ + elements_spacing_
                                        var new_participants = []
                                        for (var participant in new_model["hosts"][host]["users"][user]["processes"][process]["participants"])
                                        {
                                            var metatraffic_ = new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["metatraffic"]
                                            if (metatraffic_ != true || is_metatraffic_visible_)
                                            {
                                                accum_y += label_height_ + elements_spacing_
                                                var new_endpoints = []
                                                for (var endpoint in new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"])
                                                {
                                                    var metatraffic_ = new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["metatraffic"]
                                                    if (metatraffic_ != true || is_metatraffic_visible_)
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
                }
                model = {
                    "kind": new_model["kind"],
                    "domain": new_model["domain"],
                    "topics": new_topics,
                    "hosts": new_hosts,
                }

                // Update visual elements by re-calculating their sizes
                resize_elements_()

                // hide empty screen label
                emptyScreenLabel.visible = false
            }
        }
        // print error message
        if (new_topics.length === 0 || new_hosts.length === 0)
        {
            // Discard any possible data received
            model = {
                "kind": "domain_view",
                "domain": domain_id,
                "topics": [],
                "hosts": [],
            }

            // display empty screen label
            emptyScreenLabel.visible = true
        }

        // Update tab name with selected domain id
        domainGraphLayout.update_tab_name("Domain " + domain_id + " View")
    }

    // remove drawn connections
    function clear_graph()
    {
        topic_locations_ = {}
        endpoint_topic_connections_ = {}
        endpoint_painted_ = []
        topic_painted_ = []
        vertical_bar.position = 0
        horizontal_bar.position = 0
        entity_box_width_ = 0;
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
    }
}
