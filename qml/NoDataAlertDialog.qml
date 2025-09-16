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
    id: noDataAlertKindDialog
    modal: false
    title: "Create new alert"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property bool activeOk: true

    Component.onCompleted: {
        standardButton(Dialog.Ok).text = qsTrId("Add")
        standardButton(Dialog.Cancel).text = qsTrId("Close")
        controller.update_available_entity_ids("Host", "getDataDialogSourceEntityId")
    }

    onAboutToShow: {
        getDataDialogSourceEntityId.currentIndex = 0
        updateAllEntities()
        sourceEntityId.currentIndex = -1
        alertTextField.text = ""
    }

    onAccepted: {
        if (!checkInputs())
            return

        if (activeOk) {
            createAlert()
        }
        activeOk = true
    }

    onApplied: {
        if (!checkInputs())
            return

        if (activeOk) {
            createAlert()
        }
        activeOk = false
        statisticKind.currentIndex = -1
        cumulative.checked = false
    }

    onClosed: activeOk = true

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: alertLabel
            text: "Alert label: "
            InfoToolTip {
                text: "Name of the alert.\n"+
                      "The alert name is autogerated\n" +
                      "using the values given in this\n" +
                      "dialog."
            }
        }
        TextField {
            id: alertTextField
            placeholderText: ""
            selectByMouse: true
            maximumLength: 100
            Layout.fillWidth: true

            onTextEdited: activeOk = true
        }


        Label {
            id: entityKindLabel
            text: "Entity kind: "
            InfoToolTip {
                text: "Entity kind from which the data\n" +
                      "will be collected."
            }
        }

        RowLayout {
            AdaptiveComboBox {
                id: getDataDialogSourceEntityId
                model: [
                    "Host",
                    "User",
                    "Process",
                    "Domain",
                    "Topic",
                    "DomainParticipant",
                    "DataWriter",
                    "DataReader",
                    "Locator"]

                onActivated: {
                    activeOk = true
                    updateEntities()
                }
            }
            AdaptiveComboBox {
                id: sourceEntityId
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
    }

    MessageDialog {
        id: emptyEntityIdDialog
        title: "Empty Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: noDataAlertDialog.open()
        onDiscard: noDataAlertDialog.close()
    }

    function checkInputs() {
        if (currentTopic.currentIndex === -1 || alertTextField.text === "") {
            emptyEntityIdDialog.open()
            return false
        }

        return true
    }
}
