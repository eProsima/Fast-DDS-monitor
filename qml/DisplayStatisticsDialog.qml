import QtQml 2.15
import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.calendar 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QCC1
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12
import Controller 1.0

Dialog {
    id: displayStatisticsDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property string startTimeDate: "" + new Date().toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
    property string endTimeDate: "" + new Date().toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")

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

        controller.update_available_entity_ids("Host", "getDataDialogSourceEntityId")
    }

    onAccepted: {
        var startTime = Date.fromLocaleString(
                    Qt.locale(),
                    startTimeDate,
                    "dd.MM.yyyy HH:mm:ss")

        var endTime = Date.fromLocaleString(
                    Qt.locale(),
                    endTimeDate,
                    "dd.MM.yyyy HH:mm:ss")
        if (startTime <= endTime) {
            controlPanel.addSeries(
                        chartTitle,
                        sourceEntityId.currentText,
                        (targetEntityIdObject === null) ? '' : targetEntityIdObject.targetEntityId,
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

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: sourceEntityIdLabel
            text: "Source Entity Id: "
        }
        RowLayout {
            ComboBox {
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
                onActivated:  {
                    controller.update_available_entity_ids(currentText, "getDataDialogSourceEntityId")
                }
            }
            ComboBox {
                id: sourceEntityId
                textRole: "id"
                model: entityModelFirst
            }
        }

        RowLayout {
            id: entityIdModelSecondRow
            Layout.columnSpan: 2
        }

        Label {
            id: binsLabel
            text: "Number of bins: "
        }
        SpinBox {
            id: bins
            from: 0
            value: 0
        }

        Label {
            text: "Start time: "
        }
        ColumnLayout {
            id: startTimeValues

            RowLayout {
                Label {
                    text: "Default inital timestamp: "
                }

                CheckBox {
                    id: startTimeDefault
                    checked: false
                    indicator.width: 20
                    indicator.height: 20
                    onCheckedChanged: {
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
            var tmpDate = new Date(startTimeCalendar.selectedDate)
            tmpDate.setHours(parseInt(startTimeHour.currentItem.text),
                             parseInt(startTimeMinute.currentItem.text),
                             parseInt(startTimeSecond.currentItem.text),
                             0)
            startTimeDate = tmpDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        }

        RowLayout {
            QCC1.Calendar {
                id: startTimeCalendar
            }

            Rectangle {
                width: startTimeFrame.implicitWidth + 10
                height: startTimeFrame.implicitHeight + 10

                Component {
                    id: startTimeDelegate

                    Label {
                        text: formatText(Tumbler.tumbler.count, modelData)
                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Frame {
                    id: startTimeFrame
                    padding: 0
                    anchors.centerIn: parent

                    RowLayout {
                        Tumbler {
                            id: startTimeHour
                            model: 24
                            wrap: false
                            delegate: startTimeDelegate
                        }

                        Tumbler {
                            id: startTimeMinute
                            model: 60
                            wrap: false
                            delegate: startTimeDelegate
                        }

                        Tumbler {
                            id: startTimeSecond
                            model: 60
                            wrap: false
                            delegate: startTimeDelegate
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: endTimeCalendarDialog
        title: "Choose a date"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        onAccepted: {
            var tmpDate = new Date(endTimeCalendar.selectedDate)
            tmpDate.setHours(parseInt(endTimeHour.currentItem.text),
                             parseInt(endTimeMinute.currentItem.text),
                             parseInt(endTimeSecond.currentItem.text),
                             0)
            endTimeDate = tmpDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        }

        RowLayout {
            QCC1.Calendar {
                id: endTimeCalendar
            }

            Rectangle {
                width: endTimeFrame.implicitWidth + 10
                height: endTimeFrame.implicitHeight + 10

                Component {
                    id: endTimeDelegate

                    Label {
                        text: formatText(Tumbler.tumbler.count, modelData)
                        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Frame {
                    id: endTimeFrame
                    padding: 0
                    anchors.centerIn: parent

                    RowLayout {
                        Tumbler {
                            id: endTimeHour
                            model: 24
                            wrap: false
                            delegate: endTimeDelegate
                        }

                        Tumbler {
                            id: endTimeMinute
                            model: 60
                            wrap: false
                            delegate: endTimeDelegate
                        }

                        Tumbler {
                            id: endTimeSecond
                            model: 60
                            wrap: false
                            delegate: endTimeDelegate
                        }
                    }
                }
            }
        }
    }

    MessageDialog {
        id: wrongDatesDialog
        title: "Wrong timestamps"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The start timestamp entered is posterior to the end timestamp."
        onAccepted: {
            displayStatisticsDialog.open()
        }
    }

    function formatText(count, modelData) {
        var data = count === 24 ? modelData + 1 : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }
}


