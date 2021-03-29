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

    property string startTimeDate: "" + new Date().toLocaleDateString(Qt.locale(), "dd.MM.yy")
    property string endTimeDate: "" + new Date().toLocaleDateString(Qt.locale(), "dd.MM.yy")

    property var component: Qt.createComponent("AdditionalEntityId.qml")
    property var entityIdSecondObject: null

    Component.onCompleted: {
        if (label == "FASTDDS_LATENCY" |
                label == "NETWORK_LATENCY" |
                label == "RTPS_PACKETS_SENT" |
                label == "RTPS_BYTES_SENT" |
                label == "RTPS_PACKETS_LOST" |
                label == "RTPS_BYTES_LOST") {
            if (entityIdSecondObject === null) {
                entityIdSecondObject = component.createObject(entityIdModelSecondRow);
            }
        } else {
            if (entityIdSecondObject !== null) {
                entityIdSecondObject.destroy();
            }
        }
    }

    onAccepted: {
        controlPanel.addSeries();
    }

    GridLayout{

        columns: 2

        Label {
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
                textRole: "id"
                model: entityModelFirst
            }
        }

        Row {
            id: entityIdModelSecondRow
            Layout.columnSpan: 2
        }

        Label {
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
        Row {
            id: startTimeValues

            Button {
                id: startTimeCalendarButton
                text: startTimeDate
                anchors.bottom: parent.bottom
                onClicked: {
                    startTimeCalendarDialog.open()
                }
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
            }
            Text {
                text: " : "
                anchors.bottom: parent.bottom
                font.bold: true
            }
            SpinBox {
                id: startTimeMinute
                anchors.bottom: parent.bottom
                value: 0
                minimumValue: 0
                maximumValue: 60
            }
            Text {
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
            }
        }


        Label {
            text: "End time: "
        }
        Row {
            id: endTimeValues

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
            startTimeDate = startTimeCalendar.selectedDate.toLocaleDateString(Qt.locale(), "dd.MM.yy");
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
            endTimeDate = endTimeCalendar.selectedDate.toLocaleDateString(Qt.locale(), "dd.MM.yy");
        }

        Calendar {
            id: endTimeCalendar
            onDoubleClicked: {
                endTimeCalendarDialog.click(StandardButton.Save)
            }
        }
    }
}


