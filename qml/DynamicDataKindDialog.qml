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

    signal createChart(string dataKind, double timeWindowSeconds, int updatePeriod)

    onAccepted: {
        var days = (timeWindowDays.text === "") ? 0 : parseInt(timeWindowDays.text)
        var hours = (timeWindowHours.text === "") ? 0 : parseInt(timeWindowHours.text)
        var minutes = (timeWindowMinutes.text === "") ? 0 : parseInt(timeWindowMinutes.text)
        var seconds = (timeWindowSeconds.text === "") ? 0 : parseInt(timeWindowSeconds.text)

        var timeFrame = (days*86400 + hours*3600 + minutes*60 + seconds)*1000
        if (timeFrame === 0){
            emptyTimeWindow.open()
        } else {
            createChart(dataKindComboBox.currentText, timeFrame, (updatePeriod.value) * 1000)
        }
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
            model: [
                "FASTDDS_LATENCY",
                "NETWORK_LATENCY",
                "PUBLICATION_THROUGHPUT",
                "SUBSCRIPTION_THROUGHPUT",
                "RTPS_PACKETS_SENT",
                "RTPS_BYTES_SENT",
                "RTPS_PACKETS_LOST",
                "RTPS_BYTES_LOST",
                "RESENT_DATA",
                "HEARTBEAT_COUNT",
                "ACKNACK_COUNT",
                "NACKFRAG_COUNT",
                "GAP_COUNT",
                "DATA_COUNT",
                "PDP_PACKETS",
                "EDP_PACKETS",
                "DISCOVERED_ENTITY",
                "SAMPLE_DATAS"]
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
    }

    MessageDialog {
        id: emptyTimeWindow
        title: "Empty Time Window"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The time window cannot be blank. Please set the time window duration."
        onAccepted: {
            dynamicDataKindDialog.open()
        }
    }
}


