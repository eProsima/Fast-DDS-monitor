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
    id: scheduleClear
    modal: false
    title: "Remove old data"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property bool deleteEntities: false
    property bool deleteData: false

    onAccepted: {
        refreshTimer.start()
    }

    onAboutToShow: {
        refreshTimer.stop()
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            text: "Delete entities: "
            InfoToolTip {
                text: "Remove all the inactive entities\n" +
                      "from the database."
            }
        }
        CheckBox {
            id: entities
            checked: false
            indicator.width: 20
            indicator.height: 20
            onCheckedChanged: {
                if (checked) {
                    deleteEntities = true

                } else {
                    deleteEntities = false
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
        }

        Label {
            text: "Delete data: "
            InfoToolTip {
                text: "Clear the statistics data \n" +
                      "of all the entities."
            }
        }
        CheckBox {
            id: dataCheck
            checked: false
            indicator.width: 20
            indicator.height: 20
            onCheckedChanged: {
                if (checked) {
                    deleteData = true

                } else {
                    deleteData = false
                }
            }
        }
        Label {
            text: "Time offset: "
            enabled: deleteData
            InfoToolTip {
                text: "Time offset from current \n" +
                      "time from which to delete \n" +
                      "old data. "
            }
        }
        GridLayout {
            id: updatePeriodClearData
            enabled: deleteData
            columns: 3

            RowLayout {
                TextField {
                    id: updatePeriodClearDataHours
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
                    id: updatePeriodClearDataMinutes
                    text: qsTr("05")
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
                    id: updatePeriodClearDataSeconds
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

        RowLayout {
            Layout.columnSpan: 2

            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: Theme.lightGrey
            }
        }

        Label {
            text: qsTr("Delete interval: ")
            InfoToolTip {
                text: "Interval between deletes. "
            }
        }
        GridLayout {
            id: updatePeriodClear
            columns: 3

            RowLayout {
                TextField {
                    id: updatePeriodClearHours
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
                    id: updatePeriodClearMinutes
                    text: qsTr("05")
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
                    id: updatePeriodClearSeconds
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
    }

    function updatePeriodClearToMilliseconds() {
        var hours = (updatePeriodClearHours.text === "") ? 0 : parseInt(updatePeriodClearHours.text)
        var minutes = (updatePeriodClearMinutes.text === "") ? 0 : parseInt(updatePeriodClearMinutes.text)
        var seconds = (updatePeriodClearSeconds.text === "") ? 0 : parseInt(updatePeriodClearSeconds.text)

        return ((hours*3600 + minutes*60 + seconds)*1000)
    }

    function updatePeriodClearDataToSeconds() {
        var hours = (updatePeriodClearDataHours.text === "") ? 0 : parseInt(updatePeriodClearDataHours.text)
        var minutes = (updatePeriodClearDataMinutes.text === "") ? 0 : parseInt(updatePeriodClearDataMinutes.text)
        var seconds = (updatePeriodClearDataSeconds.text === "") ? 0 : parseInt(updatePeriodClearDataSeconds.text)

        return (hours*3600 + minutes*60 + seconds)
    }

    Timer {
        id:  refreshTimer
        interval: updatePeriodClearToMilliseconds()
        running: false
        repeat: true
        onTriggered: {
            if (deleteEntities) {
                controller.clear_entities()
            }
            if (deleteData) {
                controller.clear_statistics_data(updatePeriodClearDataToSeconds())
            }
        }
    }

}
