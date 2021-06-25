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
import Theme 1.0

Dialog {
    id: displayStatisticsDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Apply | Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property string startTimeDate: "" + new Date().toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
    property string endTimeDate: "" + new Date().toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")

    property bool targetExists: false

    property bool activeOk: true

    Component.onCompleted: {
        if (chartTitle == "FASTDDS_LATENCY" |
                chartTitle == "NETWORK_LATENCY" |
                chartTitle == "RTPS_PACKETS_SENT" |
                chartTitle == "RTPS_BYTES_SENT" |
                chartTitle == "RTPS_PACKETS_LOST" |
                chartTitle == "RTPS_BYTES_LOST") {
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
                text: "Name of the series\n"+
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
            id: binsLabel
            text: "Number of bins: "
            InfoToolTip {
                text: "Number of time points to be\n" +
                      "plotted.\n" +
                      "If bins is equal to 0, all\n" +
                      "available values will be\n" +
                      "represented.\n" +
                      "In case bins is greater than\n" +
                      "0, the selected statistic will\n" +
                      "be applied in each time\n" +
                      "interval."
            }
        }
        SpinBox {
            id: bins
            editable: true
            from: 0
            to: 9999
            value: 0

            onValueModified: activeOk = true
        }

        Label {
            text: "Start time: "
            InfoToolTip {
                text: "Initial time from which data\n" +
                      "are collected."
            }
        }
        ColumnLayout {
            id: startTimeValues

            RowLayout {
                Label {
                    text: "Default inital timestamp: "
                    InfoToolTip {
                        text: "The default start timestamp\n" +
                              "is the time at which the\n" +
                              "monitor application was\n" +
                              "launched."
                    }
                }

                CheckBox {
                    id: startTimeDefault
                    checked: false
                    indicator.width: 20
                    indicator.height: 20
                    onCheckedChanged: {
                        activeOk = true
                        if (checked) {
                            startTimeCalendarButton.enabled = false

                        } else {
                            startTimeCalendarButton.enabled = true
                        }
                    }
                }
            }

            Button {
                id: startTimeCalendarButton
                text: startTimeDate
                onClicked: {
                    startTimeCalendarDialog.open()
                }
                enabled: true
            }
        }


        Label {
            text: "End time: "
            InfoToolTip {
                text: "End timestamp of the data\n" +
                      "series."
            }
        }
        ColumnLayout {
            id: endTimeValues

            RowLayout {
                Label {
                    text: "Now: "
                }

                CheckBox {
                    id: endTimeDefault
                    checked: false
                    indicator.width: 20
                    indicator.height: 20
                    onCheckedChanged: {
                        activeOk = true
                        if (checked) {
                            endTimeCalendarButton.enabled = false

                        } else {
                            endTimeCalendarButton.enabled = true
                        }
                    }
                }
            }

            Button {
                id: endTimeCalendarButton
                text: endTimeDate
                onClicked: {
                    endTimeCalendarDialog.open()
                }
            }
        }

        Label {
            text: "Statistic kind: "
            InfoToolTip {
                text: "Cumulative function that is\n" +
                      "applied to the data of each\n" +
                      "time interval.\n" +
                      "If NONE is selected, the first\n" +
                      "available data of the interval\n" +
                      "is taken."
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

    Dialog {
        id: startTimeCalendarDialog
        title: "Choose the start timestamp"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            activeOk = true
            var tmpDate = new Date(startTimeCalendar.selectedDate)
            var timeDate = Date.fromLocaleTimeString(Qt.locale(), startTime.text, "HH:mm:ss")
            tmpDate.setHours(timeDate.getHours(),
                             timeDate.getMinutes(),
                             timeDate.getSeconds(),
                             0)
            startTimeDate = tmpDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        }

        ColumnLayout {

            Label {
                text: "Date: "
            }
            QCC1.Calendar {
                id: startTimeCalendar
            }

            Rectangle {
                id: startTimeseparator
                Layout.fillWidth: true
                height: 10
                color: "transparent"
            }

            Label {
                text: "Time: "
            }
            TextField {
                id: startTime
                text : "00:00:00"
                inputMask: "99:99:99"
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegExpValidator {
                    regExp: /^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):[0-5][0-9]$ /
                }

                Layout.fillWidth: true
            }
        }
    }

    Dialog {
        id: endTimeCalendarDialog
        title: "Choose the end timestamp"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            activeOk = true
            var tmpDate = new Date(endTimeCalendar.selectedDate)
            var timeDate = Date.fromLocaleTimeString(Qt.locale(), endTime.text, "HH:mm:ss")
            tmpDate.setHours(timeDate.getHours(),
                             timeDate.getMinutes(),
                             timeDate.getSeconds(),
                             0)
            endTimeDate = tmpDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        }

        ColumnLayout {

            Label {
                text: "Date: "
            }
            QCC1.Calendar {
                id: endTimeCalendar
            }

            Rectangle {
                id: endTimeseparator
                Layout.fillWidth: true
                height: 10
                color: "transparent"
            }

            Label {
                text: "Time: "
            }
            TextField {
                id: endTime
                text : "00:00:00"
                inputMask: "99:99:99"
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegExpValidator {
                    regExp: /^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):[0-5][0-9]$ /
                }

                Layout.fillWidth: true
            }
        }
    }

    MessageDialog {
        id: wrongDatesDialog
        title: "Wrong Timestamps"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The start timestamp entered is posterior to the end timestamp."
        onAccepted: {
            displayStatisticsDialog.open()
        }
    }

    MessageDialog {
        id: emptySourceEntityIdDialog
        title: "Empty Source Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The source Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: {
            displayStatisticsDialog.open()
        }
    }

    MessageDialog {
        id: emptyTargetEntityIdDialog
        title: "Empty Target Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The target Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: {
            displayStatisticsDialog.open()
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

        var startTime = Date.fromLocaleString(
                    Qt.locale(),
                    startTimeDate,
                    "dd.MM.yyyy HH:mm:ss")

        var endTime
        if (endTimeDefault.checked) {
            endTime = new Date()
        } else {
            endTime = Date.fromLocaleString(
                    Qt.locale(),
                    endTimeDate,
                    "dd.MM.yyyy HH:mm:ss")
        }

        if (startTime <= endTime) {
            controlPanel.addSeries(
                        chartTitle,
                        (seriesLabelTextField.text === "") ? seriesLabelTextField.placeholderText : seriesLabelTextField.text,
                        sourceEntityId.currentValue,
                        (targetExists) ? targetEntityId.currentValue : '',
                        bins.value,
                        startTime,
                        startTimeDefault.checked,
                        endTime,
                        endTimeDefault.checked,
                        statisticKind.currentText)
        } else {
            if (!startTimeDefault.checked) {
                wrongDatesDialog.open()
            }
        }
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


