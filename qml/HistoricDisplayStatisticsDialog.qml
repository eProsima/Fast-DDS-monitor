// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

import QtQuick
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls

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
    property var availableStatisticKinds: []

    Component.onCompleted: {
        standardButton(Dialog.Apply).text = qsTrId("Add")
        standardButton(Dialog.Ok).text = qsTrId("Add && Close")
        standardButton(Dialog.Cancel).text = qsTrId("Close")

        // Get the available statistic kinds from the backend
        availableStatisticKinds = controller.get_statistic_kinds()

        if (controller.data_kind_has_target(dataKind)) {
            targetExists = true
        }

        controller.update_available_entity_ids("Host", "getDataDialogSourceEntityId")
        controller.update_available_entity_ids("Host", "getDataDialogDestinationEntityId")
        regenerateSeriesLabel()
    }

    onAboutToShow: {
        getDataDialogSourceEntityId.currentIndex = 0
        getDataDialogTargetEntityId.currentIndex = 0
        updateAllEntities()
        statisticKind.currentIndex = -1
        sourceEntityId.currentIndex = -1
        targetEntityId.currentIndex = -1
    }

    onAccepted: {
        if (!checkInputs())
            return

        if (activeOk) {
            createSeries()
        }
        activeOk = true
        statisticKind.currentIndex = -1
    }

    onApplied: {
        if (!checkInputs())
            return

        if (activeOk) {
            createSeries()
        }
        activeOk = false
        statisticKind.currentIndex = -1
    }

    onClosed: activeOk = true

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
                    updateSources()
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
                    updateTargets()
                }
            }
            AdaptiveComboBox {
                id: targetEntityId
                textRole: "nameId"
                valueRole: "id"
                displayText: currentIndex === -1
                             ? ("Please choose a " + getDataDialogTargetEntityId.currentText + "...")
                             : currentText
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
            displayText: currentIndex === -1 ? "Please choose a statistic..." : currentText
            model: availableStatisticKinds
            popup.y: height

            Component.onCompleted: currentIndex = -1

            onActivated: {
                activeOk = true
                regenerateSeriesLabel()
            }
        }
    }

    Dialog {
        id: startTimeCalendarDialog
        title: "Choose the start timestamp"
        standardButtons: Dialog.Save | Dialog.Cancel

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            activeOk = true
            var tmpDate = new Date(startYear.value, startMonth.value - 1, startDay.value)
            var timeDate = Date.fromLocaleTimeString(Qt.locale(), startTime.text, "HH:mm:ss")
            tmpDate.setHours(timeDate.getHours(),
                            timeDate.getMinutes(),
                            timeDate.getSeconds(),
                            0)
            startTimeDate = tmpDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        }

        ColumnLayout {
            spacing: 10

            Label {
                text: "Date: "
            }
            
            GridLayout {
                columns: 3
                rowSpacing: 5
                columnSpacing: 10

                Label { text: "Day:" }
                Label { text: "Month:" }
                Label { text: "Year:" }

                SpinBox {
                    id: startDay
                    from: 1
                    to: 31
                    value: {
                        var date = Date.fromLocaleString(Qt.locale(), startTimeDate, "dd.MM.yyyy HH:mm:ss")
                        return date.getDate()
                    }
                    editable: true
                }

                SpinBox {
                    id: startMonth
                    from: 1
                    to: 12
                    value: {
                        var date = Date.fromLocaleString(Qt.locale(), startTimeDate, "dd.MM.yyyy HH:mm:ss")
                        return date.getMonth() + 1
                    }
                    editable: true
                    
                    textFromValue: function(value) {
                        return ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"][value - 1]
                    }
                    valueFromText: function(text) {
                        var months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
                        return months.indexOf(text) + 1
                    }
                }

                SpinBox {
                    id: startYear
                    from: 1900
                    to: 2100
                    value: {
                        var date = Date.fromLocaleString(Qt.locale(), startTimeDate, "dd.MM.yyyy HH:mm:ss")
                        return date.getFullYear()
                    }
                    editable: true
                    stepSize: 1
                    
                    textFromValue: function(value) {
                        return value.toString()
                    }
                    
                    valueFromText: function(text) {
                        return parseInt(text)
                    }
                }
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
                text: "00:00:00"
                inputMask: "99:99:99"
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegularExpressionValidator {
                    regularExpression: /^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):[0-5][0-9]$/
                }

                Layout.fillWidth: true
            }
        }
    }

    Dialog {
        id: endTimeCalendarDialog
        title: "Choose the end timestamp"
        standardButtons: Dialog.Save | Dialog.Cancel

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            activeOk = true
            var tmpDate = new Date(endYear.value, endMonth.value - 1, endDay.value)
            var timeDate = Date.fromLocaleTimeString(Qt.locale(), endTime.text, "HH:mm:ss")
            tmpDate.setHours(timeDate.getHours(),
                            timeDate.getMinutes(),
                            timeDate.getSeconds(),
                            0)
            endTimeDate = tmpDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        }

        ColumnLayout {
            spacing: 10

            Label {
                text: "Date: "
            }
            
            GridLayout {
                columns: 3
                rowSpacing: 5
                columnSpacing: 10

                Label { text: "Day:" }
                Label { text: "Month:" }
                Label { text: "Year:" }

                SpinBox {
                    id: endDay
                    from: 1
                    to: 31
                    value: {
                        var date = Date.fromLocaleString(Qt.locale(), endTimeDate, "dd.MM.yyyy HH:mm:ss")
                        return date.getDate()
                    }
                    editable: true
                }

                SpinBox {
                    id: endMonth
                    from: 1
                    to: 12
                    value: {
                        var date = Date.fromLocaleString(Qt.locale(), endTimeDate, "dd.MM.yyyy HH:mm:ss")
                        return date.getMonth() + 1
                    }
                    editable: true
                    
                    textFromValue: function(value) {
                        return ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"][value - 1]
                    }
                    valueFromText: function(text) {
                        var months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
                        return months.indexOf(text) + 1
                    }
                }

                SpinBox {
                    id: endYear
                    from: 1900
                    to: 2100
                    value: {
                        var date = Date.fromLocaleString(Qt.locale(), endTimeDate, "dd.MM.yyyy HH:mm:ss")
                        return date.getFullYear()
                    }
                    editable: true
                    stepSize: 1
                    
                    textFromValue: function(value) {
                        return value.toString()
                    }
                    
                    valueFromText: function(text) {
                        return parseInt(text)
                    }
                }
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
                text: "00:00:00"
                inputMask: "99:99:99"
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegularExpressionValidator {
                    regularExpression: /^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):[0-5][0-9]$/
                }

                Layout.fillWidth: true
            }
        }
    }

    MessageDialog {
        id: wrongDatesDialog
        title: "Wrong Timestamps"
        buttons: MessageDialog.Retry | MessageDialog.Discard
        text: "The start timestamp entered is posterior to the end timestamp."
        onAccepted: {
            displayStatisticsDialog.open()
        }
        onButtonClicked: function (button, role) {
            switch (button) {
                case MessageDialog.Retry:
                    displayStatisticsDialog.open()
                    break;
                case MessageDialog.Discard:
                    break;
            }
        }
    }

    MessageDialog {
        id: emptySourceEntityIdDialog
        title: "Empty Source Entity Id"
        buttons: MessageDialog.Retry | MessageDialog.Discard
        text: "The source Entity Id field is empty. Please choose an Entity Id from the list."
        onButtonClicked: function (button, role) {
            switch (button) {
                case MessageDialog.Retry:
                    displayStatisticsDialog.open()
                    break;
                case MessageDialog.Discard:
                    displayStatisticsDialog.close()
                    break;
            }
        }
    }

    MessageDialog {
        id: emptyTargetEntityIdDialog
        title: "Empty Target Entity Id"
        buttons: MessageDialog.Retry | MessageDialog.Discard
        text: "The target Entity Id field is empty. Please choose an Entity Id from the list."
        onButtonClicked: function (button, role) {
            switch (button) {
                case MessageDialog.Retry:
                    displayStatisticsDialog.open()
                    break;
                case MessageDialog.Discard:
                    displayStatisticsDialog.close()
                    break;
            }
        }
    }

    MessageDialog {
        id: emptyStatisticKind
        title: "Empty Statistic Kind"
        buttons: MessageDialog.Retry | MessageDialog.Discard
        text: "The statistic kind field is empty. Please choose a statistic from the list."
        onButtonClicked: function (button, role) {
            switch (button) {
                case MessageDialog.Retry:
                    displayStatisticsDialog.open()
                    break;
                case MessageDialog.Discard:
                    displayStatisticsDialog.close()
                    break;
            }
        }
    }

    function createSeries() {
        if (!checkInputs())
            return

        controlPanel.addHistoricSeries(
                    dataKind,
                    (seriesLabelTextField.text === "") ? seriesLabelTextField.placeholderText : seriesLabelTextField.text,
                    sourceEntityId.currentValue,
                    (targetExists) ? targetEntityId.currentValue : '',
                    bins.value,
                    Date.fromLocaleString(Qt.locale(), startTimeDate, "dd.MM.yyyy HH:mm:ss"),
                    startTimeDefault.checked,
                    Date.fromLocaleString(Qt.locale(), endTimeDate, "dd.MM.yyyy HH:mm:ss"),
                    endTimeDefault.checked,
                    statisticKind.currentText)
    }

    function checkInputs() {
        if (sourceEntityId.currentText == "") {
            emptySourceEntityIdDialog.open()
            return false
        } else if ((targetEntityId.currentText == "") && targetExists) {
            emptyTargetEntityIdDialog.open()
            return false
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

        if (startTime >= endTime && !startTimeDefault.checked) {
            wrongDatesDialog.open()
            return false
        }
        return true
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
        // Workaround for Host too long name
        if (entityName.length > 20) {
            var entityName_id_str = entityName.split("<")
            return entityName.split(":")[0] + "<" + entityName_id_str[entityName_id_str.length-1]
        }else{
            return entityName
        }
    }

    function updateSources() {
        controller.update_available_entity_ids(getDataDialogSourceEntityId.currentText, "getDataDialogSourceEntityId")
        sourceEntityId.recalculateWidth()
        regenerateSeriesLabel()
    }

    function updateTargets() {
        controller.update_available_entity_ids(getDataDialogTargetEntityId.currentText, "getDataDialogDestinationEntityId")
        targetEntityId.recalculateWidth()
        regenerateSeriesLabel()
    }

    function updateAllEntities() {
        updateSources()
        updateTargets()
    }
}
