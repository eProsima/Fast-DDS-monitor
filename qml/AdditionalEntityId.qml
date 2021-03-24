import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

RowLayout {

    Label {
        text: "Destination Entity Id: "
    }

    ComboBox {
        id: getDataDialogEntityIdModelSecond
        model: [
            "Host",
            "User",
            "Process",
            "Domain",
            "Topic",
            "DomainParticipant",
            "DataWriter",
            "DataReader",
            "Locator"]
        onActivated:  {
            controller.updateAvailableEntityIds(currentText, "getDataDialogEntityIdModelSecond")
        }
    }

    ComboBox {
        textRole: "id"
        model: entityModelSecond
    }


}

