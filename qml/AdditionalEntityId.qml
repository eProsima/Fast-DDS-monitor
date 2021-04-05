import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

RowLayout {
    id: additionalEntityId

    property string targetEntityId

    Label {
        text: "Target Entity Id: "
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
            targetEntityId = targetEntityIdComboBox.currentText
        }
    }

    ComboBox {
        id: targetEntityIdComboBox
        textRole: "id"
        model: entityModelSecond

        Component.onCompleted: {
            targetEntityId = targetEntityIdComboBox.currentText
        }

        onActivated:  {
            targetEntityId = currentText
        }
    }


}

