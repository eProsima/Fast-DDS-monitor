import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Dialog {
    id: dataKindDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    signal createChart(string dataKind)

    onAccepted: createChart(dataKindComboBox.currentText)

    RowLayout {

        Label {
            id: dataKindLabel
            text: "Data kind: "
        }
        ComboBox {
            id: dataKindComboBox
            implicitWidth: 300
            model: [
                "FASTDDS_LATENCY",
                "NETWORK_LATENCY",
                "PUBLICATION_THROUGHPUT",
                "SUBSCRIPTION_THROUGHPUT",
                "RTPS_PACKETS_SENT",
                "RTPS_BYTES_SENT",
                "RTPS_PACKETS_LOST",
                "RTPS_BYTES_LOST",
                "RESENT_DATA",
                "HEARTBEAT_COUNT",
                "ACKNACK_COUNT",
                "NACKFRAG_COUNT",
                "GAP_COUNT",
                "DATA_COUNT",
                "PDP_PACKETS",
                "EDP_PACKETS",
                "DISCOVERED_ENTITY",
                "SAMPLE_DATAS"]
        }
    }
}


