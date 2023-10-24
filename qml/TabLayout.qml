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

Item {
    id: tabLayout

    // Public properties
    property bool fullScreen: false                                         // ChartsLayout inherited var

    // Private properties
    property int current_: 0                                                // current tab displayed
    property int last_index_: 1                                             // force unique idx on QML components
    property var tab_model_: [{"idx":0, "title":"New Tab", "stack_id": 0}]  // tab model for tab bad and tab management
    property bool disable_chart_selection_: false                           // flag to disable multiple chart view tabs

    // private signals
    signal open_domain_view_(int stack_id, int entity_id, int domain_id)
    signal initialize_domain_view_(int stack_id, int entity_id, int domain_id)

    // Read only design properties
    readonly property int max_tabs_: 15
    readonly property int max_tab_size_: 180
    readonly property int min_tab_size_: 120
    readonly property int tabs_height_: 36
    readonly property int tabs_margins_: 15
    readonly property int tab_icons_size_: 16
    readonly property int add_tab_width_: 50
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
                initialItem: view_selector

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
                                width: 400; height: 400
                                anchors.verticalCenter: parent.verticalCenter
                                enabled: !disable_chart_selection_
                                text: "Chart View"
                                onClicked: {
                                    if (!disable_chart_selection_)
                                    {
                                        tabLayout.tab_model_[current_]["title"] = "Chart View"
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
                                width: 400; height: 400
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Domain View"
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
                            tabLayout.tab_model_[current_]["title"] = new_name

                            // update model to set the visual change
                            tab_list.model = tabLayout.tab_model_

                            // update left panel information
                            for (var i=0; i<stack_layout.count; i++)
                            {
                                if (stack_layout.children[i].stack_id == tabLayout.tab_model_[current_]["stack_id"] &&
                                    stack_layout.children[i].currentItem.entity_id > 0)
                                {
                                    controller.domain_click(stack_layout.children[i].currentItem.entity_id)
                                    break;
                                }
                            }
                        }

                        Connections {
                            target: tabLayout

                            function onInitialize_domain_view_(stack_id, entity_id, domain_id) {
                                if (domainGraphLayout.component_id == stack_id)
                                {
                                    domainGraphLayout.entity_id = entity_id
                                    domainGraphLayout.domain_id = domain_id
                                    domainGraphLayout.load_model()
                                }
                            }
                        }

                    }
                }

                Connections {
                    target: tabLayout

                    function onOpen_domain_view_(stack_id, entity_id, domain_id) {
                        if (stack.stack_id == stack_id)
                        {
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
            Text {
                horizontalAlignment: Qt.AlignLeft; verticalAlignment: Qt.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: tabs_margins_
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
            // tab selection action
            MouseArea {
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
        // add new tab action
        MouseArea {
            anchors.fill: parent
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

        width: 300

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
                            ? ("Please choose a Domain ID")
                            : ("DDS Domain " + currentText)
            model: entityModelFirst

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

    function create_new_tab()
    {
        var idx = tabLayout.tab_model_.length
        tabLayout.tab_model_[idx] = {"idx" : idx, "title": "New Tab", "stack_id":last_index_}
        var new_stack = stack_component.createObject(null, {"stack_id": tabLayout.tab_model_[idx]["stack_id"]})
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
                    if (stack_layout.children[i].stack_id == tabLayout.tab_model_[idx]["stack_id"])
                    {
                        controller.domain_click(stack_layout.children[i].currentItem.entity_id)
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
}
