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

import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Theme 1.0

Dialog {
    id: newDataAlertDialog
    modal: false
    title: "Create new alert"
    standardButtons: Dialog.Ok | Dialog.Cancel

    property bool activeOk: true
    property string currentAlertName: ""
    property string currentHost: ""
    property string currentUser: ""
    property string currentTopic: ""
    property int currentThreshold: 5
    property int currentTimeBetweenAlerts: 5000

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    signal createAlert(string alert_name, string host_name, string user_name, string topic_name,
                       int t_between_triggers)

    Component.onCompleted: {
        standardButton(Dialog.Ok).text = qsTrId("Add")
        standardButton(Dialog.Cancel).text = qsTrId("Close")
    }

    onAccepted: {
        if (!checkInputs())
            return

        currentAlertName = alertNameTextField.text
        currentHost = hostComboBox.currentText
        currentUser = userComboBox.currentText
        currentTopic = topicComboBox.currentText
        currentTimeBetweenAlerts = noDataTimeBetweenAlerts.value
        createAlert(currentAlertName, currentHost, currentUser, currentTopic, currentTimeBetweenAlerts)
    }

    onAboutToShow: {
        alertNameTextField.text = "<alert_name>"
        hostComboBox.currentIndex = 0
        topicComboBox.currentIndex = 0
        userComboBox.currentIndex = 0
        updateTopics()
        updateUsers()
        updateHosts()
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

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
                textRole: "host"
                valueRole: "id"
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
                textRole: "user"
                valueRole: "id"
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
                textRole: "topic"
                valueRole: "id"
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

        SpinBox {
            id: noDataThreshold
            editable: true
            from: 1
            to: 100
            stepSize: 1
            value: 5
        }

        Label {
            text: "Time between alerts (ms): "
            InfoToolTip {
                text: "Minimum time between two consecutive alerts."
            }
        }
        SpinBox {
            id: noDataTimeBetweenAlerts
            editable: true
            from: 0
            to: 10000
            stepSize: 50
            value: 5000
        }
    }

    MessageDialog {
        id: emptyAlertName
        title: "Missing alert name"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The alert name field is empty. Please enter an alert name."
        onAccepted: newDataAlertDialog.open()
        onDiscard: newDataAlertDialog.close()
    }

    MessageDialog {
        id: emptyTopic
        title: "Topic not selected"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The topic field is empty. Please choose a topic from the list."
        onAccepted: newDataAlertDialog.open()
        onDiscard: newDataAlertDialog.close()
    }

    function checkInputs() {
        if (topicComboBox.currentIndex === -1) {
            emptyTopic.open()
            return false
        }
        if (alertNameTextField.text === "") {
            emptyAlertName.open()
            return false
        }

        return true
    }

    function updateTopics() {
        controller.update_available_entity_ids("Topic", "alertTopic")
    }

    function updateUsers(){
        controller.update_available_entity_ids("User", "alertUser")
    }

    function updateHosts(){
        controller.update_available_entity_ids("Host", "alertHost")
    }

    function formatText(count, modelData) {
        var data = count === 24 ? modelData + 1 : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }
}
