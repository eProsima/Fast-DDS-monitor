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

import QtQuick 2.15
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
    property bool manuallySetAxes: false

    property real y_MAX_DEFAULT: controller.get_min_real()
    property real y_MIN_DEFAULT: controller.get_max_real()
    property real x_MAX_DEFAULT: controller.get_min_uint()
    property real x_MIN_DEFAULT: controller.get_max_uint()

    signal clearedChart()

    Component.onCompleted: {
        axisY.applyNiceNumbers()
        // This series is only used to print the axis
        chartView.createSeries(ChartView.SeriesTypeLine, "__initialSeries__", dateTimeAxisXItem, axisYItem);
        removeAllSeries()
        zoomReset()
    }

    ValueAxis {
        id: axisY
        min: 0
        max: 1
        tickCount: 5 // This does not work with nice numbers
        minorTickCount: 4 // Sub divisions (pretty)
        titleText: dataKind + " [" + controller.get_data_kind_units(dataKind) + "]"
    }

    DateTimeAxis {
        id: dateTimeAxisX
        min: {
            var d = new Date()
            d.setHours(d.getHours() - 1)
            return d
        }
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
                chartViewMouseArea.cursorShape = Qt.ArrowCursor
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
                    manuallySetAxes = true
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
                    manuallySetAxes = true
                }
            }
        }
    }

    SetAxesDialog {
        id: setAxesDialog
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
        if (isDynamic) running = false
    }

    function dynamicContinue(){
        if (isDynamic) running = true
    }

    function setYAxis(min, max, niceNumbers = true, force = false) {
        // If axes has been set manually and forced is not set, do not change
        if (force || !manuallySetAxes) {
            var axesLimits = checkAxes(min, max)
            axisY.min = axesLimits.min
            axisY.max = axesLimits.max
            if (niceNumbers) {
                axisY.applyNiceNumbers()
            }
        }
    }

    function setXAxis(min, max, force = false) {
        // If axes has been set manually and forced is not set, do not change
        if (force || !manuallySetAxes) {
            var axesLimits = checkAxes(min, max)
            dateTimeAxisX.min = axesLimits.min
            dateTimeAxisX.max = axesLimits.max
        }
    }

    function checkAxes(min, max) {
        var axisMin, axisMax
        if (min == y_MIN_DEFAULT || min == y_MAX_DEFAULT)
        {
            axisMin = 0
        }
        else
        {
            axisMin = min
        }
        if (max == y_MIN_DEFAULT || max == y_MAX_DEFAULT)
        {
            axisMax = 1
        }
        else
        {
            axisMax = max
        }
        if (axisMin == axisMax)
        {
            axisMin = min - 1
            axisMax = max + 1
        }
        else if (axisMin > axisMax)
        {
            axisMin = max
            axisMax = min
        }
        return  {
            min: axisMin,
            max: axisMax
        }
    }

    function xLabel() {
        return axisY.titleText
    }

    function userSetAxes() {
        // Set actual axes
        setAxesDialog.startTimeDate = dateTimeAxisX.min
        setAxesDialog.endTimeDate = dateTimeAxisX.max
        setAxesDialog.yMax = axisY.max
        setAxesDialog.yMin = axisY.min

        setAxesDialog.open()
    }

    function modifyAxes(yMax, yMin, xMax, xMin, keepRunning) {
        // No values set for the X-axis means that the preset values are maintained, whether it was running or not.
        // Otherwise, if values are set for the X-axis, the dynamic chart stops setting those timestamps as the maximum
        // and minimum time values.
        if (!keepRunning) dynamicPause();
        manuallySetAxes = true
        setYAxis(yMin, yMax, false, true)
        setXAxis(xMin, xMax, true)
    }

    // Virtual functions that require implementation for Historic and Dynamic child classes:
    // - add_Series
    // - clearChart
    // - resetChartViewZoom (must set manuallySetAxes to false)
}
