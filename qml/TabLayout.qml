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
import Clipboard 1.0

Item {
    id: tabLayout

    // Public properties
    property bool fullScreen: false                                         // ChartsLayout inherited var

    // Public signals
    signal openEntitiesMenu(string domainEntityId, string entityId, string currentAlias, string entityKind, int caller)
    signal openTopicMenu(string domainEntityId, string domainId, string entityId, string currentAlias, string entityKind, int caller)

    // Private properties
    property int current_: 0                                                // current tab displayed
    property int last_index_: 1                                             // force unique idx on QML components
    property var tab_model_: [{"idx":0, "title":"New Tab", "icon":"", "stack_id": 0}]  // tab model for tab bad and tab management
    property bool disable_chart_selection_: false                           // flag to disable multiple chart view tabs
    readonly property var allowed_stack_components_:                        // list of allowed component names to be
            ["view_selector", "chartsLayout", "domainGraphLayout_component", "idlView_component"] //  loaded in the tabs stack view

    // private signals
    signal open_domain_view_(int stack_id, int entity_id, int domain_id)
    signal initialize_domain_view_(int stack_id, int entity_id, int domain_id)
    signal filter_domain_view_by_topic_(int stack_id, int domain_entity_id, string topic_id)
    signal display_idl_content_(int stack_id, string content)

    // Read only design properties
    readonly property int max_tabs_: 15
    readonly property int max_tab_size_: 180
    readonly property int min_tab_size_: 120
    readonly property int tabs_height_: 36
    readonly property int tabs_margins_: 15
    readonly property int tab_icons_size_: 16
    readonly property int tab_icons_margins_: 8
    readonly property int add_tab_width_: 50
    readonly property int timer_ms_interval_: 500
    readonly property int dialog_width_: 300
    readonly property int dialog_height_: 152
    readonly property int idl_text_margin_: 30
    readonly property int hover_text_offset_: 50
    readonly property int elements_spacing_: 5
    readonly property int scrollbar_min_size_: 8
    readonly property int scrollbar_max_size_: 12
    readonly property int ros2_info_box_padding_: 10
    readonly property int ros2_info_box_border_width_: 2
    readonly property int ros2_info_box_radius_: 10
    readonly property real scroll_speed_: 0.05
    readonly property string selected_tab_color_: "#ffffff"
    readonly property string selected_shadow_tab_color_: "#c0c0c0"
    readonly property string not_selected_tab_color_: "#f0f0f0"
    readonly property string not_selected_shadow_tab_color_: "#d0d0d0"

    // initialize first element in the tab
    Component.onCompleted:{
        var new_stack = stack_component.createObject(null, {"stack_id": 0})
        stack_layout.children.push(new_stack)
        refresh_layout(current_)
    }

    ChartsLayout {
        visible: disable_chart_selection_
        id: chartsLayout
        anchors.fill: stack_layout
        onFullScreenChanged: {
            tabLayout.fullScreen = fullScreen
        }
    }

    ClipboardHandler {
        id: clipboardHandler
    }

    // stack layout (where idx referred to the tab, which would contain different views)
    StackLayout {
        id: stack_layout
        width: tabLayout.width
        anchors.top: tab_list.bottom; anchors.bottom: tabLayout.bottom

        Component {
            id: stack_component

            // view with the different views available in a tab
            StackView {
                id: stack
                property int stack_id: 0
                property string customInitialItem: "view_selector"
                initialItem: customInitialItem == "chartsLayout" ? chartsLayout :
                        customInitialItem == "domainGraphLayout_component" ? domainGraphLayout_component :
                        customInitialItem == "idlView_component" ? idlView_component : view_selector
                property string topic_IDL_ID: ""

                // override push transition to none
                pushEnter: Transition {}

                // menu that allows the selection of the view, and changes the stack if necessary
                Component {
                    id: view_selector
                    Rectangle {
                        Row {
                            anchors{
                                horizontalCenter: parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                            height: parent.height
                            width: childrenRect.width
                            spacing: 60
                            Button {
                                id: chart_button
                                width: 400; height: 400
                                background: Rectangle {
                                    color: disable_chart_selection_ ? Theme.lightGrey : Theme.whiteSmoke
                                    border.width: 3
                                    border.color: disable_chart_selection_ ? Theme.grey :
                                            chart_button.hovered ? Theme.eProsimaLightBlue : Theme.eProsimaDarkBlue
                                    radius: 40

                                    Image {
                                        anchors.centerIn: parent
                                        anchors.verticalCenterOffset: -50
                                        smooth: true
                                        source: "/resources/images/graphs.svg/"
                                        property int size: 25
                                        sourceSize.width: size * 16
                                        sourceSize.height: size * 9
                                    }

                                    Text {
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.bottom: parent.bottom; anchors.bottomMargin: 50
                                        width: parent.width
                                        text: "Chart View"
                                        horizontalAlignment: Text.AlignHCenter
                                        font.pointSize: 20
                                        color: disable_chart_selection_ ? Theme.grey :
                                                chart_button.hovered ? Theme.eProsimaLightBlue : Theme.eProsimaDarkBlue
                                    }
                                }
                                anchors.verticalCenter: parent.verticalCenter
                                enabled: !disable_chart_selection_
                                onClicked: {
                                    if (!disable_chart_selection_)
                                    {
                                        tabLayout.tab_model_[current_]["title"] = "Chart View"
                                        tabLayout.tab_model_[current_]["icon"] = "dynamicchart"
                                        if (stack.deep > 1)
                                        {
                                            stack.pop()
                                        }
                                        stack.push(chartsLayout)
                                        disable_chart_selection_ = true
                                        refresh_layout(current_)
                                    }
                                }
                            }
                            Button {
                                id: domain_view_button
                                width: 400; height: 400
                                background: Rectangle {
                                    color: Theme.whiteSmoke
                                    border.width: 3
                                    border.color: domain_view_button.hovered ? Theme.eProsimaLightBlue : Theme.eProsimaDarkBlue
                                    radius: 40

                                    Image {
                                        anchors.centerIn: parent
                                        anchors.verticalCenterOffset: -50
                                        smooth: true
                                        source: "/resources/images/domain_graph.svg/"
                                        property int size: 30
                                        sourceSize.width: size * 16
                                        sourceSize.height: size * 9
                                    }

                                    Text {
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.bottom: parent.bottom; anchors.bottomMargin: 50
                                        width: parent.width
                                        text: "Domain View"
                                        horizontalAlignment: Text.AlignHCenter
                                        font.pointSize: 20
                                        color: domain_view_button.hovered ? Theme.eProsimaLightBlue : Theme.eProsimaDarkBlue
                                    }
                                }
                                anchors.verticalCenter: parent.verticalCenter
                                onClicked: {
                                    if (mainApplicationView.monitors == 0)
                                    {
                                        dialogInitMonitor.open()
                                    }
                                    else if (mainApplicationView.monitors == 1)
                                    {
                                        controller.update_available_entity_ids("Domain", "getDataDialogSourceEntityId")
                                        open_domain_view_(
                                            tabLayout.tab_model_[current_]["stack_id"],
                                            entityModelFirst.get(0).id,
                                            entityModelFirst.get(0).name)
                                    }
                                    else
                                    {
                                        domain_id_dialog.open()
                                    }
                                }
                            }
                        }
                    }
                }

                Component {
                    id: domainGraphLayout_component

                    DomainGraphLayout
                    {
                        id: domainGraphLayout
                        component_id: stack.stack_id

                        onUpdate_tab_name: {
                            for (var i = 0; i<tabLayout.tab_model_.length; i++)
                            {
                                if (tabLayout.tab_model_[i]["stack_id"] == stack_id)
                                {
                                    tabLayout.tab_model_[i]["title"] = new_name
                                    tabLayout.tab_model_[i]["icon"] = new_icon

                                    // update model to set the visual change
                                    tab_list.model = tabLayout.tab_model_

                                    // update left panel information
                                    for (var j=0; j<stack_layout.count; j++)
                                    {
                                        if (stack_layout.children[j].stack_id == tabLayout.tab_model_[i]["stack_id"] &&
                                            stack_layout.children[j].currentItem.domain_entity_id > 0)
                                        {
                                            controller.domain_click(stack_layout.children[j].currentItem.domain_entity_id)
                                            break;
                                        }
                                    }
                                    break       // exit loop
                                }
                            }
                        }

                        onOpenEntitiesMenu: {
                            tabLayout.openEntitiesMenu(domainEntityId, entityId, currentAlias, entityKind, caller)
                        }
                        onOpenTopicMenu: {
                            tabLayout.openTopicMenu(domainEntityId, domainId, entityId, currentAlias, entityKind, caller)
                        }

                        onOpenLoadingGraphDialog: {
                            loading_graph_dialog.open()
                        }

                        onInitialized: {
                            loading_graph_dialog.soft_close()
                        }

                        Connections {
                            target: tabLayout

                            function onInitialize_domain_view_(stack_id, entity_id, domain_id) {
                                if (domainGraphLayout.component_id == stack_id)
                                {
                                    domainGraphLayout.domain_entity_id = entity_id
                                    domainGraphLayout.domain_id = domain_id
                                    domainGraphLayout.load_model()
                                }
                            }

                            function onFilter_domain_view_by_topic_(stack_id, domain_entity_id, topic_id) {
                                if (domainGraphLayout.component_id == stack_id &&
                                    domainGraphLayout.domain_entity_id == domain_entity_id)
                                {
                                    domainGraphLayout.filter_model_by_topic(topic_id)
                                }
                            }
                        }
                    }
                }

                Component {
                    id: idlView_component
                    Flickable
                    {
                        id: idlView
                        clip: true
                        boundsBehavior: Flickable.StopAtBounds
                        interactive: false
                        anchors.fill: parent
                        width: parent.width
                        height: parent.height
                        contentWidth: parent.width
                        contentHeight: idl_text.height + 2 * tabLayout.idl_text_margin_
                        property bool is_ros2: false
                        ScrollBar.vertical: ScrollBar {
                            id: vertical_bar
                            policy: ScrollBar.AlwaysOn
                            visible: idlView.contentHeight > idlView.height
                            stepSize: tabLayout.scroll_speed_
                            anchors.top: parent.top;        anchors.topMargin: 0
                            anchors.right: parent.right;
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

                        Rectangle {
                            id: ros2InfoBox
                            property int padding: ros2_info_box_padding_
                            property int defaultWidth: ros2InfoText.implicitWidth + padding * 2
                            property int minWidth: border.width * 2
                            property int collapsePoint: parent.width * 2 / 3
                            anchors.top: parent.top
                            anchors.topMargin: tabLayout.idl_text_margin_
                            anchors.right: parent.right
                            anchors.rightMargin: tabLayout.idl_text_margin_
                            width: {
                                // Keep full width until left edge would cross collapse point
                                var leftEdge = parent.width - anchors.rightMargin - defaultWidth
                                if (leftEdge < collapsePoint) {
                                // Start collapsing: shrink width, but don't go below minWidth
                                return Math.max(parent.width - anchors.rightMargin - collapsePoint, minWidth)
                                } else {
                                    return defaultWidth
                                }
                            }
                            height: ros2InfoText.implicitHeight + padding * 2
                            color: "transparent"
                            border.color: "black"
                            border.width: ros2_info_box_border_width_
                            radius: ros2_info_box_radius_
                            visible: is_ros2 && monitorMenuBar.ros2DemanglingActive
                            z: idl_text.z + 1
                            Text {
                                id: ros2InfoText
                                anchors.centerIn: parent
                                text: "ROS 2 Demangling applied"
                                color: "black"
                                elide: Text.ElideRight
                                clip: true
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            MouseArea {
                                id: ros2InfoBoxMouseArea
                                //acceptedButtons: Qt.NoButton
                                hoverEnabled: true
                                anchors.fill: parent
                            }
                            ToolTip {
                                //parent: ros2InfoBox.Window
                                text: "Undo ROS 2 demangling in View->Revert ROS 2 Demangling"
                                visible: ros2InfoBoxMouseArea.containsMouse && ros2InfoBox.visible
                            }
                        }

                        MouseArea {
                            id: textMouseArea
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            hoverEnabled: true
                            onWheel: {
                                if(wheel.angleDelta.y > 0){
                                  vertical_bar.decrease()
                                }else{
                                  vertical_bar.increase()
                                }
                            }
                            onPressed: {
                                if(mouse.button & Qt.RightButton) {
                                    var start = idl_text.selectionStart
                                    var end = idl_text.selectionEnd
                                    idl_text.focus = true
                                    contextMenu.popup()
                                    idl_text.select(start, end)
                                }
                            }
                        }

                        Menu {
                            id: contextMenu
                            MenuItem {
                                text: "Copy"
                                onTriggered: {
                                    if (clipboardHandler) {
                                        let textToCopy = idl_text.selectedText.length > 0 ? idl_text.selectedText : idl_text.text
                                        clipboardHandler.setClipboardText(textToCopy)
                                    }else{
                                        console.log("Clipboard not available")
                                    }
                                }
                            }
                            MenuItem {
                                text: "Select All"
                                onTriggered: {
                                    idl_text.selectAll()
                                }
                            }
                            MenuItem {
                                text: "Copy IDL title"
                                onTriggered: {
                                    if (clipboardHandler) {
                                        let textToCopy = tabLayout.tab_model_[current_]["title"]
                                        clipboardHandler.setClipboardText(textToCopy)
                                    }else{
                                        console.log("Clipboard not available")
                                    }
                                }
                            }
                        }

                        TextEdit
                        {
                            id: idl_text
                            text: ""
                            selectionColor: Theme.eProsimaLightBlue
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.leftMargin: tabLayout.idl_text_margin_
                            anchors.rightMargin: tabLayout.idl_text_margin_
                            anchors.topMargin: tabLayout.idl_text_margin_
                            width: parent.width - 2 * tabLayout.idl_text_margin_
                            wrapMode: TextEdit.WrapAnywhere

                            // Enable text selection in the view
                            readOnly: true
                            selectByMouse: true
                            selectByKeyboard: true
                            Connections
                            {
                                target: tabLayout

                                function onDisplay_idl_content_(stack_id, content)
                                {
                                    if (stack.stack_id == stack_id)
                                    {
                                        idl_text.text = content
                                    }
                                }
                            }
                        }
                        Connections
                        {
                            target: monitorMenuBar

                            function onRos2DemanglingChange(newValue){
                                if (is_ros2)
                                {
                                    idl_text.text = newValue ? controller.get_type_idl(topic_IDL_ID) : controller.get_ros2_type_idl(topic_IDL_ID)
                                    var i
                                    for (i=0; i<tabLayout.tab_model_.length; i++)
                                    {
                                        if (tabLayout.tab_model_[i]["stack_id"] == stack.stack_id)
                                        {
                                            tabLayout.tab_model_[i]["title"] = newValue ? controller.get_ros2_type_name(topic_IDL_ID) : controller.get_data_type_name(topic_IDL_ID)
                                            refresh_layout(i)
                                            break
                                        }
                                    }
                                }
                            }
                        }
                        Component.onCompleted: {
                            is_ros2 = controller.get_ros2_type_name(topic_IDL_ID) != controller.get_data_type_name(topic_IDL_ID)
                        }
                    }
                }

                Connections {
                    target: tabLayout

                    function onOpen_domain_view_(stack_id, entity_id, domain_id, topic_id) {
                        if (stack.stack_id == stack_id)
                        {
                            loading_graph_dialog.open()
                            if (stack.deep > 1)
                            {
                                stack.pop()
                            }

                            stack.push(domainGraphLayout_component)
                            refresh_layout(current_)
                            initialize_domain_view_(stack_id, entity_id, domain_id)
                        }
                    }
                }
            }
        }
    }

    ListView {
        id: tab_list
        anchors.top: parent.top
        anchors.left: parent.left
        width: contentWidth
        height: tabs_height_
        orientation: ListView.Horizontal
        model: tabLayout.tab_model_
        interactive: false

        // tab design
        delegate: Rectangle {
            id: delegated_rect
            height: tabs_height_
            width: tabLayout.tab_model_.length == max_tabs_
                ? tabLayout.width / tabLayout.tab_model_.length < tab_icons_size_+ (4*tabs_margins_)
                    ? current_ == modelData["idx"] ? tab_icons_size_+ (2 * tabs_margins_)
                    : tabLayout.width / tabLayout.tab_model_.length : tabLayout.width / tabLayout.tab_model_.length
                : (tabLayout.width - add_new_tab_button.width) / tabLayout.tab_model_.length > max_tab_size_ ? max_tab_size_
                    : (tabLayout.width - add_new_tab_button.width) / tabLayout.tab_model_.length < tab_icons_size_+ (4*tabs_margins_)
                        ? current_ == modelData["idx"] ? tab_icons_size_+ (2 * tabs_margins_)
                        : (tabLayout.width - add_new_tab_button.width) / tabLayout.tab_model_.length
                    : (tabLayout.width - add_new_tab_button.width) / tabLayout.tab_model_.length
            color: current_ == modelData["idx"] ? selected_tab_color_ : not_selected_tab_color_
            property string shadow_color: current_ == modelData["idx"] ? selected_shadow_tab_color_ : not_selected_shadow_tab_color_
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: modelData["idx"] == 0 || current_ == modelData["idx"] ? delegated_rect.color : shadow_color}
                GradientStop { position: 0.04; color: delegated_rect.color }
                GradientStop { position: 0.96; color: delegated_rect.color }
                GradientStop { position: 1.0; color: current_ == modelData["idx"] + 1 ? shadow_color : delegated_rect.color}
            }
            // tab icon
            IconSVG {
                id: tab_icon
                visible: modelData["title"] != "New Tab" && modelData["icon"] != ""
                anchors.left: parent.left
                anchors.leftMargin: tab_icons_margins_
                anchors.verticalCenter: parent.verticalCenter
                name: modelData["icon"]
                size: tab_icons_size_
            }
            Text {
                horizontalAlignment: Qt.AlignLeft; verticalAlignment: Qt.AlignVCenter
                anchors.left: tab_icon.right
                anchors.leftMargin: tab_icons_margins_
                anchors.right: close_icon.visible ? close_icon.left : parent.right
                anchors.rightMargin: tabs_margins_
                anchors.verticalCenter: parent.verticalCenter
                text:  modelData["title"]
                elide: Text.ElideRight
            }
            // close tab icon
            IconSVG {
                id: close_icon
                visible: modelData["idx"] == current_ ? true : parent.width > min_tab_size_
                anchors.right: parent.right
                anchors.rightMargin: tabs_margins_
                anchors.verticalCenter: parent.verticalCenter
                name: "cross"
                size: tab_icons_size_
            }
            Label {
                id: hover_label
                visible: false
                anchors.top: delegated_rect.bottom
                anchors.topMargin: tabLayout.hover_text_offset_
                anchors.horizontalCenter: delegated_rect.horizontalCenter
                ToolTip.text: modelData["title"]
                ToolTip.visible: mouse_area.containsMouse
            }

            // tab selection action
            MouseArea {
                id: mouse_area
                hoverEnabled: true
                anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left;
                anchors.right: close_icon.left; anchors.rightMargin: - tabs_margins_
                onClicked: {
                    refresh_layout(modelData["idx"])
                }
            }
            // close tab action
            MouseArea {
                anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.right: parent.right
                anchors.left: close_icon.left; anchors.leftMargin: - tabs_margins_
                onClicked: {
                    // act as close is close icon shown (same expression as in close_icon visible attribute)
                    if (modelData["idx"] == current_ || parent.width > min_tab_size_)
                    {
                        remove_idx(modelData["idx"])
                    }
                    // if not, act as open tab action
                    else
                    {
                        refresh_layout(modelData["idx"])
                    }
                }
            }
        }
    }

    // Add new tab button
    Rectangle {
        id: add_new_tab_button
        visible: tabLayout.tab_model_.length < max_tabs_
        anchors.right: remain_width_rect.left
        anchors.verticalCenter: tab_list.verticalCenter
        height: tabs_height_
        width: tabLayout.tab_model_.length == max_tabs_ ? 0 : add_tab_width_
        color: not_selected_tab_color_
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color:  not_selected_shadow_tab_color_}
            GradientStop { position: 0.08; color: add_new_tab_button.color }
            GradientStop { position: 1.0; color: add_new_tab_button.color }
        }
        // add new tab icon
        IconSVG {
            visible: tabLayout.tab_model_.length < max_tabs_
            anchors.centerIn: parent
            name: "plus"
            size: tab_icons_size_
        }
        Label {
            visible: false
            anchors.top: add_new_tab_button.bottom
            anchors.topMargin: tabLayout.hover_text_offset_
            anchors.horizontalCenter: add_new_tab_button.horizontalCenter
            ToolTip.text: "Add new tab"
            ToolTip.visible: add_tab_mouse_area.containsMouse
        }
        // add new tab action
        MouseArea {
            id: add_tab_mouse_area
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if (tabLayout.tab_model_.length < max_tabs_)
                    tabLayout.create_new_tab()
            }
        }
    }

    // remain space in tab bar handled by this component
    Rectangle {
        id: remain_width_rect
        width: tabLayout.width - add_new_tab_button.width - tab_list.width; height: tabs_height_
        anchors.right: tabLayout.right
        anchors.verticalCenter: tab_list.verticalCenter
        color: not_selected_tab_color_

        Rectangle {
            width: parent.width >= 80 ? 80 : parent.width; height: parent.height
            color: parent.color
            gradient: Gradient {
            orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color:  not_selected_shadow_tab_color_}
                GradientStop { position: 0.08; color: not_selected_tab_color_ }
                GradientStop { position: 1.0; color: not_selected_tab_color_ }
            }
        }
    }

    Dialog {
        id: domain_id_dialog

        property bool enable_ok_button: false       // disable OK button until user selects domain id

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        width: dialog_width_

        modal: true
        title: "Select DDS Domain"

        footer: DialogButtonBox {
            id: buttons
            standardButtons: Dialog.Ok | Dialog.Cancel
        }

        onAboutToShow: {
            custom_combobox.currentIndex = -1
            controller.update_available_entity_ids("Domain", "getDataDialogSourceEntityId")
            custom_combobox.recalculateWidth()
            enable_ok_button = false
            buttons.standardButton(Dialog.Ok).enabled = false
        }

        onEnable_ok_buttonChanged: {
            buttons.standardButton(Dialog.Ok).enabled = domain_id_dialog.enable_ok_button
        }

        AdaptiveComboBox {
            id: custom_combobox
            textRole: "name"
            valueRole: "id"
            displayText: currentIndex === -1
                            ? ("Please choose a Domain ID or Participant Profile")
                            : currentText
            model: entityModelFirst

            width: parent.width > implicitWidth ? parent.width : implicitWidth

            Component.onCompleted:
            {
                currentIndex = -1
                custom_combobox.recalculateWidth()
            }

            onActivated: {
                domain_id_dialog.enable_ok_button = true
                custom_combobox.recalculateWidth()
            }
        }

        onAccepted:
        {
            open_domain_view_(
                tabLayout.tab_model_[current_]["stack_id"],
                entityModelFirst.get(custom_combobox.currentIndex).id,
                entityModelFirst.get(custom_combobox.currentIndex).name)
        }
    }

    Dialog {
        id: loading_graph_dialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        width: dialog_width_
        height: dialog_height_

        modal: true

        background: Rectangle {
            color: "white"
        }


        AnimatedImage {
            source: "/resources/images/loading_graph.gif"
            anchors.centerIn: parent
            width: dialog_width_ * 3/4
            height: dialog_height_ * 3/4
        }

        onAboutToShow:
        {
            timer.start()
        }

        function soft_close()
        {
            if (timer.running)
            {
                timer.should_close = true
            }
            else
            {
                loading_graph_dialog.close()
            }
        }

        Timer
        {
            id: timer
            property bool should_close: false
            interval: timer_ms_interval_; running: false
            onTriggered:
            {
                if (timer.should_close)
                {
                    loading_graph_dialog.close()
                    timer.should_close = false
                }
            }
        }
    }

    function create_new_tab()
    {
        create_new_custom_tab_("", "")
    }

    function create_new_custom_tab_(component_identifier, topic_IDL_ID)
    {
        var initial_component = component_identifier
        if (!allowed_stack_components_.includes(component_identifier))
        {
            initial_component = "view_selector";
        }
        var idx = tabLayout.tab_model_.length
        tabLayout.tab_model_[idx] = {"idx" : idx, "title": "New Tab", "icon":"", "stack_id":last_index_}
        var new_stack = stack_component.createObject(null, {
                "stack_id": tabLayout.tab_model_[idx]["stack_id"], "customInitialItem": initial_component , "topic_IDL_ID": topic_IDL_ID})
        last_index_++
        stack_layout.children.push(new_stack)
        refresh_layout(idx)
        stack_layout.currentIndex = tabLayout.tab_model_[idx]["stack_id"]
    }

    // the given idx update current tab displayed (if != current)
    function refresh_layout(idx)
    {
        var i
        // move to idx tab if necessary
        if (idx != current_)
        {
            current_ = idx

            // move to the idx tab in the stack
            stack_layout.currentIndex = tabLayout.tab_model_[idx]["stack_id"]

            // check if domain info has changed
            if (tabLayout.tab_model_[idx]["title"].includes("Domain"))
            {
                for (var i=0; i<stack_layout.count; i++)
                {
                    if (stack_layout.children[i].stack_id == tabLayout.tab_model_[idx]["stack_id"] &&
                        stack_layout.children[i].currentItem.domain_entity_id > 0)
                    {
                        controller.domain_click(stack_layout.children[i].currentItem.domain_entity_id)
                        break;
                    }
                }
            }
        }
        // update idx model
        tab_list.model = tabLayout.tab_model_
    }

    // remove tab and all contained components
    function remove_idx(idx)
    {
        var should_add_new_tab = false
        // add new tab if closing the last opened tab
        if (tabLayout.tab_model_.length <= 1)
        {
            should_add_new_tab = true
        }

        var i, idx_prev
        var swap = false
        for (i=0, idx_prev=-1; i<tabLayout.tab_model_.length; i++, idx_prev++)
        {
            // if tab removed, reorder remain tabs
            if (swap)
            {
                tabLayout.tab_model_[idx_prev]["title"] = tabLayout.tab_model_[i]["title"]
                tabLayout.tab_model_[idx_prev]["icon"] = tabLayout.tab_model_[i]["icon"]
                tabLayout.tab_model_[idx_prev]["stack_id"] = tabLayout.tab_model_[i]["stack_id"]
            }
            // reorder model idx usage, and delete idx tab components (stack layout content)
            if (idx == i){
                swap = true
                var j
                for (j=0; j<stack_layout.count; j++)
                {
                    if (stack_layout.children[j].id == tabLayout.tab_model_[idx]["stack_id"])
                    {
                        stack_layout.children[j].destroy()
                    }
                }

                // check if removed tab was declared as chart view to enable new chart view tab
                if (tabLayout.tab_model_[idx]["title"] == "Chart View")
                {
                    disable_chart_selection_ = false
                }
            }
        }
        // if removed, remove tab from model (repeater tab bar)
        if (swap)
        {
            tabLayout.tab_model_.pop(idx_prev)
        }

        // if last tab closed
        if (should_add_new_tab)
        {
            create_new_tab()
        }
        // reset the focus to the new "current" tab
        else
        {
            var new_current = current_
            if (idx == current_)
            {
                if (idx -1 >= 1)
                {
                    new_current = idx -1
                }
                else
                {
                    new_current = 0
                }
                // move to the idx tab in the stack
                stack_layout.currentIndex = tabLayout.tab_model_[new_current]["stack_id"]
            }
            else
            {
                if (current_ == tabLayout.tab_model_.length)
                {
                    new_current = current_ -1
                }
            }
            // perform changes in the view
            refresh_layout(new_current)
        }
    }

    // Inherited ChartsLayout functions
    function chartsLayout_boxesPerRow(new_boxesPerRow_value)
    {
        chartsLayout.boxesPerRow = new_boxesPerRow_value
    }

    function chartsLayout_exitFullScreen()
    {
        chartsLayout.exitFullScreen()
    }

    function chartsLayout_createHistoricChart(dataKind){
        chartsLayout.createHistoricChart(dataKind)
    }

    function chartsLayout_createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints){
        chartsLayout.createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints)
    }

    function chartsLayout_createScheduleClear(entities, data, updateData, updateClear){
        chartsLayout.createScheduleClear(entities, data, updateData, updateClear)
    }

    function chartsLayout_saveAllCSV() {
        chartsLayout.saveAllCSV()
    }

    function open_topic_view(domainEntityId, domainId, entityId) {
        create_new_custom_tab_("domainGraphLayout_component", "")
        open_domain_view_(tabLayout.tab_model_[current_]["stack_id"], domainEntityId, domainId)
        filter_domain_view_by_topic_(tabLayout.tab_model_[current_]["stack_id"], domainEntityId, entityId)
    }

    function open_idl_view(entityId) {
        create_new_custom_tab_("idlView_component", entityId)
        tabLayout.tab_model_[current_]["title"] = monitorMenuBar.ros2DemanglingActive ? controller.get_ros2_type_name(entityId) : controller.get_data_type_name(entityId)
        tabLayout.tab_model_[current_]["icon"] = "idl"
        var content = monitorMenuBar.ros2DemanglingActive ? controller.get_type_idl(entityId) : controller.get_ros2_type_idl(entityId)
        display_idl_content_(tabLayout.tab_model_[current_]["stack_id"], content)
        refresh_layout(current_)
    }

    function refresh_domain_graph_view(domainEntityId, entityId) {
        for (var i=0; i<stack_layout.count; i++)
        {
            if (stack_layout.children[i].currentItem.domain_entity_id != undefined)
            {
                if (stack_layout.children[i].currentItem.contains_entity(domainEntityId, entityId))
                {
                    stack_layout.children[i].currentItem.load_model()
                }
            }
        }
    }
}
