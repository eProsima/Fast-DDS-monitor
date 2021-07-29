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
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QCC1
import Theme 1.0

Dialog {
    id: setAxesDialog
    title: "Set Chart Axis"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: Overlay.overlay

    property var startTimeDate: new Date()
    property var endTimeDate: new Date()
    property var yMax: 0.0
    property var yMin: 0.0

    ColumnLayout {
        spacing: 20
        GroupBox {
            label: CheckBox {
                id: checkBoxYAxis
                checked: true
                text: qsTr("Y Axis")
            }

            GridLayout {
                anchors.fill: parent
                enabled: checkBoxYAxis.checked
                columns: 2
                rows: 2
                rowSpacing: 20

                Label {
                    text: "Y Axis max: "
                }
                DoubleSpinBox {
                    id: yAxisMax
                    value: yMax * 100
                }

                Label {
                    text: "Y Axis min: "
                }
                DoubleSpinBox {
                    id: yAxisMin
                    value: yMin * 100
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 2
            color: Theme.grey
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.rightMargin: 10
        }

        GroupBox {
            label: CheckBox {
                id: checkBoxXAxis
                checked: false
                text: qsTr("X Axis")
            }

            GridLayout {
                anchors.fill: parent
                enabled: checkBoxXAxis.checked
                columns: 2
                rows: 2
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
                }
            }
        }
    }

    onAccepted: {

        if (startTimeDate >= endTimeDate) {
            wrongDatesDialog.open()
        }

        if (yAxisMin.realValue >= yAxisMax.realValue) {
            wrongYDialog.open()
        }

        modifyAxes(
            yAxisMax.realValue,
            yAxisMin.realValue,
            endTimeDate,
            startTimeDate,
            !checkBoxXAxis.checked
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
            setAxesDialog.open()
        }
    }

    MessageDialog {
        id: wrongYDialog
        title: "Wrong Y Axis values"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The min Y min value must be lower than the Y max value."
        onAccepted: {
            setAxesDialog.open()
        }
    }
}
