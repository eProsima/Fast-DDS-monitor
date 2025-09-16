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
    property string currentTopic: ""

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    signal createAlert(string topicId)

    Component.onCompleted: {
        standardButton(Dialog.Ok).text = qsTrId("Add")
        standardButton(Dialog.Cancel).text = qsTrId("Close")

        // Get the available topics from the backend
        controller.update_available_entity_ids("Topic", "getDataDialogSourceEntityId")
    }

    onAccepted: {
        if (!checkInputs())
            return

        currentTopic = topicComboBox.currentText
        createAlert(currentTopic)
    }

    onAboutToShow: {
        getDataDialogSourceEntityId.currentIndex = 0
        alertTextField.text = ""
        controller.update_available_entity_ids("Topic", "getDataDialogSourceEntityId")
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: seriesLabel
            text: "Alert label: "
            InfoToolTip {
                text: "Name of the alert.\n"
            }
        }
        TextField {
            id: alertTextField
            placeholderText: ""
            selectByMouse: true
            maximumLength: 50
            Layout.fillWidth: true

            onTextEdited: activeOk = true
        }


        Label {
            id: sourceEntityIdLabel
            text: "Source Entity Id: "
            InfoToolTip {
                text: "Entity from which the data\n" +
                      "will be collected."
            }
        }
        RowLayout {
            AdaptiveComboBox {
                id: getDataDialogSourceEntityId
                model: ["Topic"]

                onActivated: {
                    activeOk = true
                }
            }
            AdaptiveComboBox {
                id: topicComboBox
                textRole: "nameId"
                valueRole: "id"
                displayText: currentIndex === -1
                             ? ("Please choose a " + getDataDialogSourceEntityId.currentText + "...")
                             : currentText
                model: entityModelFirst

                onActivated: {
                    activeOk = true
                }
            }
        }

    }

    MessageDialog {
        id: emptyAlertLabel
        title: "Missing alert label"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The alert label field is empty. Please enter an alert label."
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
        if (alertTextField.text === "") {
            emptyAlertLabel.open()
            return false
        }

        return true
    }

    function updateEntities() {
        controller.update_available_entity_ids("Topic", "getDataDialogSourceEntityId")
    }

}
