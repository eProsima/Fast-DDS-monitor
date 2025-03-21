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
    property var model: {}                              // domain view graph JSON model
    property int domain_entity_id                       // entity id associated to the domain id
    property int domain_id                              // domain id
    required property string component_id               // mandatory to be included when object created

    // Public signals
    signal update_tab_name(string new_name, string new_icon, string stack_id)  // Update tab name based on selected domain id
    signal openEntitiesMenu(string domainEntityId, string entityId, string currentAlias, string entityKind, int caller)
    signal openTopicMenu(string domainEntityId, string domainId, string entityId, string currentAlias, string entityKind, int caller)
    signal openLoadingGraphDialog()                     // let tab layout know that graph is about to be generated
    signal initialized()                                // let tab layout know that graph has been generated

    // Private properties
    property var topic_locations_: {}                   // topic information needed for connection representation
    property var topic_style_map_: {}                   // map with boolean values to alternate style in topics tags and connections
    property var endpoint_topic_connections_: {}        // endpoint information needed for connection representation
    property var topic_painted_: []                     // already painted topic connection references
    property var endpoint_painted_: []                  // already painted endpoint connection references
    property var pending_endpoints_: []                 // pending endpoints references that have not been resized yet
    property var pending_connections_: []               // pending connections references that have not been generated yet
    property var filtered_topics_: []                   // flitered topic entity id in the graph
    property var endpoints_per_topic: {}                // list of endpoint ids associated to each topic
    property int entity_box_width_: 0                   // entity box width management
    property bool topic_connections_generated: false    // topic side connections generated
    property bool endpoint_connections_generated: false // endpoint side connections generated


    // Private (resize) signals               The signal resize_elements_ will trigger all entities resize methods in
    //    HOST       TOPIC ─┐                 the order displayed in the left figure. All entities width value are
    //  1↓ ... ↓4    5↑    6└─>CONNECTIONS    based on the var entity_box_width which would be updated with the max
    //   ENDPOINT ────┘                       width. After that, connections between endpoints and topics are generated.
    signal resize_elements_()
    signal topics_updated_()
    signal endpoints_updated_()
    signal record_connections_()
    signal topic_visibility_changed_(string endpoint_id, bool new_status)

    // Read only design properties (sizes and colors)
    readonly property int radius_: 10
    readonly property int connection_thickness_: 6
    readonly property int elements_spacing_: 5
    readonly property int containers_spacing_: 100
    readonly property int topic_tag_size_: 150
    readonly property int topic_tag_margin_: 30
    readonly property int max_topic_name_size_: 100
    readonly property int endpoint_height_: 30
    readonly property int first_indentation_: 5
    readonly property int icon_size_: 18
    readonly property int label_height_: 25
    readonly property int spacing_icon_label_: 8
    readonly property int spacing_icon_: 4
    readonly property int scrollbar_min_size_: 8
    readonly property int scrollbar_max_size_: 12
    readonly property int topic_thickness_: 10
    readonly property int wheel_displacement_: 30
    readonly property int timer_initial_ms_interval_: 200
    readonly property int hover_text_offset_: 50
    readonly property int hover_delay_: 250
    readonly property string topic_color_: Theme.grey
    readonly property string topic_color_alias_: "grey" // color alias for svg icons
    readonly property string topic_color2_: Theme.midGrey
    readonly property string topic_color2_alias_: "mid_grey" // color alias for svg icons
    readonly property string host_color_: Theme.darkGrey
    readonly property string user_color_: Theme.eProsimaLightBlue
    readonly property string process_color_: Theme.eProsimaDarkBlue
    readonly property string participant_color_: Theme.whiteSmoke
    readonly property string reader_color_: Theme.eProsimaYellow
    readonly property string writer_color_: Theme.eProsimaGreen


    // Horizontal scroll view for topics section. This will contain also a Flickable that replicates entities height
    // and will move accordingly to display the connections
    Flickable {
        id: topicView
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.leftMargin: entity_box_width_ + elements_spacing_
        width: parent.width - entity_box_width_ - 9*elements_spacing_
        flickableDirection: Flickable.HorizontalFlick
        boundsBehavior: Flickable.StopAtBounds

        contentWidth: topicsList.contentWidth + containers_spacing_
        contentHeight: parent.height

        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOff }
        ScrollBar.horizontal: ScrollBar {
            id: horizontal_bar
            anchors.left: parent.left; anchors.leftMargin: 9*elements_spacing_
            anchors.bottom: parent.bottom
            policy: ScrollBar.AlwaysOn
            visible: topicView.contentWidth > topicView.width
            hoverEnabled: true

            contentItem: Item {
                implicitHeight: scrollbar_min_size_

                Rectangle {
                    anchors.fill: parent
                    anchors.rightMargin: 2
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
            property int yOffset: label_height_ + elements_spacing_
            model: domainGraphLayout.model ? domainGraphLayout.model["topics"] : undefined
            anchors.left: parent.left; anchors.leftMargin: 9 * elements_spacing_
            anchors.top: parent.top; anchors.topMargin: elements_spacing_;
            anchors.bottom: parent.bottom
            contentWidth: contentItem.childrenRect.width
            spacing: -(topic_tag_size_/3 + elements_spacing_)
            orientation: ListView.Horizontal
            interactive: false

            // Resizing management connections
            Connections
            {
                target: domainGraphLayout

                function onEndpoints_updated_()
                {
                    topicsList.record_connections()
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
                        if (c > 1)
                        {
                            // The current item overlaps with the previous one
                            listViewWidth += topicsList.spacing
                        }
                    }
                }
                topicsList.height = listViewHeight
                topicsList.width = listViewWidth
            }

            function record_connections()
            {
                var draw_width = 9*elements_spacing_

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
                    topic_style_map_[topicsList.currentItem.topic_id] = topicsList.currentItem.even_position
                    draw_width += topicsList.currentItem.width + topicsList.spacing
                }

                // announce topics are ready
                topics_updated_()
            }

            // Topic delegated item box with vertical line
            delegate: Rectangle
            {
                property string topic_id: modelData["id"]
                property bool even_position: index % 2 === 0
                implicitWidth: topic_tag.implicitWidth
                height: topicsList.height
                color: "transparent"

                // Topic name and icon
                Rectangle
                {
                    id: topic_tag
                    height: label_height_
                    color: parent.even_position ? topic_color_ : topic_color2_
                    radius: radius_
                    y: !parent.even_position ? topicsList.yOffset : 0
                    property int textFullWidth: text_metrics.width
                    implicitWidth: topicsList.count > 1 ? topic_tag_size_ : Math.max(topic_tag_label.width + topic_tag_margin_, topic_tag_size_)

                    Label {
                        id: topic_tag_label
                        anchors.centerIn: parent
                        text: modelData["alias"]
                        Layout.rightMargin: 2* first_indentation_
                        color: "white"
                        width: topicsList.count > 1 ? max_topic_name_size_ : text.width
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                    }

                    // Save total text size (without eliding)
                    TextMetrics {
                        id: text_metrics
                        text: modelData["alias"]
                    }

                    MouseArea
                    {
                        id: topic_tag_mouse_area
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        hoverEnabled: true
                        onClicked:
                        {
                            if(mouse.button & Qt.RightButton) {
                                openTopicMenu(domain_entity_id, domain_id, modelData["id"], modelData["alias"], modelData["kind"], panels.openMenuCaller.domainGraph)
                            } else {
                                controller.topic_click(modelData["id"])
                            }
                        }
                    }
                    Label {
                        id: hover_label
                        visible: false
                        anchors.top: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: hover_text_offset_
                        ToolTip.text: modelData["alias"]
                        // Show hover only if text is elided
                        ToolTip.visible: topic_tag_mouse_area.containsMouse && text_metrics.width > topic_tag_label.width
                        ToolTip.delay: hover_delay_
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
                    color: parent.even_position ? topic_color_ : topic_color2_
                }

                Connections {
                    target: topicView
                    function onContentXChanged()
                    {
                        domainGraphLayout.topic_visibility_changed(
                            topic_id, ((x + width/2 + topic_thickness_/2 + elements_spacing_) < topicView.contentX))
                    }
                }
            }
        }

        // Section where connections are represented
        Flickable
        {
            id: topicSpace
            anchors.top: parent.top; anchors.topMargin: topicsList.count > 1 ? label_height_ + topicsList.yOffset + 2* elements_spacing_ : label_height_ + 2* elements_spacing_
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
                            if ((topicView.contentX + topicView.width) > topicView.contentWidth) {
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
                topicView.generate_connections()
            }
        }

        // Generate connections in topic side
        function generate_connections()
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
                            ,"arrow_color": topic_style_map_[topic_id] ? topic_color_ : topic_color2_
                            ,"arrow_head_color": topic_style_map_[topic_id] ? "grey" : "mid_grey"
                            ,"background_color": background_color.color
                            ,"endpoint_id": key
                            ,"show_fill_gap": false }
                        var connection_bar = arrow_component.createObject(topic_connections, input)
                        topic_painted_[topic_painted_.length] = key;
                    }
                }
            }

            topic_connections_generated = true
            domainGraphLayout.connections_generated()
        }
    }


    // Left section background (over right section)
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        height: parent.height
        width: entity_box_width_ + 9*elements_spacing_
        color: "white"
    }

    // Entities vertical flickable (left section)
    Flickable {
        id: mainView
        anchors.left: parent.left ; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: entity_box_width_ + elements_spacing_
        anchors.topMargin: topicSpace.anchors.topMargin
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

        // Space where entities will be represented
        Rectangle
        {
            id: mainSpace
            anchors.top: parent.top

            width: hostsList.width + 2*elements_spacing_
            height: hostsList.height < (domainGraphLayout.height - (label_height_ + 2*elements_spacing_))
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
                    id: conn             
                    Connections{
                        target: domainGraphLayout

                        function onTopic_visibility_changed_(endpoint_id, new_status)
                        {
                            conn.topid_hidden(endpoint_id, new_status)
                        }
                    }
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

                    function onResize_elements_()
                    {
                        hostsList.resize()
                        hostsList.resize_elements()
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
                        entity_box_width_ = aux_width
                    }
                }

                // Makes each list element to be resized
                function resize_elements()
                {
                    // iterate over each element in the list item
                    for (var c = 0; c < hostsList.count; c++)
                    {
                        hostsList.currentIndex = c
                        if (hostsList.currentItem != null)
                        {
                            hostsList.currentItem.resize()
                        }
                    }
                }

                // Host delegated item box
                delegate: Item
                {
                    height: host_tag.height + usersList.height
                    width: hostRowLayout.implicitWidth > entity_box_width_
                        ? hostRowLayout.implicitWidth
                        : entity_box_width_

                    function resize()
                    {
                        usersList.resize()
                        usersList.resize_elements()
                    }

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
                        height: modelData["alias"] != "Unknown" ? label_height_ : 0
                        color: host_color_
                        radius: radius_
                        visible: modelData["alias"] != "Unknown"

                        RowLayout {
                            id: hostRowLayout
                            spacing: spacing_icon_label_
                            anchors.centerIn: parent

                            Rectangle {
                                color: "transparent"
                                width: first_indentation_
                            }
                            Rectangle {
                                visible: modelData["status"] != "OK"
                                color: modelData["status"] == "WARNING" ? "transparent" : "white"
                                width: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                height: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                radius: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                IconSVG {
                                    anchors.centerIn: parent
                                    name: modelData["status"] == "WARNING" ? "issues" : "error"
                                    color: modelData["status"] == "WARNING" ? "yellow" : "red"
                                    size: modelData["status"] != "OK"? icon_size_ : 0
                                }
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
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onClicked:
                            {
                                if(mouse.button & Qt.RightButton) {
                                    openEntitiesMenu(domain_entity_id, modelData["id"], modelData["alias"], modelData["kind"], openMenuCaller.domainGraph)
                                } else {
                                    controller.host_click(modelData["id"])
                                }
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
                                entity_box_width_ = aux_width
                            }
                        }

                        // Makes each list element to be resized
                        function resize_elements()
                        {
                            // iterate over each element in the list item
                            for (var c = 0; c < usersList.count; c++)
                            {
                                usersList.currentIndex = c
                                if (usersList.currentItem != null)
                                {
                                    usersList.currentItem.resize()
                                }
                            }
                        }


                        // User delegated item box
                        delegate: Item
                        {
                            height: user_tag.height + processesList.height
                            width: userRowLayout.implicitWidth > (entity_box_width_-(2*elements_spacing_))
                                ? userRowLayout.implicitWidth
                                : entity_box_width_-(2*elements_spacing_)

                            function resize()
                            {
                                processesList.resize()
                                processesList.resize_elements()
                            }

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
                                height: modelData["alias"] != "Unknown" ? label_height_ : 0
                                color: user_color_
                                radius: radius_
                                visible: modelData["alias"] != "Unknown"

                                RowLayout {
                                    id: userRowLayout
                                    spacing: spacing_icon_label_
                                    anchors.centerIn: parent

                                    Rectangle {
                                        color: "transparent"
                                        width: first_indentation_
                                    }
                                    Rectangle {
                                        visible: modelData["status"] != "OK"
                                        color: modelData["status"] == "WARNING" ? "transparent" : "white"
                                        width: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                        height: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                        radius: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                        IconSVG {
                                            anchors.centerIn: parent
                                            name: modelData["status"] == "WARNING" ? "issues" : "error"
                                            color: modelData["status"] == "WARNING" ? "yellow" : "red"
                                            size: modelData["status"] != "OK"? icon_size_ : 0
                                        }
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
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                                    onClicked:
                                    {
                                        if(mouse.button & Qt.RightButton) {
                                            openEntitiesMenu(domain_entity_id, modelData["id"], modelData["alias"], modelData["kind"], openMenuCaller.domainGraph)
                                        } else {
                                            controller.user_click(modelData["id"])
                                        }
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
                                        entity_box_width_ = aux_width
                                    }
                                }

                                // Makes each list element to be resized
                                function resize_elements()
                                {
                                    // iterate over each element in the list item
                                    for (var c = 0; c < processesList.count; c++)
                                    {
                                        processesList.currentIndex = c
                                        if (processesList.currentItem != null)
                                        {
                                            processesList.currentItem.resize()
                                        }
                                    }
                                }

                                // Process delegated item box
                                delegate: Item
                                {
                                    height: process_tag.height + participantsList.height
                                    width: processRowLayout.implicitWidth > (entity_box_width_-(4*elements_spacing_))
                                        ? processRowLayout.implicitWidth
                                        : entity_box_width_-(4*elements_spacing_)

                                    function resize()
                                    {
                                        participantsList.resize()
                                        participantsList.resize_elements()
                                    }

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
                                        height: modelData["alias"] != "Unknown" ? label_height_ : 0
                                        color: process_color_
                                        radius: radius_
                                        visible: modelData["alias"] != "Unknown"

                                        RowLayout {
                                            id: processRowLayout
                                            spacing: spacing_icon_label_
                                            anchors.centerIn: parent

                                            Rectangle {
                                                color: "transparent"
                                                width: first_indentation_
                                            }
                                            Rectangle {
                                                visible: modelData["status"] != "OK"
                                                color: modelData["status"] == "WARNING" ? "transparent" : "white"
                                                width: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                height: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                radius: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                IconSVG {
                                                    anchors.centerIn: parent
                                                    name: modelData["status"] == "WARNING" ? "issues" : "error"
                                                    color: modelData["status"] == "WARNING" ? "yellow" : "red"
                                                    size: modelData["status"] != "OK"? icon_size_ : 0
                                                }
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
                                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                                            onClicked:
                                            {
                                                if(mouse.button & Qt.RightButton) {
                                                    openEntitiesMenu(domain_entity_id, modelData["id"], modelData["alias"], modelData["kind"], openMenuCaller.domainGraph)
                                                } else {
                                                    controller.process_click(modelData["id"])
                                                }
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
                                                entity_box_width_ = aux_width
                                            }
                                        }

                                        // Makes each list element to be resized
                                        function resize_elements()
                                        {
                                            // iterate over each element in the list item
                                            for (var c = 0; c < participantsList.count; c++)
                                            {
                                                participantsList.currentIndex = c
                                                if (participantsList.currentItem != null)
                                                {
                                                    participantsList.currentItem.resize()
                                                }
                                            }
                                        }

                                        // Participant delegated item box
                                        delegate: Item
                                        {
                                            height: participant_tag.height + endpointsList.height
                                            width: participant_tag.implicitWidth > (entity_box_width_-(6*elements_spacing_))
                                                ? participant_tag.implicitWidth
                                                : entity_box_width_-(6*elements_spacing_)

                                            function resize()
                                            {
                                                endpointsList.resize()
                                                endpointsList.resize_elements()
                                            }

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
                                                implicitWidth: (participantRowLayout.implicitWidth + participant_app_icon.width)
                                                    > (entity_box_width_-(6*elements_spacing_))
                                                    ? (participantRowLayout.implicitWidth + participant_app_icon.width)
                                                    : entity_box_width_-(6*elements_spacing_)
                                                height: label_height_
                                                color: participant_color_
                                                radius: radius_

                                                Rectangle {
                                                    id: dds_vendor_icon
                                                    visible: modelData["dds_vendor"] != "UNKNOWN"
                                                    anchors.left: parent.left
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    width: icon_size_ + 2*spacing_icon_label_
                                                    height: icon_size_
                                                    color: "transparent"

                                                    Image {
                                                        smooth: true
                                                        visible: parent.visible
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        source: modelData["dds_vendor"] == "UNKNOWN" ? "" :
                                                                "/resources/images/app_icons/" + modelData["dds_vendor"] + ".svg"
                                                        readonly property int amlip_offset_: 5
                                                        // SAFEDDS is wider than it is tall, so its size is increased a little
                                                        // bit to make it look like the same aspect ratio as the other icons
                                                        sourceSize.width: modelData["dds_vendor"] == "SAFEDDS"
                                                                ? parent.height + amlip_offset_ : parent.height
                                                        sourceSize.height: modelData["dds_vendor"] == "SAFEDDS"
                                                                ? parent.height + amlip_offset_ : parent.height
                                                    }
                                                }

                                                RowLayout {
                                                    id: participantRowLayout
                                                    spacing: spacing_icon_label_
                                                    anchors.centerIn: parent

                                                    Rectangle {
                                                        color: "transparent"
                                                        width: icon_size_
                                                    }
                                                    Rectangle {
                                                        visible: modelData["status"] != "OK"
                                                        color: modelData["status"] == "WARNING" ? "transparent" : "white"
                                                        width: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                        height: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                        radius: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                        IconSVG {
                                                            anchors.centerIn: parent
                                                            name: modelData["status"] == "WARNING" ? "issues" : "error"
                                                            color: modelData["status"] == "WARNING" ? "yellow" : "red"
                                                            size: modelData["status"] != "OK"? icon_size_ : 0
                                                        }
                                                    }
                                                    IconSVG {
                                                        name: "participant"
                                                        size: icon_size_
                                                    }
                                                    Label {
                                                        text: modelData["alias"]
                                                    }
                                                    Rectangle {
                                                        color: "transparent"
                                                        width: icon_size_
                                                    }
                                                }
                                                Rectangle {
                                                    id: participant_app_icon
                                                    visible: modelData["app_id"] != "UNKNOWN_APP"
                                                    anchors.right: parent.right
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    width: icon_size_ + 2*spacing_icon_label_
                                                    height: icon_size_
                                                    color: "transparent"

                                                    Image {
                                                        smooth: true
                                                        visible: parent.visible
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        source: modelData["app_id"] == "UNKNOWN_APP" ? "" :
                                                                "/resources/images/app_icons/" + modelData["app_id"] + ".svg"
                                                        readonly property int amlip_offset_: 5
                                                        // AML_IP is wider than it is tall, so its size is increased a little
                                                        // bit to make it look like the same aspect ratio as the other icons
                                                        // It also happens with FASTDDS_VISUALIZER
                                                        sourceSize.width: modelData["app_id"] == "AML_IP" || modelData["app_id"] == "FASTDDS_VISUALIZER"
                                                                ? parent.height + amlip_offset_ : parent.height
                                                        sourceSize.height: modelData["app_id"] == "AML_IP" || modelData["app_id"] == "FASTDDS_VISUALIZER"
                                                                ? parent.height + amlip_offset_ : parent.height
                                                    }
                                                }
                                                MouseArea
                                                {
                                                    anchors.fill: parent
                                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                                                    onClicked:
                                                    {
                                                        if(mouse.button & Qt.RightButton) {
                                                            openEntitiesMenu(domain_entity_id, modelData["id"], modelData["alias"], modelData["kind"], openMenuCaller.domainGraph)
                                                        } else {
                                                            controller.participant_click(modelData["id"])
                                                        }
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

                                                // Connection management
                                                Connections
                                                {
                                                    target: domainGraphLayout

                                                    function onRecord_connections_()
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
                                                        entity_box_width_ = aux_width
                                                    }
                                                }

                                                // Makes each list element to be resized
                                                function resize_elements()
                                                {
                                                    // remove current endpoints from pending queue
                                                    for (var c = 0; c < endpointsList.count; c++)
                                                    {
                                                        endpointsList.currentIndex = c
                                                        if (endpointsList.currentItem != null)
                                                        {
                                                            if (pending_endpoints_.includes(endpointsList.currentItem.get_endpoint_id()))
                                                            {
                                                                pending_connections_[pending_connections_.length] = endpointsList.currentItem.get_endpoint_id()
                                                                pending_endpoints_.splice(pending_endpoints_.indexOf(endpointsList.currentItem.get_endpoint_id()), 1)
                                                            }
                                                        }
                                                    }

                                                    if (pending_endpoints_.length == 0)
                                                    {
                                                        domainGraphLayout.record_connections_()
                                                    }
                                                }

                                                function record_connections()
                                                {
                                                    for (var c = 0; c < endpointsList.count; c++)
                                                    {
                                                        endpointsList.currentIndex = c
                                                        if (pending_connections_.includes(endpointsList.currentItem.get_endpoint_id()))
                                                        {
                                                            pending_connections_.splice(pending_connections_.indexOf(endpointsList.currentItem.get_endpoint_id()), 1)
                                                            endpointsList.currentItem.record_connection()
                                                        }
                                                    }

                                                    if (pending_connections_.length == 0)
                                                    {
                                                        stop_timer()
                                                        endpoints_updated_()
                                                    }
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
                                                        var src_y = globalCoordinates.y + (endpointComponent.height / 2)
                                                        var left_direction = modelData["kind"] == "DataReader"
                                                        var right_direction = modelData["kind"] == "DataWriter"

                                                        endpoint_topic_connections_[modelData["id"]] = {
                                                            "id":  modelData["id"], "left_direction": left_direction,
                                                            "right_direction": right_direction, "x": src_x, "y": src_y,
                                                            "destination_id": modelData["topic"]
                                                        }
                                                    }

                                                    function get_endpoint_id()
                                                    {
                                                        return modelData["id"]
                                                    }

                                                    // background
                                                    Rectangle
                                                    {
                                                        id: endpoint_background
                                                        width: parent.width
                                                        height: endpoint_height_
                                                        color: modelData["kind"] == "DataReader" ? reader_color_ : writer_color_
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
                                                                width: first_indentation_
                                                            }
                                                            Rectangle {
                                                                visible: modelData["status"] != "OK"
                                                                color: modelData["status"] == "WARNING" ? "transparent" : "white"
                                                                width: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                                height: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                                radius: modelData["status"] != "OK"? icon_size_ + spacing_icon_: 0
                                                                IconSVG {
                                                                    visible: modelData["status"] == "WARNING"
                                                                    anchors.centerIn: parent
                                                                    name: "issues"
                                                                    color: "white"
                                                                    size:  icon_size_ * (3/2)
                                                                }
                                                                IconSVG {
                                                                    anchors.centerIn: parent
                                                                    name: modelData["status"] == "WARNING" ? "issues" : "error"
                                                                    color: modelData["status"] == "WARNING" ? "yellow" : "red"
                                                                    size: modelData["status"] != "OK"? icon_size_ : 0
                                                                }
                                                            }
                                                            IconSVG {
                                                                name: modelData["kind"] == "DataReader"
                                                                    ? "datareader" : "datawriter"
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
                                                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                                                            onClicked:
                                                            {
                                                                if(mouse.button & Qt.RightButton) {
                                                                    openEntitiesMenu(domain_entity_id, modelData["id"], modelData["alias"], modelData["kind"], openMenuCaller.domainGraph)
                                                                } else {
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
            }

            // Resizing management connections
            Connections
            {
                target: domainGraphLayout

                function onTopics_updated_()
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
                                ,"arrow_color": topic_style_map_[topic_id] ? topic_color_ : topic_color2_, "background_color": background_color.color
                                ,"arrow_head_color": topic_style_map_[topic_id] ? topic_color_alias_ : topic_color2_alias_
                                ,"endpoint_id": key
                                ,"show_fill_gap": true }
                            var connection_bar = arrow_component.createObject(mainSpace, input)
                            endpoint_painted_[endpoint_painted_.length] = key
                        }
                    }
                }

                endpoint_connections_generated = true
                domainGraphLayout.connections_generated()
            }
        }
    }

    // top section to cut entities layout and display the REFRESH button
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        height: topicsList.count > 1? label_height_ + topicsList.yOffset + 2* elements_spacing_: 2* elements_spacing_ + label_height_
        width: entity_box_width_ + 9*elements_spacing_
        color: "white"

        // Refresh button
        Button{
            id: refresh_button
            width: (parent.width /2) < 150 ? 150 : parent.width /2
            height: label_height_
            anchors.top: parent.top; anchors.topMargin: elements_spacing_
            anchors.left:  parent.left
            anchors.leftMargin: ((entity_box_width_/2) + elements_spacing_ - (refresh_button.width /2)) < 40
                ? 5* elements_spacing_ : (entity_box_width_/2) + elements_spacing_ - (refresh_button.width /2)
            text: "Refresh"

            onClicked:{
                domainGraphLayout.openLoadingGraphDialog()
                load_model()
            }
        }
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

    Timer {
        id: safety_timer
        interval: timer_initial_ms_interval_; running: false
        onTriggered: {
            interval += interval
            load_model()
        }
    }
    function stop_timer() {
        if (safety_timer.running)
        {
            safety_timer.stop()
            safety_timer.interval = timer_initial_ms_interval_
        }
    }

    // Obtain given domain id graph JSON model
    function load_model()
    {
        if (filtered_topics_.length > 0)
        {
            filter_model_by_topic (filtered_topics_[filtered_topics_.length-1])
        }
        else
        {
            filter_model_by_topic ("")
        }
    }

    // Filter model by topic
    function filter_model_by_topic (topic_id)
    {
        // topic id management
        var topic_names = []
        if (topic_id != "" && !filtered_topics_.includes(topic_id))
        {
            filtered_topics_[filtered_topics_.length] = topic_id;
        }

        // clear internal models
        clear_graph()

        // Obtain model from backend
        var model_string = controller.get_domain_view_graph(domain_entity_id)

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
                        if (filtered_topics_.length > 0)
                        {
                            for (var i = 0; i < filtered_topics_.length; i++)
                            {
                                if (filtered_topics_[i] == topic)
                                {
                                    topic_names[i] = new_model["topics"][topic]["alias"]
                                    new_topics[new_topics.length] = {
                                        "id":topic,
                                        "kind":"Topic",
                                        "alias":new_model["topics"][topic]["alias"]
                                    }
                                    endpoints_per_topic[topic] = []
                                }
                            }
                        }
                        else
                        {
                            new_topics[new_topics.length] = {
                                "id":topic,
                                "kind":"Topic",
                                "alias":new_model["topics"][topic]["alias"]
                            }
                            endpoints_per_topic[topic] = []
                        }
                    }
                }
                var accum_y = 0
                var host_temp_y = 0
                for (var host in new_model["hosts"])
                {
                    var discard_host = true
                    var metatraffic_ = new_model["hosts"][host]["metatraffic"]
                    if (metatraffic_ != true || is_metatraffic_visible_)
                    {
                        accum_y += label_height_ + elements_spacing_
                        var new_users = []
                        var user_temp_y = accum_y
                        for (var user in new_model["hosts"][host]["users"])
                        {
                            var discard_user = true
                            var metatraffic_ = new_model["hosts"][host]["users"][user]["metatraffic"]
                            if (metatraffic_ != true || is_metatraffic_visible_)
                            {
                                accum_y += label_height_ + elements_spacing_
                                var new_processes = []
                                var process_temp_y = accum_y
                                for (var process in new_model["hosts"][host]["users"][user]["processes"])
                                {
                                    var discard_process = true
                                    var metatraffic_ = new_model["hosts"][host]["users"][user]["processes"][process]["metatraffic"]
                                    if (metatraffic_ != true || is_metatraffic_visible_)
                                    {
                                        accum_y += label_height_ + elements_spacing_
                                        var new_participants = []
                                        var participant_temp_y = accum_y
                                        for (var participant in new_model["hosts"][host]["users"][user]["processes"][process]["participants"])
                                        {
                                            var discard_participant = true
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
                                                        if ((!filtered_topics_.length) || (filtered_topics_.length > 0
                                                            && filtered_topics_.includes(new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["topic"])))
                                                        {
                                                            discard_participant = false; discard_process = false; discard_user = false; discard_host = false
                                                            var kind = "DataWriter"
                                                            if (new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["kind"] == "datareader")
                                                            {
                                                                kind = "DataReader"
                                                            }
                                                            var endpoint_topic = new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["topic"]
                                                            new_endpoints[new_endpoints.length] = {
                                                                "id":endpoint,
                                                                "kind":kind,
                                                                "alias":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["alias"],
                                                                "status":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["status"],
                                                                "topic": endpoint_topic,
                                                                "accum_y":accum_y
                                                            }
                                                            endpoints_per_topic[endpoint_topic][endpoints_per_topic[endpoint_topic].length] = endpoint
                                                            accum_y += endpoint_height_ + elements_spacing_
                                                            pending_endpoints_[pending_endpoints_.length] = endpoint
                                                        }
                                                    }
                                                }
                                                if (!discard_participant)
                                                {
                                                    new_participants[new_participants.length] = {
                                                        "id":participant,
                                                        "kind": "DomainParticipant",
                                                        "alias":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["alias"],
                                                        "status":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["status"],
                                                        "app_id":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["app_id"],
                                                        "app_metadata":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["app_metadata"],
                                                        "dds_vendor":new_model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["dds_vendor"],
                                                        "endpoints":new_endpoints
                                                    }
                                                    accum_y += elements_spacing_
                                                    participant_temp_y = accum_y
                                                }
                                                else
                                                {
                                                    accum_y = participant_temp_y
                                                }
                                            }
                                        }
                                        if (!discard_process)
                                        {
                                            new_processes[new_processes.length] = {
                                                "id":process,
                                                "kind":"Process",
                                                "alias":new_model["hosts"][host]["users"][user]["processes"][process]["alias"],
                                                "pid": new_model["hosts"][host]["users"][user]["processes"][process]["pid"],
                                                "status":new_model["hosts"][host]["users"][user]["processes"][process]["status"],
                                                "participants":new_participants
                                            }
                                            accum_y += elements_spacing_
                                            process_temp_y = accum_y
                                        }
                                        else
                                        {
                                            accum_y = process_temp_y
                                        }
                                    }
                                }
                                if (!discard_user)
                                {
                                    new_users[new_users.length] = {
                                        "id":user,
                                        "kind": "User",
                                        "alias":new_model["hosts"][host]["users"][user]["alias"],
                                        "status":new_model["hosts"][host]["users"][user]["status"],
                                        "processes":new_processes
                                    }
                                    accum_y += elements_spacing_
                                    user_temp_y = accum_y
                                }
                                else
                                {
                                    accum_y = user_temp_y
                                }
                            }
                        }
                        if (!discard_host)
                        {
                            new_hosts[new_hosts.length] = {
                                "id":host,
                                "kind":"Host",
                                "alias":new_model["hosts"][host]["alias"],
                                "status":new_model["hosts"][host]["status"],
                                "users":new_users
                            }
                            accum_y += elements_spacing_
                            host_temp_y = accum_y
                        }
                        else
                        {
                            accum_y = host_temp_y
                        }
                    }

                }
                model = {
                    "kind": new_model["kind"],
                    "domain": new_model["domain"],
                    "topics": new_topics,
                    "hosts": new_hosts,
                }

                // recovery timer starts
                safety_timer.start()

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

            // disable recovery timer
            stop_timer();

            // display empty screen label
            emptyScreenLabel.visible = true

            // stop animation
            domainGraphLayout.initialized()
        }

        // Update tab name with selected domain id
        if (filtered_topics_.length > 0)
        {
            if (filtered_topics_.length == 1)
            {
                domainGraphLayout.update_tab_name(topic_names[0] + " Topic View", "topic", component_id)
            }
            else
            {
                var print_topic_names = topic_names[0]
                for (var i = 1; i < topic_names.length -1; i++)
                {
                    print_topic_names += ", " + topic_names[i]
                }
                if (print_topic_names.length-1 > 0)
                {
                    print_topic_names += " and " + topic_names[topic_names.length-1]
                }

                domainGraphLayout.update_tab_name(print_topic_names + " Topics View", "topic", component_id)
            }
        }
        else
        {
            domainGraphLayout.update_tab_name("Domain " + domain_id + " View", "domain_graph", component_id)
        }
    }

    // remove drawn connections
    function clear_graph()
    {
        topic_locations_ = {}
        topic_style_map_ = {}
        endpoint_topic_connections_ = {}
        endpoint_painted_ = []
        topic_painted_ = []
        pending_endpoints_ = []
        pending_connections_ = []
        endpoints_per_topic = {}
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

    // check if model contains entity
    function contains_entity(domainEntityId, entityId)
    {
        // check if domainEntityId has content
        if (domainEntityId != "")
        {
            // belongs to the current domain
            if (domain_entity_id.toString() != domainEntityId)
            {
                return false
            }
        }
        // check all entities by entityId

        // check domain
        if(domain_entity_id.toString() == entityId)
        {
            return true
        }

        // check topics
        for (var topic in model["topics"])
        {
            if (model["topics"][topic]["id"] == entityId)
            {
                return true
            }
        }

        // check entities
        for (var host in model["hosts"])
        {
            if (model["hosts"][host]["id"] == entityId)
            {
                return true
            }
            else
            {
                for (var user in model["hosts"][host]["users"])
                {
                    if (model["hosts"][host]["users"][user]["id"] == entityId)
                    {
                        return true
                    }
                    else
                    {
                        for (var process in model["hosts"][host]["users"][user]["processes"])
                        {
                            if (model["hosts"][host]["users"][user]["processes"][process]["id"] == entityId)
                            {
                                return true
                            }
                            else
                            {
                                for (var participant in model["hosts"][host]["users"][user]["processes"][process]["participants"])
                                {
                                    if (model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["id"] == entityId)
                                    {
                                        return true
                                    }
                                    else
                                    {
                                        for (var endpoint in model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"])
                                        {
                                            if (model["hosts"][host]["users"][user]["processes"][process]["participants"][participant]["endpoints"][endpoint]["id"] == entityId)
                                            {
                                                return true
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


        // not found yet
        return false
    }

    // report to the graph connections that the endpoint associated topic is not currently in view
    function topic_visibility_changed(topic_id, inView)
    {
        if (topic_id in endpoints_per_topic)
        {
            for (var i = 0; i < endpoints_per_topic[topic_id].length; i++)
            {
                domainGraphLayout.topic_visibility_changed_(endpoints_per_topic[topic_id][i], inView)
            }
        }
    }

    // set the graph as initialized
    function connections_generated()
    {
        if (domainGraphLayout.topic_connections_generated && domainGraphLayout.endpoint_connections_generated)
        {
            domainGraphLayout.topic_connections_generated = false
            domainGraphLayout.endpoint_connections_generated = false
            domainGraphLayout.initialized()
        }
    }
}
