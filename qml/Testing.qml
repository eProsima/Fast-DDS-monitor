//import QtQuick 2.3
//import QtQuick.Controls 1.2
//import QtQuick.Dialogs 1.2
//import QtQuick.Layouts 1.1
//import QtQuick.Window 2.0

//Item {
//    id: root
//    width: 580
//    height: 400
//    SystemPalette { id: palette }
//    clip: true

//    Dialog {
//        id: helloDialog
//        modality: dialogModal.checked ? Qt.WindowModal : Qt.NonModal
//        title: customizeTitle.checked ? windowTitleField.text : "Hello"
//        onButtonClicked: console.log("clicked button " + clickedButton)
//        onAccepted: lastChosen.text = "Accepted " +
//            (clickedButton == StandardButton.Ok ? "(OK)" : (clickedButton == StandardButton.Retry ? "(Retry)" : "(Ignore)"))
//        onRejected: lastChosen.text = "Rejected " +
//            (clickedButton == StandardButton.Close ? "(Close)" : (clickedButton == StandardButton.Abort ? "(Abort)" : "(Cancel)"))
//        onHelp: lastChosen.text = "Yelped for help!"
//        onYes: lastChosen.text = (clickedButton == StandardButton.Yes ? "Yeessss!!" : "Yes, now and always")
//        onNo: lastChosen.text = (clickedButton == StandardButton.No ? "Oh No." : "No, no, a thousand times no!")
//        onApply: lastChosen.text = "Apply"
//        onReset: lastChosen.text = "Reset"

//        Label {
//            text: "Hello world!"
//        }
//    }

//    Dialog {
//        id: spinboxDialog
//        modality: dialogModal.checked ? Qt.WindowModal : Qt.NonModal
//        title: customizeTitle.checked ? windowTitleField.text : "Spinbox"
//        onHelp: {
//            lastChosen.text = "No help available, sorry.  Please answer the question."
//            visible = true
//        }
//        onButtonClicked: {
//            if (clickedButton === StandardButton.Ok && answer.value == 11.0)
//                lastChosen.text = "You are correct!"
//            else
//                lastChosen.text = "Having failed to give the correct answer, you shall not pass!"
//        }

//        ColumnLayout {
//            id: column
//            width: parent ? parent.width : 100
//            Label {
//                text: "<b>What</b> is the average airspeed velocity of an unladen European swallow?"
//                Layout.columnSpan: 2
//                Layout.fillWidth: true
//                wrapMode: Text.WordWrap
//            }
//            RowLayout {
//                Layout.alignment: Qt.AlignHCenter
//                SpinBox {
//                    id: answer
//                    onEditingFinished: spinboxDialog.click(StandardButton.Ok)
//                }
//                Label {
//                    text: "m/s"
//                    Layout.alignment: Qt.AlignBaseline | Qt.AlignLeft
//                }
//            }
//        }
//    }

//    Dialog {
//        id: dateDialog
//        modality: dialogModal.checked ? Qt.WindowModal : Qt.NonModal
//        title: customizeTitle.checked ? windowTitleField.text : "Choose a date"
//        onButtonClicked: console.log("clicked button " + clickedButton)
//        onAccepted: {
//            if (clickedButton == StandardButton.Ok)
//                lastChosen.text = "Accepted " + calendar.selectedDate.toLocaleDateString()
//            else
//                lastChosen.text = (clickedButton == StandardButton.Retry ? "(Retry)" : "(Ignore)")
//        }
//        onRejected: lastChosen.text = "Rejected"

//        Calendar {
//            id: calendar
//            width: parent ? parent.width : implicitWidth
//            onDoubleClicked: dateDialog.click(StandardButton.Ok)
//        }
//    }

