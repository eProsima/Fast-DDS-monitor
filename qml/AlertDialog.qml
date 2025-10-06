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

import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Theme 1.0

Dialog {
    id: alertDialog

    readonly property int layout_vertical_spacing_: 10 // vertical spacing between the components in a row
    readonly property int layout_horizontal_spacing_: 15 // horizontal spacing between rows
    readonly property int item_height_: 40 // Height of header item and each item of
                                           // advanced options submenu (title + options)
    readonly property int dialog_width_: 300 // Width of the dialog

    property var availableAlertKinds: []
    property bool activeOk: true
    property string currentKind: ""
    property string currentAlertName: ""
    property string currentHost: ""
    property string currentUser: ""
    property string currentTopic: ""
    property int currentThreshold: 5
    property int currentTimeBetweenAlerts: 5000
    property string contactInfo: "sample@email.com"

    modal: false
    title: "Create new alert"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    signal createAlert(string alert_name, string host_name, string user_name, string topic_name,
                       string alert_type, int t_between_triggers, int threshold, string contact_info)

    Component.onCompleted: {
        availableAlertKinds = controller.get_alert_kinds()
        standardButton(Dialog.Ok).text = qsTrId("Add")
        standardButton(Dialog.Cancel).text = qsTrId("Close")
    }

    onAccepted: {
        if (!checkInputs())
            return

        currentKind = alertKindComboBox.currentText
        currentAlertName = alertNameTextField.text
        currentHost = manualHostCheckBox.checked ? manualHostText.text : hostComboBox.currentText
        currentUser = manualUserCheckBox.checked ? manualUserText.text : userComboBox.currentText
        currentTopic = manualTopicCheckBox.checked ? manualTopicText.text : topicComboBox.currentText
        currentTimeBetweenAlerts = alertTimeBetweenAlerts.value
        currentThreshold = parseInt(alertThreshold.value)
        createAlert(currentAlertName, currentHost, currentUser, currentTopic, currentKind, currentTimeBetweenAlerts, currentThreshold, contactInfo)
    }

    onAboutToShow: {
        alertKindComboBox.currentIndex = -1
        alertNameTextField.text = "<alert_name>"
        hostComboBox.currentIndex = -1
        topicComboBox.currentIndex = -1
        userComboBox.currentIndex = -1
        updateTopics()
        updateUsers()
        updateHosts()
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: alertKindLabel
            text: "Alert kind: "
            InfoToolTip {
                text: "Type of alert to be created."
            }
        }
        AdaptiveComboBox {
            id: alertKindComboBox
            displayText: currentIndex === -1
                         ? ("Please choose an alert kind...")
                         : currentText
            model: availableAlertKinds

            Component.onCompleted: currentIndex = -1
            onActivated: {
                activeOk = true
            }
        }

        Label {
            id: alertNameLabel
            text: "Alert name: "
            InfoToolTip {
                text: "Name of the alert.\n"+
                      "The alert name is autogerated\n" +
                      "using the values given in this\n" +
                      "dialog."
            }
        }

        TextField {
            id: alertNameTextField
            placeholderText: ""
            selectByMouse: true
            maximumLength: 100
            Layout.fillWidth: true

            onTextEdited: activeOk = true
        }

        Label {
            id: hostLabel
            text: "Host: "
            InfoToolTip {
                text: "Host name from which the data\n" +
                      "will be collected."
            }
        }

        AdaptiveComboBox {
                id: hostComboBox
                enabled: !manualHostCheckBox.checked
                textRole: "nameId"
                valueRole: "id"
                popup.y: height
                displayText: currentIndex === -1
                             ? ("Please choose a host...")
                             : currentText
                model: alertHostModel
                Component.onCompleted: currentIndex = -1

                onActivated: {
                    activeOk = true
                }
        }

        Label {
            id: userLabel
            text: "User: "
            InfoToolTip {
                text: "User name from which the data\n" +
                      "will be collected."
            }
        }

        AdaptiveComboBox {
                id: userComboBox
                enabled: !manualUserCheckBox.checked
                textRole: "nameId"
                valueRole: "id"
                popup.y: height
                displayText: currentIndex === -1
                             ? ("Please choose a user...")
                             : currentText
                model: alertUserModel
                Component.onCompleted: currentIndex = -1

                onActivated: {
                    activeOk = true
                }
        }

        Label {
            id: topicLabel
            text: "Topic: "
            InfoToolTip {
                text: "Topic name from which the data\n" +
                      "will be collected."
            }
        }

        AdaptiveComboBox {
                id: topicComboBox
                enabled: !manualTopicCheckBox.checked
                textRole: "nameId"
                valueRole: "id"
                popup.y: height
                displayText: currentIndex === -1
                             ? ("Please choose a topic...")
                             : currentText
                model: alertTopicModel
                Component.onCompleted: currentIndex = -1

                onActivated: {
                    activeOk = true
                }
        }

        Label {
            text: "Threshold: "
            InfoToolTip {
                text: "Threshold of the throughput under which the alert will start triggering."
            }
        }

        TextField {
            id: alertThreshold
            enabled: alertKindComboBox.currentText !== "NEW_DATA"
            Connections {
                target: alertKindComboBox
                onCurrentTextChanged: {
                    if (alertKindComboBox.currentText === "NEW_DATA") {
                        alertThreshold.text = "0"
                    }
                }
            }
        }

        Label {
            text: "Time between alerts (ms): "
            InfoToolTip {
                text: "Minimum time between two consecutive alerts."
            }
        }
        SpinBox {
            id: alertTimeBetweenAlerts
            editable: true
            from: 0
            to: 10000
            stepSize: 50
            value: 5000
        }

        Rectangle {
            id: advancedOptionsSubmenu
            color: "transparent"

            property bool isExpanded: false
            readonly property int item_height_: alertDialog.item_height_
            readonly property int collapsed_options_box_height_: item_height_
            readonly property int options_box_body_height_: item_height_
            readonly property int expanded_options_box_height_: collapsed_options_box_height_ + 3*options_box_body_height_

            Layout.fillWidth: true
            Layout.preferredHeight: isExpanded
                ? expanded_options_box_height_ + 20
                : collapsed_options_box_height_ + 20

            Column {
                anchors.fill: parent
                spacing: layout_horizontal_spacing_
                RowLayout {
                    width: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                        height: 2
                        color: Theme.lightGrey
                    }

                    Rectangle {
                        width: 175
                        height: 30
                        radius: 15
                        color: advancedOptionsMouseArea.containsMouse ? Theme.grey : "transparent"
                        Row {
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: alertDialog.layout_vertical_spacing_
                            leftPadding: 10

                            IconSVG {
                            anchors.verticalCenter: parent.verticalCenter
                            name: advancedOptionsSubmenu.isExpanded ? "cross" : "plus"
                            size: 12
                            color: advancedOptionsMouseArea.containsMouse ? "white" : "grey"
                            }

                            Label {
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Advanced options"
                                color: advancedOptionsMouseArea.containsMouse ? "white" : "grey"
                            }
                        }

                        MouseArea {
                            id: advancedOptionsMouseArea
                            width: parent.width
                            height: parent.height
                            hoverEnabled: true
                            onClicked: {
                                advancedOptionsSubmenu.isExpanded = !advancedOptionsSubmenu.isExpanded
                            }
                        }
                    }
                }

                Column {
                    width: parent.width
                    visible: advancedOptionsSubmenu.isExpanded
                    height: advancedOptionsSubmenu.isExpanded ? advancedOptionsSubmenu.item_height_ : 0
                    spacing: alertDialog.layout_horizontal_spacing_

                    Row {
                        id: manualHost
                        spacing: alertDialog.layout_vertical_spacing_
                        CheckBox {
                            id: manualHostCheckBox
                            text: "Set host name manually"
                            checked: false

                            indicator: Rectangle {
                                implicitWidth: 16
                                implicitHeight: 16
                                anchors.verticalCenter: parent.verticalCenter
                                border.color: Theme.grey
                                border.width: 2
                                Rectangle {
                                    visible: manualHostCheckBox.checked
                                    color: Theme.eProsimaLightBlue
                                    radius: 1
                                    anchors.margins: 3
                                    anchors.fill: parent
                                }
                            }
                        }

                        TextField {
                            id: manualHostText
                            enabled: manualHostCheckBox.checked
                            selectByMouse: true
                            placeholderText: "manual_host_name"
                            width: 130
                            height: 5/6*advancedOptionsSubmenu.item_height_
                            anchors.verticalCenter: parent.verticalCenter

                            background: Rectangle {
                                color: !manualHostCheckBox.checked ? "#a0a0a0" : Theme.whiteSmoke
                                border.color: Theme.grey
                            }

                            onTextChanged: {
                            }
                        }
                    }

                    Row {
                        id: manualUser
                        spacing: alertDialog.layout_vertical_spacing_
                        CheckBox {
                            id: manualUserCheckBox
                            text: "Set user name manually"
                            checked: false

                            indicator: Rectangle {
                                implicitWidth: 16
                                implicitHeight: 16
                                anchors.verticalCenter: parent.verticalCenter
                                border.color: Theme.grey
                                border.width: 2
                                Rectangle {
                                    visible: manualUserCheckBox.checked
                                    color: Theme.eProsimaLightBlue
                                    radius: 1
                                    anchors.margins: 3
                                    anchors.fill: parent
                                }
                            }
                        }

                        TextField {
                            id: manualUserText
                            enabled: manualUserCheckBox.checked
                            selectByMouse: true
                            placeholderText: "manual_user_name"
                            width: 130
                            height: 5/6*advancedOptionsSubmenu.item_height_
                            anchors.verticalCenter: parent.verticalCenter

                            background: Rectangle {
                                color: !manualUserCheckBox.checked ? "#a0a0a0" : Theme.whiteSmoke
                                border.color: Theme.grey
                            }

                            onTextChanged: {
                            }
                        }
                    }

                    Row {
                        id: manualTopic
                        spacing: alertDialog.layout_vertical_spacing_
                        CheckBox {
                            id: manualTopicCheckBox
                            text: "Set topic name manually"
                            checked: false

                            indicator: Rectangle {
                                implicitWidth: 16
                                implicitHeight: 16
                                anchors.verticalCenter: parent.verticalCenter
                                border.color: Theme.grey
                                border.width: 2
                                Rectangle {
                                    visible: manualTopicCheckBox.checked
                                    color: Theme.eProsimaLightBlue
                                    radius: 1
                                    anchors.margins: 3
                                    anchors.fill: parent
                                }
                            }
                        }

                        TextField {
                            id: manualTopicText
                            enabled: manualTopicCheckBox.checked
                            selectByMouse: true
                            placeholderText: "manual_topic_name"
                            width: 130
                            height: 5/6*advancedOptionsSubmenu.item_height_
                            anchors.verticalCenter: parent.verticalCenter

                            background: Rectangle {
                                color: !manualTopicCheckBox.checked ? "#a0a0a0" : Theme.whiteSmoke
                                border.color: Theme.grey
                            }

                            onTextChanged: {
                            }
                        }
                    }
                }
            }
        }
    }

    MessageDialog {
        id: emptyAlertName
        title: "Missing alert name"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The alert name field is empty. Please enter an alert name."
        onAccepted: alertDialog.open()
        onDiscard: alertDialog.close()
    }

    function checkInputs() {
        if (alertNameTextField.text === "") {
            emptyAlertName.open()
            return false
        }

        return true
    }

    function updateTopics() {
        controller.update_available_entity_ids("Topic", "alertTopic")
        topicComboBox.recalculateWidth()
    }

    function updateUsers(){
        controller.update_available_entity_ids("User", "alertUser")
        userComboBox.recalculateWidth()
    }

    function updateHosts(){
        controller.update_available_entity_ids("Host", "alertHost")
        hostComboBox.recalculateWidth()
    }

    function abbreviateEntityName(entityName){
        return entityName.split(":")[0]
    }

    function regenerateAlertName(){
        alertNameTextField.text = ""
        if (manualHostCheckBox.checked && manualHostText.text !== "") {
            alertNameTextField.text += abbreviateEntityName(manualHostText.text)
        } else if (hostComboBox.currentIndex !== -1) {
            alertNameTextField.text += abbreviateEntityName(hostComboBox.currentText)
        }

        if (manualUserCheckBox.checked && manualUserText.text !== "") {
            alertNameTextField.text += "_" + abbreviateEntityName(manualUserText.text)
        } else if (userComboBox.currentIndex !== -1) {
            alertNameTextField.text += "_" + abbreviateEntityName(userComboBox.currentText)
        }

        if (manualTopicCheckBox.checked && manualTopicText.text !== "") {
            alertNameTextField.text += "_" + abbreviateEntityName(manualTopicText.text)
        } else if (topicComboBox.currentIndex !== -1) {
            alertNameTextField.text += "_" + abbreviateEntityName(topicComboBox.currentText)
        }

        if (alertKindComboBox.currentIndex !== -1) {
            alertNameTextField.text += "_" + alertKindComboBox.currentText
        }
    }
}
