// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import QtQml 2.15
import QtQuick 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.calendar 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QCC1
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12

Dialog {
    id: dynamicDisplayStatisticsDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Apply | Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property bool targetExists: false

    property bool activeOk: true

    Component.onCompleted: {
        if (dataKind == "FASTDDS_LATENCY" |
                dataKind == "NETWORK_LATENCY" |
                dataKind == "RTPS_PACKETS_SENT" |
                dataKind == "RTPS_BYTES_SENT" |
                dataKind == "RTPS_PACKETS_LOST" |
                dataKind == "RTPS_BYTES_LOST") {
            targetExists = true
        }

        controller.update_available_entity_ids("Host", "getDataDialogSourceEntityId")
        controller.update_available_entity_ids("Host", "getDataDialogDestinationEntityId")
        regenerateSeriesLabel()
    }

    onAccepted: {
        if (activeOk) {
            createSeries()
        }
        activeOk = true
    }

    onApplied: {
        activeOk = false
        createSeries()
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: seriesLabel
            text: "Series label: "
            InfoToolTip {
                text: "Name of the series.\n"+
                      "The series name is autogerated\n" +
                      "using the values given in this\n" +
                      "dialog."
            }
        }
        TextField {
            id: seriesLabelTextField
            placeholderText: ""
            selectByMouse: true
            maximumLength: 20
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
                    controller.update_available_entity_ids(currentText, "getDataDialogSourceEntityId")
                    sourceEntityId.recalculateWidth()
                    regenerateSeriesLabel()
                }
            }
            AdaptiveComboBox {
                id: sourceEntityId
                textRole: "nameId"
                valueRole: "id"
                model: entityModelFirst

                onActivated: {
                    activeOk = true
                    regenerateSeriesLabel()
                }
            }
        }

        Label {
            id: targetEntityIdLabel
            text: "Target Entity Id: "
            visible: targetExists
            InfoToolTip {
                text: "This is the entity to which\n" +
                      "the data refer.\n" +
                      "It is available only for those\n" +
                      "data kinds that involve a\n" +
                      "source and a target entity\n" +
                      "such as latency."
            }
        }
        RowLayout {
            id: targetEntityIdLayout
            visible: targetExists
            AdaptiveComboBox {
                id: getDataDialogTargetEntityId
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
                onActivated:  {
                    activeOk = true
                    controller.update_available_entity_ids(currentText, "getDataDialogDestinationEntityId")
                    targetEntityId.recalculateWidth()
                    regenerateSeriesLabel()
                }
            }
            AdaptiveComboBox {
                id: targetEntityId
                textRole: "nameId"
                valueRole: "id"
                model: entityModelSecond

                onActivated: {
                    activeOk = true
                    regenerateSeriesLabel()
                }
            }
        }

        Label {
            text: "Statistic kind: "
            InfoToolTip {
                text: "Cumulative function that is\n" +
                      "applied to the data of each\n" +
                      "time interval.\n" +
                      "If NONE is selected, all \n" +
                      "available data in the last\n" +
                      "time frame is displayed.\n"
            }
        }
        AdaptiveComboBox {
            id: statisticKind
            model: [
                "NONE",
                "MEAN",
                "STANDARD_DEVIATION",
                "MAX",
                "MIN",
                "MEDIAN",
                "COUNT",
                "SUM"]

            onActivated: {
                activeOk = true
                regenerateSeriesLabel()
            }
        }
    }

    MessageDialog {
        id: emptySourceEntityIdDialog
        title: "Empty Source Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The source Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: {
            dynamicDisplayStatisticsDialog.open()
        }
    }

    MessageDialog {
        id: emptyTargetEntityIdDialog
        title: "Empty Target Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The target Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: {
            dynamicDisplayStatisticsDialog.open()
        }
    }

    function createSeries() {
        if (sourceEntityId.currentText == "") {
            emptySourceEntityIdDialog.open()
            return
        } else if ((targetEntityId.currentText == "") && targetExists) {
            emptyTargetEntityIdDialog.open()
            return
        }

        controlPanel.addDynamicSeries(
                    (seriesLabelTextField.text === "") ? seriesLabelTextField.placeholderText : seriesLabelTextField.text,
                    sourceEntityId.currentValue,
                    (targetExists) ? targetEntityId.currentValue : '',
                    statisticKind.currentText)
    }

    function formatText(count, modelData) {
        var data = count === 24 ? modelData + 1 : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }

    function regenerateSeriesLabel(){
        var text = ((statisticKind.currentText === "STANDARD_DEVIATION") ? "SD" : statisticKind.currentText) +
                   "_" +
                   abbreviateEntityName(sourceEntityId.currentText)
        if (targetExists) {
            text += "_" +
                    abbreviateEntityName(targetEntityId.currentText)
        }
        seriesLabelTextField.placeholderText = text;
    }

    function abbreviateEntityName(entityName){
        // TODO workaround for Host too long name. Erase when alias are included
        if (entityName.length > 20) {
            var entityName_id_str = entityName.split("<")
            return entityName.split(":")[0] + "<" + entityName_id_str[entityName_id_str.length-1]
        }else{
            return entityName
        }
    }
}


