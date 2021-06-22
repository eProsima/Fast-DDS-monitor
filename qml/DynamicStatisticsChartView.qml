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
import QtCharts 2.1
import QtQuick.Controls 2.15

ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeLight
    antialiasing: true
    legend.visible: false

    property int axisYMin: 0
    property int axisYMax: 10
    property date dateTimeAxisXMin: new Date()
    property date dateTimeAxisXMax: new Date()

    ValueAxis {
        id: axisY
        min: axisYMin
        max: axisYMax
        titleText: {
            switch (chartTitle) {
                case "FASTDDS_LATENCY":
                    return qsTr(chartTitle + " [ns]")
                case "NETWORK_LATENCY":
                    return qsTr(chartTitle + " [ns]")
                case "PUBLICATION_THROUGHPUT":
                    return qsTr(chartTitle + " [B/s]")
                case "SUBSCRIPTION_THROUGHPUT":
                    return qsTr(chartTitle + " [B/s]")
                case "RTPS_PACKETS_SENT":
                    return qsTr(chartTitle + " [count]")
                case "RTPS_BYTES_SENT":
                    return qsTr(chartTitle + " [B]")
                case "RTPS_PACKETS_LOST":
                    return qsTr(chartTitle + " [count]")
                case "RTPS_BYTES_LOST":
                    return qsTr(chartTitle + " [B]")
                case "RESENT_DATA":
                    return qsTr(chartTitle + " [count]")
                case "HEARTBEAT_COUNT":
                    return qsTr(chartTitle + " [count]")
                case "ACKNACK_COUNT":
                    return qsTr(chartTitle + " [count]")
                case "NACKFRAG_COUNT":
                    return qsTr(chartTitle + " [count]")
                case "GAP_COUNT":
                    return qsTr(chartTitle + " [count]")
                case "DATA_COUNT":
                    return qsTr(chartTitle + " [count]")
                case "PDP_PACKETS":
                    return qsTr(chartTitle + " [count]")
                case "EDP_PACKETS":
                    return qsTr(chartTitle + " [count]")
                case "DISCOVERED_ENTITY":
                    return qsTr(chartTitle + " [ns]")
                case "SAMPLE_DATAS":
                    return qsTr(chartTitle + " [count]")
                default:
                    return qsTr("")
            }
        }
    }

    DateTimeAxis {
        id: dateTimeAxisX
        min: chartView.fromMsecsSinceEpoch(currentDate - timeWindow)
        max: chartView.fromMsecsSinceEpoch(currentDate)
        format: "hh:mm:ss (dd.MM)"
        labelsAngle: -45
        labelsFont: Qt.font({pointSize: 8})
        titleText: qsTr("Time [hh:mm:ss (dd.MM)]")
    }

    function addDynamicSeries(
            dataKindx,
            seriesLabel,
            sourceEntityId,
            targetEntityId,
            statisticKind,
            timeWindowx,
            updatePeriodx,
            currentDatex) {

        console.log("--- chatbox id in ChartView: " + chartboxId)
        console.log("--- : currentDate: " + currentDate + " ; time window: " + timeWindow)
        console.log("--- : updatePeriod: " + currentDate + " ; time window: " + timeWindow)

        console.log("--- : starting in point: " + dateTimeAxisX.min)

        var mapper = dynamicData.add_series(chartboxId, statisticKind, sourceEntityId, targetEntityId, dateTimeAxisX.max)
        console.log("------------------------ mapper: " + mapper)
        var new_series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisX, axisY);

        mapper.series = new_series

        refreshTimer.running = true

        // TODO
        // resetChartViewZoom();
    }

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }

    function fromMsecsSinceEpoch(milliseconds) {
        return new Date(milliseconds);
    }

    Timer {
        id:  refreshTimer
        interval: updatePeriod
        running: false
        repeat: true
        onTriggered: {
            controller.update_dynamic_chartbox(chartboxId, dateTimeAxisX.max);
        }
    }

    Timer {
        id:  refreshxTimer
        interval: 10
        running: true
        repeat: true
        onTriggered: {
            // update X axis
            dateTimeAxisX.max = new Date()
            dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - timeWindow)
        }
    }
}
