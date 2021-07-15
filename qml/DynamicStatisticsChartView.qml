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

StatisticsChartView {
    id: chartView

    // There is an issue if the time that is used in the axis is the current time, as the data for current
    // time may has not arrived yet.
    // Thus, a delay_time is used in order to delay the chart regarding the actual moment.
    // For now, use delay_time to subsctract to xaxis every time this value changes
    // TODO if the backend changes and uses max time_frame as time in any point, this delay could be applied
    // to the time_to get_data call and not to the axis.
    // Meanwhile doing that would leave the chart too shifted to the left
    property int delay_time: 5000
    property int axis_refresh_time: 100

    property bool running: false

    function addDynamicSeries(
            seriesLabel,
            sourceEntityId,
            targetEntityId,
            statisticKind) {

        // Call DynamicChartBox add_series that creates a series and a related mapper and returns the mapper
        mapper.push(dynamicData.add_series(chartboxId, statisticKind, sourceEntityId, targetEntityId))
        // Create a new QAbstractSeries with index chartView.count (this index varies with deletion of series)
        var new_series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisXItem, axisYItem);

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
                        tooltipItem.x = p.x
                        tooltipItem.y = p.y - tooltipItem.height
                        tooltipItem.text = text
                        tooltipItem.seriesColor = new_series.color
                        tooltipItem.visible = true
                    })
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
        axisYMin = dynamicData.axisYMin(chartboxId)
        axisYMax = dynamicData.axisYMax(chartboxId)
        dateTimeAxisXMax = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - delay_time)
        dateTimeAxisXMin = chartView.fromMsecsSinceEpoch(toMsecsSinceEpoch(new Date()) - timeWindow - delay_time)
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
            console.log("time_to: " + time_to + " updatePeriod: " + interval)
            controller.update_dynamic_chartbox(chartboxId, time_to);
            axisYMin = dynamicData.axisYMin(chartboxId)
            axisYMax = dynamicData.axisYMax(chartboxId)
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
            dateTimeAxisXMax = chartView.fromMsecsSinceEpoch(current_date - delay_time)
            dateTimeAxisXMin = chartView.fromMsecsSinceEpoch(current_date - timeWindow - delay_time)
        }
    }
}
