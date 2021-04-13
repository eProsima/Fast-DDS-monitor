import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

SplitView {
    id: panels
    anchors.fill: parent

    LeftPanel {
        id: leftPanel
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6
    }

    ChartsLayout {
        id: chartsLayout
        SplitView.fillWidth: true
    }

    RightPanel {
        id: rightPanel
        SplitView.preferredWidth: parent.width / 6
        SplitView.minimumWidth: parent.width / 6
    }

    function createChart(dataKind){
        chartsLayout.createChart(dataKind)
    }
}

