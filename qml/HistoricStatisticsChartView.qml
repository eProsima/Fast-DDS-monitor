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
                                     toMsecsSinceEpoch(startTime),
                                     startTimeDefault,
                                     toMsecsSinceEpoch(endTime),
                                     endTimeDefault,
                                     statisticKind))

        // Create a new QAbstractSeries with index chartView.count (this index varies with deletion of series)
        var new_series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisXItem, axisYItem);

        // See each of the points and not just the line
        new_series.pointsVisible = true
        // Stores a mapper array with every series in order to not indiscriminately destroy the C++ mapper
        mapper[mapper.length-1].series = new_series

        // Create the hover line instance. Make sure the parent is the chart instance.
        hoverItems[mapper.length-1] = {}
        var hoverLineComponent = Qt.createComponent("HoverLine.qml");
        hoverItems[mapper.length-1] = hoverLineComponent.createObject(chartView, {
            chartPlotArea: chartView.plotArea, // Pass the chart's plotArea
            chartX: chartView.plotArea.x,      // Pass X coordinate (if needed for computations)
            chartY: chartView.plotArea.y,      // Pass Y coordinate
            seriesColor: new_series.color       // Optionally specify a color
        });

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
        hoverItems = []
        mapper = []
    }

    function resetChartViewZoom(reset = true){

        if (reset) {
            historicData.recalculate_y_axis(chartboxId);
            manuallySetAxes = false
        }

        chartView.zoomReset()
        setYAxis(historicData.axisYMin(chartboxId), historicData.axisYMax(chartboxId))

        setXAxis(
            statisticsChartBox.fromMsecsSinceEpoch(historicData.axisXMin(chartboxId)),
            statisticsChartBox.fromMsecsSinceEpoch(historicData.axisXMax(chartboxId)))
    }

    function customRemoveSeries(seriesIndex){
        mapper.splice(seriesIndex, 1)
        hoverItems.splice(seriesIndex, 1)
    }
}
