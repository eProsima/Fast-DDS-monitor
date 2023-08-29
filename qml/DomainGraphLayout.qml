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

Item
{
    id: domainGraphLayout

    // Public properties
    property var model: {}

    // Private properties
    property var topic_locations: {}
    property var endpoint_topic_connections: {}
    property int max_host_width_: 0
    property int max_user_width_: 0
    property int max_process_width_: 0
    property int max_participant_width_: 0
    property int max_endpoint_width_: 0

    // Private signals
    signal resize_elements()
    signal topics_updated()
    signal endpoints_updated()
    signal participants_updated()
    signal processes_updated()
    signal users_updated()
    signal hosts_updated()

    // Read only design properties
    readonly property int spacingIconLabel: 8
    readonly property int iconSize: 18
    readonly property int firstIndentation: 5
    readonly property int elementsSpacing: 12
    readonly property int connection_thickness: 10
    readonly property string topicColor: "grey"
    readonly property string hostColor: "green"
    readonly property string userColor: "blue"
    readonly property string processColor: "red"
    readonly property string participantColor: "yellow"
    readonly property string readerColor: "orange"
    readonly property string writerColor: "purple"

    Component.onCompleted:
    {
        load_model()
        resize_elements()
    }

    Connections {
        target: domainGraphLayout

        function onHosts_updated()
        {
            domainGraphLayout.create_connections()
        }
    }

    Flickable {
        id: mainView
        anchors.fill: parent

        contentWidth: mainSpace.width
        contentHeight: mainSpace.height

        ScrollBar.horizontal: ScrollBar { id: horizontal_bar; active: vertical_bar.active }
        ScrollBar.vertical: ScrollBar { id: vertical_bar; active: horizontal_bar.active }

        Rectangle
        {
            id: mainSpace

            width: hostsList.width + topicsList.width
            height: hostsList.height

            ListView
            {
                id: topicsList
                model: domainGraphLayout.model["topics"]
                anchors.left: hostsList.right; anchors.leftMargin: 5*elementsSpacing; /*anchors.right: parent.right*/
                anchors.top: parent.top; anchors.topMargin: elementsSpacing; anchors.bottom: parent.bottom
                contentWidth: contentItem.childrenRect.width
                spacing: elementsSpacing
                orientation: ListView.Horizontal
                interactive: false

                Connections
                {
                    target: domainGraphLayout

                    function onResize_elements()
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

                    topicsList.height = listViewHeight
                    topicsList.width = listViewWidth + 10* elementsSpacing
                    topics_updated()
                }

                delegate: Rectangle
                {
                    implicitWidth: topic_tag.implicitWidth
                    height: parent.height

                    Rectangle
                    {
                        id: topic_tag
                        implicitWidth: topicRowLayout.implicitWidth
                        height: 35
                        color: topicColor

                        RowLayout {
                            id: topicRowLayout
                            spacing: spacingIconLabel
                            anchors.centerIn: parent

                            IconSVG {
                                name: "topic"
                                size: iconSize
                                Layout.leftMargin: firstIndentation
                            }
                            Label {
                                text: modelData["alias"]
                                Layout.rightMargin: firstIndentation
                            }
                        }
                    }

                    Rectangle
                    {
                        id: topic_down_bar
                        anchors.top: topic_tag.bottom
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: topic_tag.horizontalCenter
                        width: 10
                        color: topicColor
                        Component.onCompleted:
                        {
                            topic_locations[modelData["id"]] = {"x" : topic_down_bar.x}
                        }
                    }
                }
            }
            ListView
            {
                id: hostsList
                model: domainGraphLayout.model["hosts"]
                anchors.top: parent.top; anchors.topMargin: elementsSpacing
                anchors.left: parent.left; anchors.leftMargin: elementsSpacing
                interactive: false
                spacing: elementsSpacing

                Connections
                {
                    target: domainGraphLayout

                    function onUsers_updated()
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
                        listViewHeight += hostsList.visibleChildren[i].height + elementsSpacing
                        var min_width = hostsList.visibleChildren[i].width
                        for (var j = 0; j < hostsList.visibleChildren[i].visibleChildren.length; j++)
                        {
                            min_width = Math.max(min_width, hostsList.visibleChildren[i].visibleChildren[j].width)
                        }
                        listViewWidth  = Math.max(listViewWidth, min_width)
                        max_host_width_ = Math.max(max_host_width_, listViewWidth)
                        max_host_width_ = Math.max(max_host_width_, (2*elementsSpacing)+max_user_width_)
                        hostsList.visibleChildren[i].width = max_host_width_
                    }

                    hostsList.height = listViewHeight + elementsSpacing
                    hostsList.width = max_host_width_
                    hosts_updated()
                }

                delegate: Item
                {
                    height: host_tag.height + usersList.height
                    width: max_host_width_ == 0 ? host_tag.implicitWidth : max_host_width_

                    Rectangle
                    {
                        id: host_background
                        height: parent.height
                        width: parent.width
                        color: hostColor
                    }

                    Rectangle
                    {
                        id: host_tag
                        anchors.horizontalCenter: parent.horizontalCenter
                        implicitWidth: max_host_width_ == 0 ? hostRowLayout.implicitWidth : max_host_width_
                        height: 35
                        color: hostColor

                        RowLayout {
                            id: hostRowLayout
                            anchors.centerIn: parent

                            IconSVG {
                                visible: modelData["status"] != "ok"
                                name: "issues"
                                size: iconSize
                                Layout.leftMargin: firstIndentation
                            }
                            IconSVG {
                                name: "process"
                                size: iconSize
                                Layout.leftMargin: modelData["status"] != "ok" ? 0 : firstIndentation
                            }
                            Label {
                                text: modelData["alias"]
                                Layout.rightMargin: firstIndentation
                            }
                        }
                        Rectangle {
                            visible: host_tag.implicitWidth < max_host_width_
                            anchors.left: host_tag.right
                            anchors.verticalCenter: parent.verticalCenter
                            height: host_tag.height
                            width: max_host_width_ - host_tag.implicitWidth
                            color: host_background.color
                        }
                    }

                    ListView
                    {
                        id: usersList
                        model: modelData["users"]
                        anchors.top: host_tag.bottom; anchors.topMargin: elementsSpacing
                        anchors.left: parent.left; anchors.leftMargin: elementsSpacing
                        anchors.right: parent.right; anchors.rightMargin: elementsSpacing
                        interactive: false
                        spacing: elementsSpacing

                        Connections
                        {
                            target: domainGraphLayout

                            function onProcesses_updated()
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
                                listViewHeight += usersList.visibleChildren[i].height + elementsSpacing
                                var min_width = usersList.visibleChildren[i].width
                                for (var j = 0; j < usersList.visibleChildren[i].visibleChildren.length; j++)
                                {
                                    min_width = Math.max(min_width, usersList.visibleChildren[i].visibleChildren[j].width)
                                }
                                listViewWidth  = Math.max(listViewWidth, min_width)
                                max_user_width_ = Math.max(max_user_width_, listViewWidth)
                                max_user_width_ = Math.max(max_user_width_, (2*elementsSpacing)+max_process_width_)
                                usersList.visibleChildren[i].width = max_user_width_
                            }

                            usersList.height = listViewHeight + elementsSpacing
                            usersList.width = max_user_width_
                            users_updated()
                        }

                        delegate: Item
                        {
                            height: user_tag.height + processesList.height
                            width: max_user_width_ == 0 ? user_tag.implicitWidth : max_user_width_

                            Rectangle
                            {
                                id: user_background
                                height: parent.height
                                width: parent.width
                                color: userColor
                            }

                            Rectangle
                            {
                                id: user_tag
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                                implicitWidth: max_user_width_ == 0 ? userRowLayout.implicitWidth : max_user_width_
                                height: 35
                                color: userColor

                                RowLayout {
                                    id: userRowLayout
                                    anchors.centerIn: parent

                                    IconSVG {
                                        visible: modelData["status"] != "ok"
                                        name: "issues"
                                        size: iconSize
                                        Layout.leftMargin: firstIndentation
                                    }
                                    IconSVG {
                                        name: "process"
                                        size: iconSize
                                        Layout.leftMargin: modelData["status"] != "ok" ? 0 : firstIndentation
                                    }
                                    Label {
                                        text: modelData["alias"]
                                        Layout.rightMargin: firstIndentation
                                    }
                                }
                                Rectangle {
                                    visible: user_tag.implicitWidth < max_user_width_
                                    anchors.left: user_tag.right
                                    anchors.verticalCenter: parent.verticalCenter
                                    height: user_tag.height
                                    width: max_user_width_ - user_tag.implicitWidth
                                    color: user_background.color
                                }
                            }

                            ListView
                            {
                                id: processesList
                                model: modelData["processes"]
                                anchors.top: user_tag.bottom; anchors.topMargin: elementsSpacing
                                anchors.left: parent.left; anchors.leftMargin: elementsSpacing
                                anchors.right: parent.right; anchors.rightMargin: elementsSpacing
                                interactive: false
                                spacing: elementsSpacing

                                Connections
                                {
                                    target: domainGraphLayout

                                    function onParticipants_updated()
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
                                        listViewHeight += processesList.visibleChildren[i].height + elementsSpacing
                                        var min_width = processesList.visibleChildren[i].width
                                        for (var j = 0; j < processesList.visibleChildren[i].visibleChildren.length; j++)
                                        {
                                            min_width = Math.max(min_width, processesList.visibleChildren[i].visibleChildren[j].width)
                                        }
                                        listViewWidth  = Math.max(listViewWidth, min_width)
                                        max_process_width_ = Math.max(max_process_width_, listViewWidth)
                                        max_process_width_ = Math.max(max_process_width_, (2*elementsSpacing)+max_participant_width_)
                                        processesList.visibleChildren[i].width = max_process_width_
                                    }

                                    processesList.height = listViewHeight + elementsSpacing
                                    processesList.width = max_process_width_
                                    processes_updated()
                                }

                                delegate: Item
                                {
                                    height: process_tag.height + participantsList.height
                                    width: max_process_width_ == 0 ? process_tag.implicitWidth : max_process_width_

                                    Rectangle
                                    {
                                        id: process_background
                                        height: parent.height
                                        width: parent.width
                                        color: processColor
                                    }

                                    Rectangle
                                    {
                                        id: process_tag
                                        anchors.top: parent.top
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        implicitWidth: max_process_width_ == 0 ? processRowLayout.implicitWidth : max_process_width_
                                        height: 35
                                        color: processColor

                                        RowLayout {
                                            id: processRowLayout
                                            anchors.centerIn: parent

                                            IconSVG {
                                                visible: modelData["status"] != "ok"
                                                name: "issues"
                                                size: iconSize
                                                Layout.leftMargin: firstIndentation
                                            }
                                            IconSVG {
                                                name: "process"
                                                size: iconSize
                                                Layout.leftMargin: modelData["status"] != "ok" ? 0 : firstIndentation
                                            }
                                            Label {
                                                text: modelData["alias"]
                                                Layout.rightMargin: firstIndentation
                                            }
                                        }
                                        Rectangle {
                                            visible: process_tag.implicitWidth < max_process_width_
                                            anchors.left: process_tag.right
                                            anchors.verticalCenter: parent.verticalCenter
                                            height: process_tag.height
                                            width: max_process_width_ - process_tag.implicitWidth
                                            color: process_background.color
                                        }
                                    }
                                    ListView
                                    {
                                        id: participantsList
                                        model: modelData["participants"]
                                        anchors.top: process_tag.bottom; anchors.topMargin: elementsSpacing
                                        anchors.left: parent.left; anchors.leftMargin: elementsSpacing
                                        anchors.right: parent.right; anchors.rightMargin: elementsSpacing
                                        interactive: false
                                        spacing: elementsSpacing

                                        Connections
                                        {
                                            target: domainGraphLayout

                                            function onEndpoints_updated()
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
                                                listViewHeight += participantsList.visibleChildren[i].height + elementsSpacing
                                                var min_width = participantsList.visibleChildren[i].width
                                                for (var j = 0; j < participantsList.visibleChildren[i].visibleChildren.length; j++)
                                                {
                                                    min_width = Math.max(min_width, participantsList.visibleChildren[i].visibleChildren[j].width)
                                                }
                                                listViewWidth  = Math.max(listViewWidth, min_width)
                                                max_participant_width_ = Math.max(max_participant_width_, listViewWidth)
                                                max_participant_width_ = Math.max(max_participant_width_, (2*elementsSpacing)+max_endpoint_width_)
                                                participantsList.visibleChildren[i].width = max_participant_width_
                                            }

                                            participantsList.height = listViewHeight + elementsSpacing
                                            participantsList.width = max_participant_width_
                                            participants_updated()
                                        }

                                        delegate: Item
                                        {
                                            height: participant_tag.height + endpointsList.height
                                            width: max_participant_width_ == 0 ? participant_tag.implicitWidth : max_participant_width_

                                            Rectangle
                                            {
                                                id: participant_background
                                                height: parent.height
                                                width: parent.width
                                                color: participantColor
                                            }
                                            Rectangle
                                            {
                                                id: participant_tag
                                                anchors.top: parent.top
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                implicitWidth: max_participant_width_ == 0 ? participantRowLayout.implicitWidth : max_participant_width_
                                                height: 35
                                                color: participantColor

                                                RowLayout {
                                                    id: participantRowLayout
                                                    anchors.centerIn: parent

                                                    IconSVG {
                                                        visible: modelData["status"] != "ok"
                                                        name: "issues"
                                                        size: modelData["status"] != "ok"? iconSize : 0
                                                        Layout.leftMargin: modelData["status"] != "ok" ? firstIndentation : 0
                                                    }
                                                    IconSVG {
                                                        name: modelData["kind"]
                                                        size: iconSize
                                                    }
                                                    Label {
                                                        text: modelData["alias"]
                                                        Layout.rightMargin: spacingIconLabel + firstIndentation
                                                    }
                                                }
                                                Rectangle {
                                                    visible: participant_tag.implicitWidth < max_participant_width_
                                                    anchors.left: participant_tag.right
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    height: participant_tag.height
                                                    width: max_participant_width_ - participant_tag.implicitWidth
                                                    color: participant_background.color
                                                }
                                            }

                                            ListView
                                            {
                                                id: endpointsList
                                                model: modelData["endpoints"]
                                                anchors.top: participant_tag.bottom; anchors.topMargin: elementsSpacing
                                                anchors.left: parent.left; anchors.leftMargin: elementsSpacing
                                                anchors.right: parent.right; anchors.rightMargin: elementsSpacing
                                                interactive: false
                                                spacing: elementsSpacing

                                                Connections
                                                {
                                                    target: domainGraphLayout

                                                    function onTopics_updated()
                                                    {
                                                        endpointsList.onCountChanged()
                                                    }
                                                }

                                                onCountChanged:
                                                {
                                                    var listViewHeight = 0

                                                    // iterate over each element in the list item
                                                    for (var i = 0; i < endpointsList.visibleChildren.length; i++) {
                                                        listViewHeight += endpointsList.visibleChildren[i].height + elementsSpacing
                                                        var min_width = endpointsList.visibleChildren[i].width
                                                        for (var j = 0; j < endpointsList.visibleChildren[i].visibleChildren.length; j++)
                                                        {
                                                            min_width = Math.max(min_width, endpointsList.visibleChildren[i].visibleChildren[j].width)
                                                        }
                                                        max_endpoint_width_ = Math.max(max_endpoint_width_, min_width)
                                                        endpointsList.visibleChildren[i].width = max_endpoint_width_
                                                        endpointsList.visibleChildren[i].record_connection = true
                                                    }

                                                    endpointsList.height = listViewHeight + elementsSpacing
                                                    endpointsList.width = max_endpoint_width_
                                                    endpoints_updated()
                                                }

                                                delegate: Item
                                                {
                                                    id: endpointComponent
                                                    property bool record_connection: false
                                                    width: max_endpoint_width_ == 0 ? endpoint_tag.implicitWidth : max_endpoint_width_
                                                    height: 40

                                                    onRecord_connectionChanged:
                                                    {
                                                        if (record_connection == true)
                                                        {
                                                            var src_x = endpointComponent.x + endpointComponent.width
                                                            var src_y = endpointComponent.y + (endpointComponent.height / 2)
                                                            var left_to_right = modelData["kind"] == "datareader"
                                                            endpoint_topic_connections.modelData["id"] = {
                                                                "id": modelData["id"], "left_to_right":left_to_right,
                                                                "x":src_x, "y":src_x, "destination_id":modelData["topic"]}
                                                            record_connection = false
                                                            console.log(JSON.stringify(endpoint_topic_connections, null, 2))
                                                        }
                                                    }

                                                    Connections
                                                    {
                                                        target: domainGraphLayout

                                                        function onHosts_updated()
                                                        {
                                                            var i = 0;
                                                            for (i = 0; i < endpoint_topic_connections.length; i++)
                                                            {
                                                                if (connection[i]["id"] == modelData["id"])
                                                                {
                                                                    var topic_id = endpoint_topic_connections[i]["destination_id"]
                                                                    var destination_x = topic_locations[topic_id]["x"]
                                                                    var conn_bar_comp = Qt.createComponent("GraphConnection.qml")
                                                                    var connection_bar = conn_bar_comp.createObject(null,
                                                                        {"x": endpoint_topic_connections[i]["x"]
                                                                        ,"left_to_right": endpoint_topic_connections[i]["left_to_right"]
                                                                        ,"y": endpoint_topic_connections[i]["y"] - (connection_thickness / 2)
                                                                        ,"width":200//destination_x - endpoint_topic_connections[i]["x"]
                                                                        ,"height":connection_thickness})
                                                                }
                                                            }
                                                        }
                                                    }

                                                    Rectangle
                                                    {
                                                        id: endpoint_background
                                                        width: parent.width
                                                        height: 40
                                                        color: modelData["kind"] == "datareader" ? readerColor : writerColor
                                                    }
                                                    Rectangle
                                                    {
                                                        id: endpoint_tag
                                                        anchors.top: parent.top
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        implicitWidth: max_endpoint_width_ == 0 ? endpointRowLayout.implicitWidth : max_endpoint_width_
                                                        height: 40
                                                        color: endpoint_background.color

                                                        RowLayout {
                                                            id: endpointRowLayout
                                                            anchors.centerIn: parent

                                                            IconSVG {
                                                                visible: modelData["status"] != "ok"
                                                                name: "issues"
                                                                size: modelData["status"] != "ok"? iconSize : 0
                                                                Layout.leftMargin: modelData["status"] != "ok" ? firstIndentation : 0
                                                            }
                                                            IconSVG {
                                                                name: modelData["kind"]
                                                                size: iconSize
                                                            }
                                                            Label {
                                                                text: modelData["alias"]
                                                                Layout.rightMargin: spacingIconLabel + firstIndentation
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


    function load_model()
    {
        // clear internal models
        topic_locations = {}
        endpoint_topic_connections = {}

        // this is implemented in this function to avoid this huge code pasting at the beginning of the file
        model = {
            "kind": "domain_view",
            "domain": 0,
            "topics":
            [
                {
                    "id": 25,
                    "kind": "topic",
                    "alias": "topic_alias_25"
                },
                {
                    "id": 26,
                    "kind": "topic",
                    "alias": "topic_alias_26"
                },
            ],
            "hosts":
            [
                {
                    "id": 1,
                    "kind": "host",
                    "alias": "host_alias_1",
                    "status": "error",
                    "users":
                    [
                        {
                            "id": 3,
                            "kind": "user",
                            "alias": "user_alias_3",
                            "status": "error",
                            "processes":
                            [
                                {
                                    "id": 6,
                                    "kind": "process",
                                    "alias": "process_alias_6",
                                    "pid": "9506",
                                    "status": "error",
                                    "participants":
                                    [
                                        {
                                            "id": 10,
                                            "kind": "participant",
                                            "alias": "participant_alias_10",
                                            "status": "error",
                                            "endpoints":
                                            [
                                                {
                                                    "id": 15,
                                                    "kind": "datareader",
                                                    "alias": "datareader_alias_15",
                                                    "status": "warning",
                                                    "topic": 25
                                                },
                                                {
                                                    "id": 16,
                                                    "kind": "datawriter",
                                                    "alias": "datawriter_alias_16",
                                                    "status": "error",
                                                    "topic": 26
                                                }
                                            ]
                                        },
                                        {
                                            "id": 11,
                                            "kind": "participant",
                                            "alias": "participant_alias_11",
                                            "status": "ok",
                                            "endpoints":
                                            [
                                                {
                                                    "id": 17,
                                                    "kind": "datareader",
                                                    "alias": "datareader_alias_17",
                                                    "status": "ok",
                                                    "topic": 25
                                                },
                                                {
                                                    "id": 18,
                                                    "kind": "datawriter",
                                                    "alias": "datawriter_alias_18",
                                                    "status": "ok",
                                                    "topic": 26
                                                }/*,
                                                {
                                                    "id": 19,
                                                    "kind": "datareader",
                                                    "alias": "datareader_alias_19",
                                                    "status": "ok",
                                                    "topic": 26
                                                }*/
                                            ]
                                        }
                                    ]
                                }/*,
                                {
                                    "id": 12,
                                    "kind": "process",
                                    "alias": "process_alias_12",
                                    "pid": "9512",
                                    "status": "warning",
                                    "participants":
                                    [
                                        {
                                            "id": 13,
                                            "kind": "participant",
                                            "alias": "participant_alias_13",
                                            "status": "warning",
                                            "endpoints":
                                            [
                                                {
                                                    "id": 14,
                                                    "kind": "datareader",
                                                    "alias": "datareader_alias_14",
                                                    "status": "warning",
                                                    "topic": 25
                                                }
                                            ]
                                        }
                                    ]
                                }*/
                            ]
                        }
                    ]
                }
            ]
        }
    }

    function create_connections()
    {
        var i = 0;
        console.log(endpoint_topic_connections.count)
        console.log(endpoint_topic_connections.size)
        console.log(endpoint_topic_connections.length)
        console.log("-----")
        for (i = 0; i < endpoint_topic_connections.length; i++)
        {
            var connection_bar = Qt.createComponent("GraphConnection.qml", mainView)
            connection_bar.left_to_right = endpoint_topic_connections[i]["left_to_right"]
            connection_bar.x = endpoint_topic_connections[i]["x"]
            connection_bar.y = endpoint_topic_connections[i]["y"] - (connection_bar.thickness / 2)
            connection_bar.height = connection_bar.thickness
            var topic_id = endpoint_topic_connections[i]["destination_id"]
            var destination_x = topic_locations[topic_id]["x"]
            connection_bar.width = destination_x - endpoint_topic_connections[i]["x"]
            console.log(connection_bar.left_to_right)
            console.log(connection_bar.x)
            console.log(connection_bar.y)
            console.log(connection_bar.width)
            console.log(connection_bar.height)
            console.log("----")
        }

        /*connection.x = src_x
        connection.y = src_y - (connection.thickness / 2)
        console.log(topic_id)
        console.log("-")
        console.log(JSON.stringify(topic_locations[topic_id], null, 2))
        console.log("-")
        console.log(topic_locations[topic_id])
        console.log("-")
        console.log(JSON.stringify(topic_locations[topic_id]["x"], null, 2))
        console.log("-")
        console.log(topic_locations[topic_id]["x"])
        console.log("-------------")
        connection.width = topic_locations[topic_id]["x"] - src_x*/
    }
}
