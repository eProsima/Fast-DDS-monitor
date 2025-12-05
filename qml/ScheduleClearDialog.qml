// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
import QtQuick.Controls
import QtQuick.Layouts
import Theme 1.0

Dialog {
    id: scheduleClear
    modal: false
    title: "Scheduler Configuration"
    standardButtons: Dialog.Ok | Dialog.Help | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property bool dumpOn: false
    property string file_name: ""
    property bool deleteEntities: false
    property bool deleteData: false

    onAccepted: {
        refreshTimer.start()
    }

    onAboutToShow: {
        refreshTimer.stop()
    }

    onHelpRequested: {
        infoDialog.open()
    }

    property int iconSize: 30
    property real innerIconSize: iconSize * 4/5

    GridLayout{

        columns: 2
        rowSpacing: 20


        Label {
            text: "Save"
            InfoToolTip {
                text: "Save database to a file."
            }
        }
        CheckBox {
            id: dump
            checked: false
            indicator.width: 20
            indicator.height: 20
            onCheckedChanged: {
                if (checked) {
                    dumpOn = true

                } else {
                    dumpOn = false
                }
            }
        }

        Label {
            text: "Select path:"
            enabled: dumpOn
            InfoToolTip {
                text: "Path to save the file."
            }
        }
        RowLayout {
            Label {
                enabled: dumpOn
                text: file_name.substring(7)    // file_name without file://
            }

            Button {
                text: "Search"
                enabled: dumpOn
                onClicked: {
                    folderDialog.open()
                }
            }

            FolderDialog {
                id: folderDialog
                onAccepted: {
                    var folderPath = selectedFolder.toString()
                    file_name = folderPath + "/"
                }
            }
        }


        Label {
            text: "File name:"
            enabled: dumpOn
            InfoToolTip {
                text: "Name of the file to which\n"+
                        "the database will be\n"+
                        "dumped, in the format\n"+
                        "name_yyyy-MM-dd_hh-mm-ss.json."
            }
        }
        TextField {
            id: fileName
            enabled: dumpOn
            Layout.fillWidth: true
            text: "dump_file"
            placeholderText: "dump_file"
            selectByMouse: true
            selectionColor: Theme.eProsimaLightBlue
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
            text: "Delete entities: "
            InfoToolTip {
                text: "Remove inactive entities\n" +
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
                text: "Only keep the statistics data \n" +
                      "of this last period of time."
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
                text: "Period of time to keep."
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
                text: "Period to activate deletes."
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

    function get_timestamp() {
        return new Date().toLocaleString(Qt.locale("es_ES"), "yyyy-MM-dd_hh-mm-ss");
    }

    Timer {
        id:  refreshTimer
        interval: updatePeriodClearToMilliseconds()
        repeat: true
        onTriggered: {
            if (dumpOn) {
                var name = file_name+fileName.text+"_"+get_timestamp()+".json"
                // console.log("Selected name: " + name);
                controller.dump(
                    name,
                    false)
            }
            if (deleteEntities) {
                controller.clear_entities()
            }
            if (deleteData) {
                controller.clear_statistics_data(updatePeriodClearDataToSeconds())
            }
        }
    }

    Dialog {
        id: infoDialog
        title: "Help"
        standardButtons: Dialog.Ok
        anchors.centerIn: Overlay.overlay

        Component.onCompleted: {
            standardButton(Dialog.Ok).text = qsTrId("Got it!")
        }

        RowLayout {
            spacing: 20

            Rectangle {
                id: infoChartRect
                width: 400
                height: infoChartRectLayout.height
                color: "transparent"

                GridLayout {
                    id: infoChartRectLayout
                    width: parent.width
                    columns: 2
                    rows: 5
                    rowSpacing: 15

                    RowLayout {
                        Layout.columnSpan: 2

                        Label { text:"Create a scheduler to remove old data and/or inactive\n" +
                                        " entities at a specified interval."}
                    }

                    RowLayout {
                        Layout.columnSpan: 2

                        Rectangle {
                            Layout.fillWidth: true
                            height: 2
                            color: Theme.lightGrey
                        }
                    }

                    Label { text:"Delete entities:"; font.bold: true}
                    Label { text:"Remove inactive entities from the\n" +
                                    "database."}

                    RowLayout {
                        Layout.columnSpan: 2

                        Rectangle {
                            Layout.fillWidth: true
                            height: 2
                            color: Theme.lightGrey
                        }
                    }

                    Label { text:"Delete data:"; font.bold: true}
                    Label { text:"Delete statistics data of all the\n" +
                                    "entities."}

                    Label { text:"Time offset:"; font.bold: true}
                    Label { text:"Specific period of time to keep data."}

                    RowLayout {
                        Layout.columnSpan: 2

                        Rectangle {
                            Layout.fillWidth: true
                            height: 2
                            color: Theme.lightGrey
                        }
                    }

                    Label { text:"Delete interval:"; font.bold: true}
                    Label { text:"Specific interval between deletes."}

                }
            }
        }
    }
}
