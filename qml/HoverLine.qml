// Copyright 2025 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

Canvas {
    id: hoverLineCanvas

    property var chartPlotArea: null  // The chart's plotArea
    property real chartX: 0                // Reference X coordinate for calculations
    property real chartY: 0                // Reference Y coordinate for calculations
    property color seriesColor: "red"             // Hover line color

    property real pointX: chartX + width / 2
    property real pointY: chartY + height / 2

    width: 20
    height: chartPlotArea ? chartPlotArea.height : 100  // Fallback height in case chartPlotArea is not set
    x: pointX - width / 2
    y: chartPlotArea ? chartPlotArea.y : 0
    visible: false
    opacity: 1.0

    onPointXChanged: requestPaint()
    onPointYChanged: requestPaint()
    onSeriesColorChanged: requestPaint()
    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d");
        ctx.clearRect(0, 0, width, height);

        var centerX = width / 2;

        // Draw the dashed line at the center.
        ctx.setLineDash([4, 4]);
        ctx.strokeStyle = seriesColor;
        ctx.lineWidth = 1;
        ctx.beginPath();
        ctx.moveTo(centerX, 0);
        ctx.lineTo(centerX, height);
        ctx.stroke();

        // Draw a filled point exactly at the pointY position.
        var centerY = pointY - chartView.plotArea.y
        var radius = 5;
        ctx.beginPath();
        ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI);
        ctx.fillStyle = seriesColor;
        ctx.fill();
        ctx.stroke();
    }
}
