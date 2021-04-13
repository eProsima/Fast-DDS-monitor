import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

ColumnLayout {
    id: rightPanel
    spacing: 0

    TabBar {
        id: settingsViewTabBar
        Layout.fillWidth: true

        TabButton {
            text: "QoS"
        }
        TabButton {
            text: "Statistics"
        }
        TabButton {
            text: "Issues"
        }
    }

    StackLayout {
        currentIndex: settingsViewTabBar.currentIndex
        Layout.alignment: Qt.AlignTop
        Layout.fillHeight: true

        QosView {
            id: qosView
        }

        SummaryView {
            id: summaryView
        }

        IssueView {
            id: issueView
        }
    }

    function expand_all(view, model) {
        for(var i=0; i < model.rowCount(); i++) {
            var index = model.index(i, 0)
            if (!view.isExpanded(index)) {
                view.expand(index)
            }
            if (model.rowCount(index) > 0) {
                expand_childs(view, model, index)
            }
        }
    }

    function expand_childs(view, model, parent) {
        for(var i=0; i < model.rowCount(parent); i++) {
            var index = model.index(i, 0, parent)
            if (!view.isExpanded(index)) {
                view.expand(index)
            }
            if (model.rowCount(index) > 0) {
                expand_childs(view, model, index)
            }
        }
    }
}
