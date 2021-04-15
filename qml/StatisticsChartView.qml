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

ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeLight
    antialiasing: true

    ValueAxis {
        id: axisY
        min: 0
        max: 10
    }

    DateTimeAxis {
        id: dateTimeAxisX
        min: new Date()
        max: new Date()
        format: "hh:mm:ss (dd.MM)"
        labelsAngle: -45
        labelsFont: Qt.font({pointSize: 8})
    }

    function addSeries(
            dataKind,
            sourceEntityId,
            targetEntityId,
            bins,
            startTime,
            startTimeDefault,
            endTime,
            endTimeDefault,
            statisticKind) {
        controller.add_statistics_data(dataKind,
                                     sourceEntityId,
                                     targetEntityId,
                                     bins,
                                     chartView.toMsecsSinceEpoch(startTime),
                                     startTimeDefault,
                                     chartView.toMsecsSinceEpoch(endTime),
                                     endTimeDefault,
                                     statisticKind)

        if (statisticsData.axisYMax > axisY.max)
            axisY.max = statisticsData.axisYMax

        if (statisticsData.axisYMin < axisY.min)
            axisY.min = statisticsData.axisYMin

        if (chartView.fromMsecsSinceEpoch(statisticsData.axisXMax) > dateTimeAxisX.max)
            dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(statisticsData.axisXMax)

        if (chartView.fromMsecsSinceEpoch(statisticsData.axisXMin) < dateTimeAxisX.min)
            dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(statisticsData.axisXMin)

        var series = chartView.createSeries(ChartView.SeriesTypeLine, "signal", dateTimeAxisX, axisY);
        statisticsData.update(series);
    }

    function clearChart() {
        chartView.removeAllSeries();
        dateTimeAxisX.max = new Date()
        dateTimeAxisX.min = new Date()
    }

    function createAxis(min, max) {
        return Qt.createQmlObject("import QtQuick 2.0; " +
                                  "import QtCharts 2.0; " +
                                  "ValueAxis { min: " + min + "; max: " + max + " }",
                                  chartView);
    }

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }

    function fromMsecsSinceEpoch(milliseconds) {
        return new Date(milliseconds);
    }
}
