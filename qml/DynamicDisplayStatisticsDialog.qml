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
    id: dynamicDisplayStatisticsDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Apply | Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

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
        cumulative.checked = false
        advanced.showAdvancedOptions = false
    }

    onAccepted: {
        if (!checkInputs())
            return

        if (activeOk) {
            createSeries()
        }
        activeOk = true
    }

    onApplied: {
        if (!checkInputs())
            return

        if (activeOk) {
            createSeries()
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
            maximumLength: 100
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

                Component.onCompleted: currentIndex = -1

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

                Component.onCompleted: currentIndex = -1

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
                      "If RAW DATA is selected, all \n" +
                      "available data in the last\n" +
                      "time frame is displayed and\n" +
                      "the cumulative option is\n" +
                      "disabled."
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

                if (currentText == "RAW DATA") {
                    cumulativeLabel.enabled = false
                    cumulative.enabled = false
                    cumulative.checked = false
                } else {
                    cumulativeLabel.enabled = true
                    cumulative.enabled = true
                }
            }
        }

        RowLayout {
            Layout.columnSpan: 2

            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: Theme.lightGrey
            }

            Rectangle {
                id: advanced
                width: 100
                height: 30
                radius: 15
                color: advancedMouseArea.containsMouse ? Theme.grey : "transparent"

                property bool showAdvancedOptions: false

                RowLayout {
                    spacing: 5
                    anchors.centerIn: parent

                    IconSVG {
                        id: participantIcon
                        name: advanced.showAdvancedOptions ? "cross" : "plus"
                        size: 12
                        color: advancedMouseArea.containsMouse ? "white" : "grey"
                    }
                    Label {
                        id: advancedLabel
                        text: "Advanced"
                        color: advancedMouseArea.containsMouse ? "white" : "grey"
                    }
                }

                MouseArea {
                    id: advancedMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: advanced.showAdvancedOptions = !advanced.showAdvancedOptions
                }
            }
        }

        Label {
            id: cumulativeLabel
            text: qsTr("Cumulative data: ")
            visible: advanced.showAdvancedOptions
            InfoToolTip {
                text: "If checked, each data point is\n" +
                      "calculated using as the final\n" +
                      "timestamp the updated time after\n" +
                      "the update period has elapsed,\n" +
                      "and as initial the final timestamp\n" +
                      "minus the cumulative time interval.\n"
            }
        }
        RowLayout {
            visible: advanced.showAdvancedOptions

            CheckBox {
                id: cumulative
                checked: false
                onCheckedChanged: {
                    activeOk = true
                    regenerateSeriesLabel()
                }
            }

            Rectangle {
                width: 2
                height: cumulativeInterval.childrenRect.height + 2 * cumulativeInterval.spacing
                color: Theme.grey
                visible: cumulative.checked
            }

            Rectangle {
                width: 5
                height: cumulativeInterval.height
                color: "transparent"
                visible: cumulative.checked
            }

            ColumnLayout {
                id: cumulativeInterval
                visible: cumulative.checked

                Label {
                    id: cumulativeIntervalLabel
                    text: qsTr("Cumulative interval: ")
                    visible: cumulative.checked
                    InfoToolTip {
                        text: "Time interval to calculate the\n" +
                              "cumulated statistic."
                    }
                }

                RowLayout {
                    Label {
                        text: "From first data point: "
                    }

                    CheckBox {
                        id: cumulativeIntervalDefault
                        checked: true
                        indicator.width: 20
                        indicator.height: 20
                        onCheckedChanged: {
                            activeOk = true
                            regenerateSeriesLabel()
                        }
                    }
                }

                GridLayout {
                    id: cumulativeIntervalTimeDuration
                    columns: 3

                    RowLayout {
                        TextField {
                            id: cumulativeIntervalHours
                            text: qsTr("00")
                            placeholderText: qsTr("00")
                            enabled: !cumulativeIntervalDefault.checked
                            selectByMouse: true
                            selectionColor: Theme.eProsimaLightBlue
                            validator: IntValidator {
                                bottom: 0
                            }
                            inputMethodHints: Qt.ImhDigitsOnly
                            onTextChanged: regenerateSeriesLabel()
                        }
                        Label {
                            text: "Hours"
                            enabled: !cumulativeIntervalDefault.checked
                        }
                    }
                    RowLayout {
                        TextField {
                            id: cumulativeIntervalMinutes
                            text: qsTr("01")
                            placeholderText: qsTr("00")
                            enabled: !cumulativeIntervalDefault.checked
                            selectByMouse: true
                            selectionColor: Theme.eProsimaLightBlue
                            validator: IntValidator {
                                bottom: 0
                            }
                            inputMethodHints: Qt.ImhDigitsOnly
                            onTextChanged: regenerateSeriesLabel()
                        }
                        Label {
                            text: "Minutes"
                            enabled: !cumulativeIntervalDefault.checked
                        }
                    }
                    RowLayout {
                        TextField {
                            id: cumulativeIntervalSeconds
                            text: qsTr("00")
                            placeholderText: qsTr("00")
                            enabled: !cumulativeIntervalDefault.checked
                            selectByMouse: true
                            selectionColor: Theme.eProsimaLightBlue
                            validator: IntValidator {
                                bottom: 0
                            }
                            inputMethodHints: Qt.ImhDigitsOnly
                            onTextChanged: regenerateSeriesLabel()
                        }
                        Label {
                            text: "Seconds"
                            enabled: !cumulativeIntervalDefault.checked
                        }
                    }
                }
            }
        }
    }

    MessageDialog {
        id: emptySourceEntityIdDialog
        title: "Empty Source Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The source Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: dynamicDisplayStatisticsDialog.open()
        onDiscard: dynamicDisplayStatisticsDialog.close()
    }

    MessageDialog {
        id: emptyTargetEntityIdDialog
        title: "Empty Target Entity Id"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The target Entity Id field is empty. Please choose an Entity Id from the list."
        onAccepted: dynamicDisplayStatisticsDialog.open()
        onDiscard: dynamicDisplayStatisticsDialog.close()
    }

    MessageDialog {
        id: emptyStatisticKind
        title: "Empty Statistic Kind"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The statistic kind field is empty. Please choose a statistic from the list."
        onAccepted: dynamicDisplayStatisticsDialog.open()
        onDiscard: dynamicDisplayStatisticsDialog.close()
    }

    MessageDialog {
        id: emptyCumulativeInterval
        title: "Empty Cumulative Interval"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The cumulative time interval is zero. " +
              "Enter a valid time interval or check the \"From first data point\" option."
        onAccepted: dynamicDisplayStatisticsDialog.open()
        onDiscard: dynamicDisplayStatisticsDialog.close()
    }

    function createSeries() {
        if (!checkInputs())
            return

        controlPanel.addDynamicSeries(
                    (seriesLabelTextField.text === "") ? seriesLabelTextField.placeholderText : seriesLabelTextField.text,
                    sourceEntityId.currentValue,
                    (targetExists) ? targetEntityId.currentValue : '',
                    statisticKind.currentText,
                    cumulative.checked,
                    cumulativeIntervalDefault.checked ? 0 : cumulativeIntervalToSeconds())
    }

    function checkInputs() {
        if (sourceEntityId.currentText == "") {
            emptySourceEntityIdDialog.open()
            return false
        } else if ((targetEntityId.currentText == "") && targetExists) {
            emptyTargetEntityIdDialog.open()
            return false
        }

        if (statisticKind.currentIndex === -1) {
            emptyStatisticKind.open()
            return false
        }

        if (cumulative.checked && !cumulativeIntervalDefault.checked) {
            var cumulativeTimeFrame = cumulativeIntervalToSeconds()
            if (cumulativeTimeFrame === 0) {
                emptyCumulativeInterval.open()
                return false
            }
        }

        return true
    }

    function cumulativeIntervalToSeconds() {
        var hours = (cumulativeIntervalHours.text === "") ? 0 : parseInt(cumulativeIntervalHours.text)
        var minutes = (cumulativeIntervalMinutes.text === "") ? 0 : parseInt(cumulativeIntervalMinutes.text)
        var seconds = (cumulativeIntervalSeconds.text === "") ? 0 : parseInt(cumulativeIntervalSeconds.text)

        return (hours*3600 + minutes*60 + seconds)
    }

    function cumulativeIntervalToMinutes() {
        var hours = (cumulativeIntervalHours.text === "") ? 0 : parseInt(cumulativeIntervalHours.text)
        var minutes = (cumulativeIntervalMinutes.text === "") ? 0 : parseInt(cumulativeIntervalMinutes.text)
        var seconds = (cumulativeIntervalSeconds.text === "") ? 0 : parseInt(cumulativeIntervalSeconds.text)

        return (hours*60 + minutes + seconds/60)
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

        if (cumulative.checked) {
            if (cumulativeIntervalDefault.checked) {
                text += "_" +
                        "cumulative-default"
            } else {
                var cumulative_minutes = cumulativeIntervalToMinutes()
                var cumulative_only_seconds = (cumulativeIntervalSeconds.text === "") ? 0 : parseInt(cumulativeIntervalSeconds.text)

                if (Number.isInteger(cumulative_minutes)) {
                    text += "_cumulative-" + cumulative_minutes + "min"
                } else if (Math.floor(cumulative_minutes) == 0) {
                    text += "_cumulative-" + cumulativeIntervalToSeconds() + "s"
                } else {
                    text += "_cumulative-" + Math.floor(cumulative_minutes) + "min," + cumulative_only_seconds%60 + "s"
                }
            }
        }

        seriesLabelTextField.placeholderText = text;
    }

    function abbreviateEntityName(entityName){
        // TODO workaround for Host too long name. Erase when alias are included
        if (entityName.length > 20) {
            var entityName_id_str = entityName.split("<")
            return entityName.split(":")[0] + "<" + entityName_id_str[entityName_id_str.length-1]
        } else {
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


