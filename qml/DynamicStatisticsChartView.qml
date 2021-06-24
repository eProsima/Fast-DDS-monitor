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

    property variant mapper: []
    property int delay_time: 5000
    property int axis_refresh_time: 10

    property bool running: false
    // property int time_to: chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - delay_time)

    signal clearedChart()

    ValueAxis {
        id: axisY
        min: 0
        max: 10
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
        // dateTimeAxisX must be always delayed by a delay_time, so every time the axis is modified must be
        // substracted the delay_time
        id: dateTimeAxisX
        min: chartView.fromMsecsSinceEpoch(currentDate - timeWindow - delay_time)
        max: chartView.fromMsecsSinceEpoch(currentDate - delay_time)
        format: "hh:mm:ss (dd.MM)"
        labelsAngle: -45
        labelsFont: Qt.font({pointSize: 8})
        titleText: qsTr("Time [hh:mm:ss (dd.MM)]")
    }

    function addDynamicSeries(
            seriesLabel,
            sourceEntityId,
            targetEntityId,
            statisticKind) {

        console.log("--- chatbox id in ChartView: " + chartboxId)
        console.log("--- : currentDate: " + currentDate + " ; time window: " + timeWindow)
        console.log("--- : updatePeriod: " + currentDate + " ; time window: " + timeWindow)

        console.log("--- : starting in point: " + dateTimeAxisX.min)
        // console.log("--- : series Index: " + seriesIndex)

        // For some reason de axis is a float and must be converted to int
        mapper.push(dynamicData.add_series(chartboxId, statisticKind, sourceEntityId, targetEntityId))
        console.log("------------------------ mapper: " + mapper)
        var new_series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisX, axisY);

        new_series.pointsVisible = true
        mapper[mapper.length-1].series = new_series

        running = true

        new_series.pointAdded.connect(
                    function (index){
                        console.log("In point Added: " + index)
                    })
    }

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }

    function fromMsecsSinceEpoch(milliseconds) {
        return new Date(milliseconds);
    }

    function updateSeriesName(seriesIndex, newSeriesName) {
        series(seriesIndex).name = newSeriesName
    }

    function updateSeriesColor(seriesIndex, newSeriesColor) {
        series(seriesIndex).color = newSeriesColor
    }

    function hideSeries(seriesIndex) {
        series(seriesIndex).opacity = 0.0
    }

    function displaySeries(seriesIndex) {
        series(seriesIndex).opacity = 1.0
    }

    function clearChart() {
        console.log("clearChart in Dynamic")
        running = false
        chartView.removeAllSeries();
        clearedChart()
        dynamicData.clear_charts(chartboxId);
        resetChartViewZoom();
        mapper = []
    }

    function resetChartViewZoom(){
        console.log("resetChartViewZoom in Dynamic")
        chartView.zoomReset()
        axisY.min = dynamicData.axis_y_min(chartboxId)
        axisY.max = dynamicData.axis_y_max(chartboxId)
        dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - delay_time)
        dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - timeWindow - delay_time)
    }

    function dynamicPause(){
        running = false
    }

    function dynamicContinue(){
        running = true
    }

    Timer {
        id:  refreshTimer
        interval: updatePeriod
        running: true
        repeat: true
        onTriggered: {
            console.log("Timer -> Updating chartbox " + chartboxId)
            var time_to = Math.round(chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - delay_time))
            controller.update_dynamic_chartbox(chartboxId, time_to);
            axisY.min = dynamicData.axis_y_min(chartboxId)
            axisY.max = dynamicData.axis_y_max(chartboxId)
        }
    }

    Timer {
        id:  refreshAxisTimer
        interval: axis_refresh_time
        running: parent.running
        repeat: true
        onTriggered: {
            // update X axis
            var current_date = toMsecsSinceEpoch(new Date())
            dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(current_date - delay_time)
            dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(current_date - timeWindow - delay_time)
        }
    }
}
