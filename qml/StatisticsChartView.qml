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
import Theme 1.0

ChartView {
    id: sharedChartView
    animationOptions: ChartView.NoAnimation // Some animations misalign the Timer period (NPI)
    theme: ChartView.ChartThemeLight
    antialiasing: true
    legend.visible: false

    margins.bottom: 0
    margins.left: 0
    margins.right: 10
    margins.top: 0

    property var mapper: []
    property var axisYItem: axisY
    property var dateTimeAxisXItem: dateTimeAxisX
    property var tooltipItem: tooltip
    property var chartViewMouseAreaItem: chartViewMouseArea

    signal clearedChart()

    Component.onCompleted: {
        axisY.applyNiceNumbers()
    }

    ValueAxis {
        id: axisY
        min: 0
        max: 1
        titleText: dataKind + "[" + controller.get_data_kind_units(dataKind) + "]"
    }

    DateTimeAxis {
        id: dateTimeAxisX
        min: new Date()
        max: new Date()
        format: "hh:mm:ss"
        labelsFont: Qt.font({pointSize: 8})
        titleText: qsTr("Time [hh:mm:ss]")
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

    Rectangle {
        id: zoomRect
        color: "transparent"
        border.color: Theme.eProsimaLightBlue
        border.width: 2
        visible: false
        Rectangle {
            id: innerZoomRect
            anchors.fill: parent
            color: Theme.eProsimaLightBlue
            visible: parent.visible
            opacity: 0.1
        }
    }

    FocusScope {
        id: focusScope
        anchors.fill: parent

        MouseArea {
            id: chartViewMouseArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons

            property bool pressedZoom: false
            property bool pressedDrag: false

            focus: true

            Keys.onPressed: {
                if (chartViewMouseArea.containsMouse) {
                    if (event.key === Qt.Key_Control) {
                        chartViewMouseArea.cursorShape = Qt.OpenHandCursor
                    } else if (event.key === Qt.Key_Shift) {
                        chartViewMouseArea.cursorShape = Qt.CrossCursor
                    } else {
                        chartViewMouseArea.cursorShape = Qt.PointingHandCursor
                    }
                } else {
                    chartViewMouseArea.cursorShape = Qt.ArrowCursor
                }
                event.accepted = true;
            }

            Keys.onReleased: {
                if (chartViewMouseArea.containsMouse) {
                    chartViewMouseArea.cursorShape = Qt.PointingHandCursor
                } else {
                    chartViewMouseArea.cursorShape = Qt.ArrowCursor
                }
                event.accepted = true;
            }

            onEntered: {
                chartViewMouseArea.cursorShape = Qt.PointingHandCursor
                focusScope.forceActiveFocus()
            }

            onExited: {
                chartViewMouseAreaItem.cursorShape = Qt.ArrowCursor
            }

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
                if (pressedZoom) {
                    chartView.zoomIn(Qt.rect(zoomRect.x, zoomRect.y, zoomRect.width, zoomRect.height))
                    zoomRect.visible = false
                    pressedZoom = false
                } else if (pressedDrag) {
                    pressedDrag = false
                } else {
                    mouse.accepted = false
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

    function dynamicPause(){
        running = false
    }

    function dynamicContinue(){
        running = true
    }

    function setYAxis(min, max) {
        axisY.min = min
        axisY.max = max
        axisY.applyNiceNumbers()
    }

    function setXAxis(min, max) {
        dateTimeAxisX.min = min
        dateTimeAxisX.max = max
    }

    function xLabel() {
        return axisY.titleText
    }

    // Virtual functions that require implementation for Historic and Dynamic child classes:
    // - add_Series
    // - clearChart
    // - resetChartViewZoom
}
