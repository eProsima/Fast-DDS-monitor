import QtQuick 2.0

Item {
    // public property
    property bool left_direction: false
    property bool right_direction: false
    property int left_margin: 0
    property string arrow_color: Theme.grey
    property string background_color: "white"

    // The index of corner for the triangle to be attached
    property int corner: 0

    Rectangle {
        id: background_arrow
        visible: left_margin != 0
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.topMargin: -2; anchors.bottomMargin: -2
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: left_margin; anchors.rightMargin: left_margin;
        color: background_color
    }

    Rectangle {
        id: base_arrow
        anchors.fill: parent
        color: arrow_color
    }


    Item {
        id: left_arrow
        visible: left_direction
        height: 30
        width: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.leftMargin: -parent.height /2

        Canvas {
            id: left_canvas

            anchors.centerIn: parent

            height: parent.height / 2
            width: parent.width

            antialiasing:true; smooth:true

            onPaint: {
                var ctx = left_canvas.getContext('2d')

                ctx.strokeStyle = arrow_color
                ctx.lineWidth = left_canvas.width * 0.1
                ctx.beginPath()
                ctx.moveTo(left_canvas.width, left_canvas.height * 0.05)
                ctx.lineTo(0, left_canvas.height / 2)
                ctx.lineTo(left_canvas.width, left_canvas.height * 0.95)
                ctx.stroke()
            }
        }
    }

    Item {
        id: right_arrow
        visible: right_direction
        height: 30
        width: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right; anchors.rightMargin: parent.height /2

        Canvas {
            id: right_canvas

            anchors.centerIn: parent

            height: parent.height / 2
            width: parent.width

            antialiasing:true; smooth:true

            onPaint: {
                var ctx = right_canvas.getContext('2d')

                ctx.strokeStyle = arrow_color
                ctx.lineWidth = right_canvas.width * 0.1
                ctx.beginPath()
                ctx.moveTo(0, right_canvas.height * 0.05)
                ctx.lineTo(right_canvas.width, right_canvas.height / 2)
                ctx.lineTo(0, right_canvas.height * 0.95)
                ctx.stroke()
            }
        }
    }
}
