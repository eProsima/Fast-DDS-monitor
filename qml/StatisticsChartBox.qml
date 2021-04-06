import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Rectangle {
    id: statisticsChartBox
    border {
        width: 2
        color: "#09487e"
    }
    width: 600
    height: 500

    property string chartTitle

    ColumnLayout {

        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 0

        Rectangle {
            id: chartBoxTitle
            width: statisticsChartBox.width
            height: statisticsChartBox.height/20
            color: "#09487e"

            Text {
                id: statisticsChartBoxLabel
                text: chartTitle
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            Layout.alignment: Qt.AlignTop | Qt.AlignCenter
            color: "#697d91"
            width: statisticsChartBox.width - (statisticsChartBox.border.width*2)
            height: statisticsChartBox.height/10

            RowLayout {
                id: controlPanel
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
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
        }


        StatisticsChartView {
            id: statisticsChartView
            Layout.fillWidth: true
            Layout.preferredHeight: statisticsChartBox.height - (3*statisticsChartBox.height/20)
            Layout.alignment: Qt.AlignTop | Qt.AlignCenter
        }

        DisplayStatisticsDialog {
            id: displayStatisticsDialog
        }
    }
}
