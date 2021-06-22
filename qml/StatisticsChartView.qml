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

    property string chartTitle: ""
    property bool isDynamic: false

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
        min: dateTimeAxisXMin
        max: dateTimeAxisXMax
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

    function addSeries(
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
        controller.add_statistics_data(dataKind,
                                     sourceEntityId,
                                     targetEntityId,
                                     bins,
                                     chartView.toMsecsSinceEpoch(startTime),
                                     startTimeDefault,
                                     chartView.toMsecsSinceEpoch(endTime),
                                     endTimeDefault,
                                     statisticKind)

        if (statisticsData.axisYMax > axisYMax)
            axisYMax = statisticsData.axisYMax

        if (statisticsData.axisYMin < axisYMin)
            axisYMin = statisticsData.axisYMin

        if (chartView.fromMsecsSinceEpoch(statisticsData.axisXMax) > dateTimeAxisXMax)
            dateTimeAxisXMax = chartView.fromMsecsSinceEpoch(statisticsData.axisXMax)

        if (chartView.fromMsecsSinceEpoch(statisticsData.axisXMin) < dateTimeAxisXMin)
            dateTimeAxisXMin = chartView.fromMsecsSinceEpoch(statisticsData.axisXMin)

        var series = chartView.createSeries(ChartView.SeriesTypeLine, seriesLabel, dateTimeAxisX, axisY);
        series.pointsVisible = true
        series.acceptedButtons = Qt.MiddleButton
        series.clicked.connect(
                    function (point){
                        var p = chartView.mapToPosition(point)
                        var text = qsTr("x: %1 \ny: %2").arg(
                                    new Date(point.x).toLocaleString(Qt.locale(), "dd.MM.yyyy HH:mm:ss")).arg(point.y)
                        tooltip.x = p.x
                        tooltip.y = p.y - tooltip.height
                        tooltip.text = text
                        tooltip.seriesColor = series.color
                        tooltip.visible = true
                    })
        statisticsData.update(series);
        resetChartViewZoom();
    }

    function clearChart() {
        chartView.removeAllSeries();
        axisYMin = 0
        axisYMax = 10
        dateTimeAxisXMax = new Date()
        dateTimeAxisXMin = new Date()
        resetChartViewZoom();
    }

    function resetChartViewZoom(){
        chartView.zoomReset()
        axisY.min = axisYMin
        axisY.max = axisYMax
        dateTimeAxisX.min = dateTimeAxisXMin
        dateTimeAxisX.max = dateTimeAxisXMax
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
}
