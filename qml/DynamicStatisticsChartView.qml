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
    animationOptions: ChartView.SeriesAnimations
    theme: ChartView.ChartThemeLight
    antialiasing: true
    legend.visible: false

    property variant mapper: []

    // There is an issue if the time that is used in the axis is the current time, as the data for current
    // time may has not arrived yet.
    // Thus, a delay_time is used in order to delay the chart regarding the actual moment.
    // For now, use delay_time to subsctract to xaxis every time this value changes
    // TODO if the backend changes and uses max time_frame as time in any point, this delay could be applied
    // to the time_to get_data call and not to the axis.
    // Meanwhile doing that would leave the chart too shifted to the left
    property int delay_time: 5000
    property int axis_refresh_time: 100
    property real y_axis_current_min: 0
    property real y_axis_current_max: 10

    property bool running: false

    signal clearedChart()

    ValueAxis {
        id: axisY
        min: y_axis_current_min
        max: y_axis_current_max
        titleText: {
            switch (dataKind) {
                case "FASTDDS_LATENCY":
                    return qsTr(dataKind + " [ns]")
                case "NETWORK_LATENCY":
                    return qsTr(dataKind + " [ns]")
                case "PUBLICATION_THROUGHPUT":
                    return qsTr(dataKind + " [B/s]")
                case "SUBSCRIPTION_THROUGHPUT":
                    return qsTr(dataKind + " [B/s]")
                case "RTPS_PACKETS_SENT":
                    return qsTr(dataKind + " [count]")
                case "RTPS_BYTES_SENT":
                    return qsTr(dataKind + " [B]")
                case "RTPS_PACKETS_LOST":
                    return qsTr(dataKind + " [count]")
                case "RTPS_BYTES_LOST":
                    return qsTr(dataKind + " [B]")
                case "RESENT_DATA":
                    return qsTr(dataKind + " [count]")
                case "HEARTBEAT_COUNT":
                    return qsTr(dataKind + " [count]")
                case "ACKNACK_COUNT":
                    return qsTr(dataKind + " [count]")
                case "NACKFRAG_COUNT":
                    return qsTr(dataKind + " [count]")
                case "GAP_COUNT":
                    return qsTr(dataKind + " [count]")
                case "DATA_COUNT":
                    return qsTr(dataKind + " [count]")
                case "PDP_PACKETS":
                    return qsTr(dataKind + " [count]")
                case "EDP_PACKETS":
                    return qsTr(dataKind + " [count]")
                case "DISCOVERED_ENTITY":
                    return qsTr(dataKind + " [ns]")
                case "SAMPLE_DATAS":
                    return qsTr(dataKind + " [count]")
                default:
                    return qsTr("")
            }
        }
    }

    DateTimeAxis {
        // dateTimeAxisX must be always delayed by a delay_time
        // Thus every time the axis is modified must be substracted the delay_time
        id: dateTimeAxisX
        min: chartView.fromMsecsSinceEpoch(currentDate - timeWindow - delay_time)
        max: chartView.fromMsecsSinceEpoch(currentDate - delay_time)
        format: "hh:mm:ss (dd.MM)"
        labelsAngle: -45
        labelsFont: Qt.font({pointSize: 8})
        titleText: qsTr("Time [hh:mm:ss (dd.MM)]")
    }

    ToolTip {
        id: tooltip

        property string seriesColor: "black"

        contentItem: Text{
            color: tooltip.seriesColor
            text: tooltip.text
        }
        background: Rectangle {
            border.color: tooltip.seriesColor
        }
    }

    Rectangle {
        id: horizontalScrollMask
        visible: false
    }

    Rectangle {
        id: verticalScrollMask
        visible: false
    }

    Rectangle{
        id: zoomRect
        color: "black"
        opacity: 0.6
        visible: false
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.AllButtons

        property bool pressedZoom: false
        property bool pressedDrag: false

        onPressed: {
            if (!((mouse.modifiers & Qt.ShiftModifier) || (mouse.modifiers & Qt.ControlModifier))) {
                mouse.accepted = false
            } else {
                if (mouse.modifiers & Qt.ShiftModifier){
                    zoomRect.x = mouseX
                    zoomRect.y = mouseY
                    zoomRect.visible = true
                    pressedZoom = true
                } else if (mouse.modifiers & Qt.ControlModifier) {
                    verticalScrollMask.y = mouseY;
                    horizontalScrollMask.x = mouseX;
                    pressedDrag = true;
                }
            }
        }
        onMouseXChanged: {
            if ((mouse.modifiers & Qt.ShiftModifier) || (mouse.modifiers & Qt.ControlModifier)){
                if (pressedZoom){
                    zoomRect.width = mouseX - zoomRect.x
                } else if (pressedDrag){
                    chartView.scrollLeft(mouseX - horizontalScrollMask.x);
                    horizontalScrollMask.x = mouseX;
                }
            }
        }
        onMouseYChanged: {
            if ((mouse.modifiers & Qt.ShiftModifier) || (mouse.modifiers & Qt.ControlModifier)){
                if (pressedZoom){
                    zoomRect.height = mouseY - zoomRect.y
                } else if (pressedDrag){
                    chartView.scrollUp(mouseY - verticalScrollMask.y);
                    verticalScrollMask.y = mouseY;
                }
            }
        }
        onReleased: {
            if (!((mouse.modifiers & Qt.ShiftModifier) || (mouse.modifiers & Qt.ControlModifier))) {
                mouse.accepted = false
            } else {
                if (pressedZoom) {
                    chartView.zoomIn(Qt.rect(zoomRect.x, zoomRect.y, zoomRect.width, zoomRect.height))
                    zoomRect.visible = false
                    pressedZoom = false
                } else if (pressedDrag) {
                    pressedDrag = false
                }
            }
        }
        onWheel: {
            if(!(wheel.modifiers & Qt.ControlModifier)) {
                wheel.accepted = false
            } else {
                if (wheel.angleDelta.y > 0) {
                    chartView.zoomIn()
                } else {
                    chartView.zoomOut()
                }
            }
        }
    }

    function addDynamicSeries(
            seriesLabel,
            sourceEntityId,
            targetEntityId,
            statisticKind) {

        // Call DynamicChartBox add_series that creates a series and a related mapper and returns the mapper
        mapper.push(dynamicData.add_series(chartboxId, statisticKind, sourceEntityId, targetEntityId))
        // Create a new QAbstractSeries with index chartView.count (this index varies with deletion of series)
        var new_series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisX, axisY);

        // See each of the points and not just the line
        new_series.pointsVisible = true
        // Stores a mapper array with every series in order to hjavascript not indiscriminately destroy the C++ mapper
        mapper[mapper.length-1].series = new_series

        // Set timer that moves the axis to running
        running = true

        // Connect to see points when passing with the mouse through the chart
        new_series.clicked.connect(
                    function (point){
                        var p = chartView.mapToPosition(point)
                        var text = qsTr("x: %1 \ny: %2").arg(
                                    new Date(point.x).toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")).arg(point.y)
                        tooltip.x = p.x
                        tooltip.y = p.y - tooltip.height
                        tooltip.text = text
                        tooltip.seriesColor = new_series.color
                        tooltip.visible = true
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
        running = false
        chartView.removeAllSeries();
        clearedChart()
        dynamicData.clear_charts(chartboxId);
        resetChartViewZoom();
        mapper = []
    }

    function resetChartViewZoom(){
        chartView.zoomReset()
        axisY.min = dynamicData.axisYMin(chartboxId)
        axisY.max = dynamicData.axisYMax(chartboxId)
        dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - delay_time)
        dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - timeWindow - delay_time)
    }

    function dynamicPause(){
        running = false
    }

    function dynamicContinue(){
        running = true
    }

    function customRemoveSeries(seriesIndex){
        mapper.splice(seriesIndex, 1)
        if (mapper.length == 0){
            running = false
        }
    }

    function xLabel() {
        return axisY.titleText
    }

    // This timer calls update_dynamic_chartbox so it calls get_data and update the series with new data from backend
    // It runs constantly so the timer in the DynamicChartBox(C++) is updated constantly.
    // If not extra logic will be needed or the first point will be an accumulation from the begin of the chartbox
    // till the current moment
    Timer {
        id:  refreshTimer
        interval: updatePeriod
        running: true
        repeat: true
        onTriggered: {
            var time_to = Math.round(chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - delay_time))
            controller.update_dynamic_chartbox(chartboxId, time_to);
            y_axis_current_min = dynamicData.axisYMin(chartboxId)
            y_axis_current_max = dynamicData.axisYMax(chartboxId)
        }
    }

    // This timer refresh the X axis and Y axis in case it has changed by new data in refreshTimer
    // It starts pressing Continue/Play(Button) or creating a series
    // It stops pressing pause/Pause(Button) or clearing chartbox (not erasing all series)
    Timer {
        id:  refreshAxisTimer
        interval: axis_refresh_time
        running: parent.running
        repeat: true
        onTriggered: {
            // update X by current time
            var current_date = toMsecsSinceEpoch(new Date())
            dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(current_date - delay_time)
            dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(current_date - timeWindow - delay_time)
            // update y axis in case it has changed in timer refreshTimer
            // axisY.min = y_axis_current_min
            // axisY.max = y_axis_current_max
        }
    }
}