//    Dialog {
//        id: filledDialog
//        modality: dialogModal.checked ? Qt.WindowModal : Qt.NonModal
//        title: customizeTitle.checked ? windowTitleField.text : "Customized content"
//        onRejected: lastChosen.text = "Rejected"
//        onAccepted: lastChosen.text = "Accepted " +
//                    (clickedButton === StandardButton.Retry ? "(Retry)" : "(OK)")
//        onButtonClicked: if (clickedButton === StandardButton.Retry) lastChosen.text = "Retry"
//        contentItem: Rectangle {
//            color: "lightskyblue"
//            implicitWidth: 400
//            implicitHeight: 100
//            Label {
//                text: "Hello blue sky!"
//                color: "navy"
//                anchors.centerIn: parent
//            }
//            Keys.onPressed: if (event.key === Qt.Key_R && (event.modifiers & Qt.ControlModifier)) filledDialog.click(StandardButton.Retry)
//            Keys.onEnterPressed: filledDialog.accept()
//            Keys.onEscapePressed: filledDialog.reject()
//            Keys.onBackPressed: filledDialog.reject() // especially necessary on Android
//        }
//    }

//    ColumnLayout {
//        anchors.fill: parent
//        anchors.margins: 12
//        spacing: 8
//        Label {
//            font.bold: true
//            text: "Message dialog properties:"
//        }
//        CheckBox {
//            id: dialogModal
//            text: "Modal"
//            Binding on checked { value: helloDialog.modality != Qt.NonModal }
//        }
//        RowLayout {
//            CheckBox {
//                id: customizeTitle
//                text: "Window Title"
//                Layout.alignment: Qt.AlignBaseline
//                checked: true
//            }
//            TextField {
//                id: windowTitleField
//                Layout.alignment: Qt.AlignBaseline
//                Layout.fillWidth: true
//                text: "Custom Dialog"
//            }
//        }
//        Label {
//            text: "Buttons:"
//        }
//        Flow {
//            spacing: 8
//            Layout.fillWidth: true
//            property bool updating: false
//            function updateButtons(button, checked) {
//                if (updating) return
//                updating = true
//                var buttons = 0
//                for (var i = 0; i < children.length; ++i)
//                    if (children[i].checked)
//                        buttons |= children[i].button
//                if (!buttons)
//                    buttons = StandardButton.Ok
//                helloDialog.standardButtons = buttons
//                spinboxDialog.standardButtons = buttons
//                dateDialog.standardButtons = buttons
//                updating = false
//            }

