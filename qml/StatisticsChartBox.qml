import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

GroupBox {
    property string chartTitle
    ColumnLayout {
        id: statisticsChartBox


        Label {
            id: statisticsChartBoxLabel
            text: chartTitle
        }

        Row {
            id: controlPanel
            spacing: 8

            signal addSeries()
            signal clearChart()

            onAddSeries: statisticsChartView.addSeries();
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
            height: 300
            width: 500
        }

        DisplayStatisticsDialog {
            id: displayStatisticsDialog
        }
    }
}
