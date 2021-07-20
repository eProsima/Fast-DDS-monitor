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

    function addHistoricSeries(
            dataKind,
            seriesLabel,
            sourceEntityId,
            targetEntityId,
            bins,
            startTime,
            startTimeDefault,
            endTime,
            endTimeDefault,
            statisticKind) {

        mapper.push(
            controller.add_statistics_data(chartboxId,
                                     dataKind,
                                     sourceEntityId,
                                     targetEntityId,
                                     bins,
                                     chartView.toMsecsSinceEpoch(startTime),
                                     startTimeDefault,
                                     chartView.toMsecsSinceEpoch(endTime),
                                     endTimeDefault,
                                     statisticKind))

        // Create a new QAbstractSeries with index chartView.count (this index varies with deletion of series)
        var new_series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisXItem, axisYItem);

        // See each of the points and not just the line
        new_series.pointsVisible = true
        // Stores a mapper array with every series in order to hjavascript not indiscriminately destroy the C++ mapper
        mapper[mapper.length-1].series = new_series

        new_series.acceptedButtons = Qt.MiddleButton
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
        resetChartViewZoom(false);
    }

    function clearChart() {
        chartView.removeAllSeries();
        clearedChart()
        historicData.clear_charts(chartboxId);
        resetChartViewZoom();
        mapper = []
    }

    function resetChartViewZoom(reset = true){
        if (reset) {
            historicData.recalculate_y_axis(chartboxId);
        }

        chartView.zoomReset()
        setYAxis(historicData.axisYMin(chartboxId), historicData.axisYMax(chartboxId))

        setXAxis(
            chartView.fromMsecsSinceEpoch(historicData.axisXMin(chartboxId)),
            chartView.fromMsecsSinceEpoch(historicData.axisXMax(chartboxId)))
    }

    function customRemoveSeries(seriesIndex){
        mapper.splice(seriesIndex, 1)
    }
}
