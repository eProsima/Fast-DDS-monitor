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
    }

    function addSeries() {
        dataSource.generateData(8)
        axisY.max = dataSource.axisYMax;
        axisY.min = dataSource.axisYMin;
        dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(dataSource.axisXMin);
        dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(dataSource.axisXMax);
        var series = chartView.createSeries(ChartView.SeriesTypeLine, "signal", dateTimeAxisX, axisY);
        dataSource.update(series);
    }

    function clearChart() {
        chartView.removeAllSeries();
    }

    function createAxis(min, max) {
        return Qt.createQmlObject("import QtQuick 2.0; import QtCharts 2.0; ValueAxis { min: " + min + "; max: " + max + " }", chartView);
    }

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }

    function fromMsecsSinceEpoch(milliseconds) {
        return new Date(milliseconds);
    }
}
