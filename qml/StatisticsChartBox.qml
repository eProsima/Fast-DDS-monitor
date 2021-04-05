import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Rectangle {
    id: statisticsChartBox
    width: 600
    height: 500

    property string chartTitle

    ColumnLayout {

        Label {
            id: statisticsChartBoxLabel
            text: chartTitle
        }

        RowLayout {
            id: controlPanel
            spacing: 8

            signal addSeries(
                string dataKind,
                string sourceEntityId,
                string targetEntityId,
                int bins,
                date startTime,
                bool startTimeDefault,
                date endTime,
                bool endTimeDefault,
                string statisticKind)
            signal clearChart()

            onAddSeries: statisticsChartView.addSeries(
                             dataKind,
                             sourceEntityId,
                             targetEntityId,
                             bins,
                             startTime,
                             startTimeDefault,
                             endTime,
                             endTimeDefault,
                             statisticKind);
            onClearChart: statisticsChartView.clearChart();

            Button {
                text: "Add series"
                onClicked: {
                    displayStatisticsDialog.open();
                }
            }

            Button {
                text: "Clear chart"
                onClicked: controlPanel.clearChart();
            }

            Button {
                text: "Remove chart"
                onClicked: {
                    statisticsChartBox.destroy()
                }
            }
        }

        StatisticsChartView {
            id: statisticsChartView
            Layout.preferredWidth: 500
            Layout.preferredHeight: 300
        }

        DisplayStatisticsDialog {
            id: displayStatisticsDialog
        }
    }
}
