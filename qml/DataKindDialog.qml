import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Dialog {
    id: dataKindDialog
    modality: Qt.NonModal
    title: "Display new statistics data"

    signal createChart(string dataKind)

    onAccepted: createChart(dataKindComboBox.currentText)

        Label {
            id: dataKindLabel
            text: "Data kind: "
            anchors.left: parent.left
            anchors.bottom: dataKindComboBox.bottom
        }
        ComboBox {
            id: dataKindComboBox
            anchors.left: dataKindLabel.right
            width: 250
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


