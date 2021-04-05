import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12
import Controller 1.0

Dialog {
    id: displayStatisticsDialog
    modality: Qt.NonModal
    title: "Display new statistics data"

    width: 450
    height: 250

    property var locale: Qt.locale()
    property string startTimeDate: "" + new Date().toLocaleDateString(locale, "dd.MM.yyyy")
    property string endTimeDate: "" + new Date().toLocaleDateString(locale, "dd.MM.yyyy")

    property var targetEntityIdComponent: Qt.createComponent("AdditionalEntityId.qml")
    property var targetEntityIdObject: null

    Component.onCompleted: {
        if (chartTitle == "FASTDDS_LATENCY" |
                chartTitle == "NETWORK_LATENCY" |
                chartTitle == "RTPS_PACKETS_SENT" |
                chartTitle == "RTPS_BYTES_SENT" |
                chartTitle == "RTPS_PACKETS_LOST" |
                chartTitle == "RTPS_BYTES_LOST") {
            if (targetEntityIdObject === null) {
                targetEntityIdObject = targetEntityIdComponent.createObject(entityIdModelSecondRow);
            }
        } else {
            if (targetEntityIdObject !== null) {
                targetEntityIdObject.destroy();
            }
        }
    }

    onAccepted: {
        var startTime = Date.fromLocaleString(
                    locale,
                    startTimeDate + " " +
                        startTimeHour.value + ":" + startTimeMinute.value + ":" + startTimeSecond.value,
                    "dd.MM.yyyy h:m:s")

        var endTime = Date.fromLocaleString(
                    locale,
                    endTimeDate + " " +
                        endTimeHour.value + ":" + endTimeMinute.value + ":" + endTimeSecond.value,
                    "dd.MM.yyyy h:m:s")

        controlPanel.addSeries(
                    chartTitle,
                    sourceEntityId.currentText,
                    (targetEntityIdObject === null) ? 'INVALID' : targetEntityIdObject.targetEntityId,
                    bins.value,
                    startTime,
                    startTimeDefault.checked,
                    endTime,
                    endTimeDefault.checked,
                    statisticKind.currentText)
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: sourceEntityIdLabel
            text: "Source Entity Id: "
        }
        Row {
            ComboBox {
                id: getDataDialogEntityIdModelFirst
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
                    controller.updateAvailableEntityIds(currentText, "getDataDialogEntityIdModelFirst")
                }
            }
            ComboBox {
                id: sourceEntityId
                textRole: "id"
                model: entityModelFirst
            }
        }

        Row {
            id: entityIdModelSecondRow
            Layout.columnSpan: 2
        }

        Label {
            id: binsLabel
            text: "Number of bins: "
        }
        SpinBox {
            id: bins
            minimumValue: 0
            value: 0
        }

        Label {
            text: "Start time: "
        }
        Column {
            id: startTimeValues

            Row {
                Label {
                    text: "Default inital timestamp: "
                }

                RadioButton {
                    id: startTimeDefault
                    checked: false
                    onCheckedChanged: {
                        if (checked) {
                            startTimeCalendarButton.enabled = false
                            startTimeHour.enabled = false
                            startTimeMinute.enabled = false
                            startTimeSecond.enabled = false
                            startTimeHourSeparator.color = "grey"
                            startTimeMinuteSeparator.color = "grey"

                        } else {
                            startTimeCalendarButton.enabled = true
                            startTimeHour.enabled = true
                            startTimeMinute.enabled = true
                            startTimeSecond.enabled = true
                            startTimeHourSeparator.color = "black"
                            startTimeMinuteSeparator.color = "black"
                        }
                    }
                }
            }

            Row {
                Button {
                    id: startTimeCalendarButton
                    text: startTimeDate
                    anchors.bottom: parent.bottom

                    onClicked: {
                        startTimeCalendarDialog.open()
                    }
                    enabled: true
                }
                Text {
                    text: "   "
                    font.bold: true
                }
                SpinBox {
                    id: startTimeHour
                    anchors.bottom: parent.bottom
                    value: 0
                    minimumValue: 0
                    maximumValue: 24
                    enabled: true
                }
                Text {
                    id: startTimeHourSeparator
                    text: " : "
                    anchors.bottom: parent.bottom
                    font.bold: true
                    color: "black"
                }
                SpinBox {
                    id: startTimeMinute
                    anchors.bottom: parent.bottom
                    value: 0
                    minimumValue: 0
                    maximumValue: 60
                    enabled: true
                }
                Text {
                    id: startTimeMinuteSeparator
                    text: " : "
                    anchors.bottom: parent.bottom
                    font.bold: true
                }
                SpinBox {
                    id: startTimeSecond
                    anchors.bottom: parent.bottom
                    value: 0
                    minimumValue: 0
                    maximumValue: 60
                    enabled: true
                }
            }
        }


        Label {
            text: "End time: "
        }
        Column {
            id: endTimeValues

            Row {
                Label {
                    text: "Now: "
                }

                RadioButton {
                    id: endTimeDefault
                    checked: false
                    onCheckedChanged: {
                        if (checked) {
                            endTimeCalendarButton.enabled = false
                            endTimeHour.enabled = false
                            endTimeMinute.enabled = false
                            endTimeSecond.enabled = false
                            endTimeHourSeparator.color = "grey"
                            endTimeMinuteSeparator.color = "grey"

                        } else {
                            endTimeCalendarButton.enabled = true
                            endTimeHour.enabled = true
                            endTimeMinute.enabled = true
                            endTimeSecond.enabled = true
                            endTimeHourSeparator.color = "black"
                            endTimeMinuteSeparator.color = "black"
                        }
                    }
                }
            }

            Row {
                Button {
                    id: endTimeCalendarButton
                    text: endTimeDate
                    anchors.bottom: parent.bottom
                    onClicked: {
                        endTimeCalendarDialog.open()
                    }
                }
                Text {
                    text: "   "
                    font.bold: true
                }
                SpinBox {
                    id: endTimeHour
                    anchors.bottom: parent.bottom
                    value: 0
                    minimumValue: 0
                    maximumValue: 24
                }
                Text {
                    id: endTimeHourSeparator
                    text: " : "
                    anchors.bottom: parent.bottom
                    font.bold: true
                }
                SpinBox {
                    id: endTimeMinute
                    anchors.bottom: parent.bottom
                    value: 0
                    minimumValue: 0
                    maximumValue: 60
                }
                Text {
                    id: endTimeMinuteSeparator
                    text: " : "
                    anchors.bottom: parent.bottom
                    font.bold: true
                }
                SpinBox {
                    id: endTimeSecond
                    anchors.bottom: parent.bottom
                    value: 0
                    minimumValue: 0
                    maximumValue: 60
                }
            }
        }

        Label {
            text: "Statistic kind: "
        }
        ComboBox {
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
        }
    }

    Dialog {
        id: startTimeCalendarDialog
        title: "Choose a date"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        onAccepted: {
            startTimeDate = startTimeCalendar.selectedDate.toLocaleDateString(locale, "dd.MM.yyyy");
        }

        Calendar {
            id: startTimeCalendar
            onDoubleClicked: {
                startTimeCalendarDialog.click(StandardButton.Save)
            }
        }
    }

    Dialog {
        id: endTimeCalendarDialog
        title: "Choose a date"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        onAccepted: {
            endTimeDate = endTimeCalendar.selectedDate.toLocaleDateString(locale, "dd.MM.yyyy");
        }

        Calendar {
            id: endTimeCalendar
            onDoubleClicked: {
                endTimeCalendarDialog.click(StandardButton.Save)
            }
        }
    }
}


