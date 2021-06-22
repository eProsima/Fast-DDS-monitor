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

    function addDynamicSeries(
            dataKind,
            seriesLabel,
            sourceEntityId,
            targetEntityId,
            statisticKind,
            timeWindow,
            updatePeriod) {

        // TODO
        resetChartViewZoom();
    }

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }

    function fromMsecsSinceEpoch(milliseconds) {
        return new Date(milliseconds);
    }
}
