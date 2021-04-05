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
        console.log("Data Kind: " + dataKind + "\n" +
                    "Source Entity Id: " + sourceEntityId + "\n" +
                    "Target Entity Id: " + targetEntityId + "\n" +
                    "Bins: " + bins + "\n" +
                    "Time Start: " + startTime + "\n" +
                    "Time Start Default: " + startTimeDefault + "\n" +
                    "End Start: " + endTime + "\n" +
                    "End Start Default: " + endTimeDefault + "\n" +
                    "Statistics Kind: " + statisticKind)

        statisticsData.generateData(8)
        axisY.max = statisticsData.axisYMax;
        axisY.min = statisticsData.axisYMin;
        dateTimeAxisX.min = chartView.fromMsecsSinceEpoch(statisticsData.axisXMin);
        dateTimeAxisX.max = chartView.fromMsecsSinceEpoch(statisticsData.axisXMax);
        var series = chartView.createSeries(ChartView.SeriesTypeLine, "signal", dateTimeAxisX, axisY);
        statisticsData.update(series);
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
