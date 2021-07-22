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
    id: userResizeAxes
    title: "Rename Chart Box"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: Overlay.overlay

    property var startTimeDate: new Date()
    property var endTimeDate: new Date()
    property var yMax: 0.0
    property var yMin: 0.0

    GridLayout {
        id: axisGrid
        columns: 2
        rows: 4
        rowSpacing: 20

        Label {
            text: "X Axis max: "
        }
        Button {
            id: endTimeCalendarButton
            text: endTimeDate
            onClicked: {
                endTimeCalendarDialog.open()
            }
            enabled: true
        }
        Label {
            text: "Y Axis max: "
        }
        DoubleSpinBox {
            id: yAxisMax
            value: yMax * 100
        }

        Label {
            text: "X Axis min: "
        }
        Button {
            id: startTimeCalendarButton
            text: startTimeDate
            onClicked: {
                startTimeCalendarDialog.open()
            }
            enabled: true
        }
        Label {
            text: "Y Axis min: "
        }
        DoubleSpinBox {
            id: yAxisMin
            value: yMin * 100
        }
    }

    onAccepted: {

        if (startTimeDate >= endTimeDate) {
            wrongDatesDialog.open()
        }

        if (yAxisMin.realValue >= yAxisMax.realValue) {
            wrongYDialog.open()
        }
        // startTimeDate = startTimeDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")
        // endTimeDate = endTimeDate.toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")

        modifyAxes(
            yAxisMax.realValue,
            yAxisMin.realValue,
            endTimeDate,
            startTimeDate
        )
    }

    Dialog {
        id: startTimeCalendarDialog
        title: "Choose the start timestamp"
        standardButtons: StandardButton.Save | StandardButton.Cancel

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            var tmpDate = new Date(startTimeCalendar.selectedDate)
            var timeDate = Date.fromLocaleTimeString(Qt.locale(), startTime.text, "HH:mm:ss")
            tmpDate.setHours(timeDate.getHours(),
                            timeDate.getMinutes(),
                            timeDate.getSeconds(),
                            0)
            startTimeDate = tmpDate
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
            var tmpDate = new Date(endTimeCalendar.selectedDate)
            var timeDate = Date.fromLocaleTimeString(Qt.locale(), endTime.text, "HH:mm:ss")
            tmpDate.setHours(timeDate.getHours(),
                            timeDate.getMinutes(),
                            timeDate.getSeconds(),
                            0)
            endTimeDate = tmpDate
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
            userResizeAxes.open()
        }
    }

    MessageDialog {
        id: wrongYDialog
        title: "Wrong Y Axis values"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The min Y min value must be lower than the Y max value."
        onAccepted: {
            userResizeAxes.open()
        }
    }
}