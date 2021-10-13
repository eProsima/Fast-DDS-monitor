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

import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Theme 1.0

Dialog {
    id: dynamicDataKindDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property var availableDataKinds: []

    signal createChart(string dataKind, double timeWindowSeconds, int updatePeriod, bool cumulative)

    onAccepted: {
        if (!checkInputs())
            return

        var timeFrame = timeToMilliseconds()
        createChart(dataKindComboBox.currentText, timeFrame, (updatePeriod.value) * 1000, cumulative.checked)
    }

    Component.onCompleted: {
        availableDataKinds = controller.get_data_kinds()
    }

    onAboutToShow: {
        dataKindComboBox.currentIndex = -1
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: dataKindLabel
            text: "Data kind: "
            InfoToolTip {
                text: "Data type to be plotted."
            }
        }
        AdaptiveComboBox {
            id: dataKindComboBox
            displayText: currentIndex === -1
                         ? ("Please choose a data kind...")
                         : currentText
            model: availableDataKinds

            Component.onCompleted: currentIndex = -1
        }

        Label {
            id: timeWindow
            text: "Time window: "
            InfoToolTip {
                text: "Maximum time shown in X axis\n" +
                      "while real-time is playing"
            }
        }

        GridLayout {

            columns: 4

            RowLayout {
                TextField {
                    id: timeWindowDays
                    text: qsTr("00")
                    placeholderText: qsTr("00")
                    selectByMouse: true
                    selectionColor: Theme.eProsimaLightBlue
                    validator: IntValidator {
                        bottom: 0
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                Label {
                    text: "Days"
                }
            }
            RowLayout {
                TextField {
                    id: timeWindowHours
                    text: qsTr("00")
                    placeholderText: qsTr("00")
                    selectByMouse: true
                    selectionColor: Theme.eProsimaLightBlue
                    validator: IntValidator {
                        bottom: 0
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                Label {
                    text: "Hours"
                }
            }
            RowLayout {
                TextField {
                    id: timeWindowMinutes
                    text: qsTr("02")
                    placeholderText: qsTr("00")
                    selectByMouse: true
                    selectionColor: Theme.eProsimaLightBlue
                    validator: IntValidator {
                        bottom: 0
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                Label {
                    text: "Minutes"
                }
            }
            RowLayout {
                TextField {
                    id: timeWindowSeconds
                    text: qsTr("00")
                    placeholderText: qsTr("00")
                    selectByMouse: true
                    selectionColor: Theme.eProsimaLightBlue
                    validator: IntValidator {
                        bottom: 0
                    }
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                Label {
                    text: "Seconds"
                }
            }
        }

        Label {
            text: qsTr("Update period: ")
            InfoToolTip {
                text: "Period to update chart with\n" +
                      "new data received\n"
            }
        }
        RowLayout {
            SpinBox {
                id: updatePeriod
                editable: true
                from: 1
                value: 5
            }
            Label {
                text: "seconds"
            }
        }

        Label {
            text: qsTr("Cumulative data: ")
            InfoToolTip {
                text: "If checked, each data point is\n" +
                      "calculated using as the initial \n" +
                      "timestamp the creation time\n" +
                      "of the chart, and as the final\n" +
                      "timestamp the updated time after\n" +
                      "the update period elapsed."
            }
        }
        RowLayout {
            CheckBox {
                id: cumulative
                checked: false
            }
        }
    }

    MessageDialog {
        id: emptyTimeWindow
        title: "Empty Time Window"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The time window cannot be blank. Please set the time window duration."
        onAccepted: dynamicDataKindDialog.open()
        onDiscard: dynamicDataKindDialog.close()
    }

    MessageDialog {
        id: emptyDataKind
        title: "Empty Data Kind"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The data kind field is empty. Please choose a data type from the list."
        onAccepted: dynamicDataKindDialog.open()
        onDiscard: dynamicDataKindDialog.close()
    }

    function checkInputs() {
        if (dataKindComboBox.currentIndex === -1) {
            emptyDataKind.open()
            return false
        }

        var days = (timeWindowDays.text === "") ? 0 : parseInt(timeWindowDays.text)
        var hours = (timeWindowHours.text === "") ? 0 : parseInt(timeWindowHours.text)
        var minutes = (timeWindowMinutes.text === "") ? 0 : parseInt(timeWindowMinutes.text)
        var seconds = (timeWindowSeconds.text === "") ? 0 : parseInt(timeWindowSeconds.text)

        var timeFrame = timeToMilliseconds()
        if (timeFrame === 0) {
            emptyTimeWindow.open()
            return false
        }

        return true
    }

    function timeToMilliseconds() {
        var days = (timeWindowDays.text === "") ? 0 : parseInt(timeWindowDays.text)
        var hours = (timeWindowHours.text === "") ? 0 : parseInt(timeWindowHours.text)
        var minutes = (timeWindowMinutes.text === "") ? 0 : parseInt(timeWindowMinutes.text)
        var seconds = (timeWindowSeconds.text === "") ? 0 : parseInt(timeWindowSeconds.text)

        return (days*86400 + hours*3600 + minutes*60 + seconds)*1000
    }
}