//            CheckBox {
//                text: "Help"
//                property int button: StandardButton.Help
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Abort"
//                property int button: StandardButton.Abort
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Close"
//                property int button: StandardButton.Close
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Cancel"
//                property int button: StandardButton.Cancel
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "NoToAll"
//                property int button: StandardButton.NoToAll
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "No"
//                property int button: StandardButton.No
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "YesToAll"
//                property int button: StandardButton.YesToAll
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Yes"
//                property int button: StandardButton.Yes
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Ignore"
//                property int button: StandardButton.Ignore
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Retry"
//                property int button: StandardButton.Retry
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Apply"
//                property int button: StandardButton.Apply
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Reset"
//                property int button: StandardButton.Reset
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "Restore Defaults"
//                property int button: StandardButton.RestoreDefaults
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            CheckBox {
//                text: "OK"
//                checked: true
//                property int button: StandardButton.Ok
//                onCheckedChanged: parent.updateButtons(button, checked)
//            }

//            Component.onCompleted: updateButtons()
//        }
//        Label {
//            id: lastChosen
//        }
//        Item { Layout.fillHeight: true }
//    }

//    Rectangle {
//        id: bottomBar
//        anchors {
//            left: parent.left
//            right: parent.right
//            bottom: parent.bottom
//        }
//        height: buttonRow.height * 1.2
//        color: Qt.darker(palette.window, 1.1)
//        border.color: Qt.darker(palette.window, 1.3)
//        Row {
//            id: buttonRow
//            spacing: 6
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.leftMargin: 12
//            width: parent.width
//            Button {
//                text: "Hello World"
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: helloDialog.open()
//            }
//            Button {
//                text: "Input"
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: spinboxDialog.open()
//            }
//            Button {
//                text: "Date"
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: dateDialog.open()
//            }
//            Button {
//                text: "No buttons or margins"
//                anchors.verticalCenter: parent.verticalCenter
//                onClicked: filledDialog.open()
//            }
//        }
//    }
//}

import QtQuick 2.0

Item {
    id: root

// public
    function set(date) { // e.g. new Date(0, 0, 0,  0, 0)) // 12:00 AM
        var hour = date.getHours() + (!date.getHours()? 12: date.getHours() <= 12? 0: -12)//24 hour to AM/PM
        repeater.itemAt(0).positionViewAtIndex(12            * (repetitions - 1) / 2 + hour - 1,                     ListView.Center) // hour
        repeater.itemAt(1).positionViewAtIndex(60 / interval * (repetitions - 1) / 2 + date.getMinutes() / interval, ListView.Center) // minute
        repeater.itemAt(2).positionViewAtIndex(60 / interval * (repetitions - 1) / 2 + date.getSeconds() / interval, ListView.Center) // minute

        for(var column = 0; column < repeater.count; column++)  select(repeater.itemAt(column))
    }

    signal clicked(date date);  //onClicked: print('onClicked', date.toTimeString())

    property int interval: 1 // 30 20 15 10 5 2 1 minutes

// private
    width: 500;  height: 200 // default size
    clip: true

    onHeightChanged: resizeTimer.start() // resize
    Timer {id: resizeTimer;  interval: 1000;  onTriggered: set(get())} // ensure same value is selected after resize

    property int rows:        3 // number of rows on the screen     (must be odd). Also change model ''
    property int repetitions: 5 // number of times data is repeated (must be odd)

    Row {
        Repeater {
            id: repeater

            model: [ 12 * repetitions, 60 / interval * repetitions, ['', 'AM', 'PM', ''] ] // 1-12 hour, 0-59 minute, am/pm

            delegate: ListView { // hours minutes am/pm
                id: view

                property int column: index // outer index
                width: root.width / 3;  height: root.height
                snapMode: ListView.SnapToItem

                model: modelData

                delegate: Item {
                    width: root.width / 3;  height: root.height / rows

                    Text {
                        text: view.get(index)
                        font.pixelSize: Math.min(0.5 * parent.width, parent.height)
                        anchors{verticalCenter:                parent.verticalCenter
                                right:            column == 0? parent.right:            undefined
                                horizontalCenter: column == 1? parent.horizontalCenter: undefined
                                left:             column == 2? parent.left:             undefined
                                rightMargin:             0.2 * parent.width}
                        opacity: view.currentIndex == index? 1: 0.3
                    }
                }

                onMovementEnded: {select(view);  timer.restart()}
                onFlickEnded:    {select(view);  timer.restart()}
                Timer {id: timer;  interval: 1;  onTriggered: clicked(root.get())} // emit only once

                function get(index) { // returns e.g. '00' given row
                         if(column == 0)  return index % 12 + 1                            // hour
                    else if(column == 1)  return ('0' + (index * interval) % 60).slice(-2) // minute
                    else                  return model[index]                              // AM/PM
                }
            }
        }
    }

    Text { // colon
        text: ':'
        font.pixelSize: Math.min(0.5 * root.width / 3, root.height / rows)
        anchors{verticalCenter: parent.verticalCenter}
        x: root.width / 3 - width / 4
    }

    function select(view) {view.currentIndex = view.indexAt(0, view.contentY + 0.5 * view.height)} // index at vertical center

    function get() { // returns e.g. '12:00 AM'
        var hour = repeater.itemAt(0).get(repeater.itemAt(0).currentIndex)         // integer
        var am   = repeater.itemAt(2).get(repeater.itemAt(2).currentIndex) == 'AM' // boolean
        return new Date(0, 0, 0,
                        hour == 12? (am? 0: 12): (am? hour: hour + 12),            // hour
                        repeater.itemAt(1).get(repeater.itemAt(1).currentIndex))   // minute
    }

   // Component.onCompleted: set(new Date(0, 0, 0,  0, 0)) // 12:00 AM otherwise defaults to index 0 selected
}
