import QtQuick 2.0

Item {
    // public property
    property bool left_direction: false             // defines if the represented connection must draw a left arrow
    property bool right_direction: false            // defines if the represented connection must draw a right arrow
    property int left_margin: 0                     // left margin to be applied
    property string arrow_color: Theme.grey         // connection color
    property string background_color: "white"       // background color

    // readonly private design properties
    readonly property int arrow_margin_: -4         // margins for background
    readonly property int arrow_size_: 30           // arrow size

    // background to make connection overlap nicely with previous topics (looks like connection goes OVER the topic)
    Rectangle {
        id: background_arrow
        visible: left_margin != 0
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.topMargin: arrow_margin_; anchors.bottomMargin: arrow_margin_
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: left_margin; anchors.rightMargin: left_margin;
        color: background_color
    }

    Rectangle {
        id: left_background
        opacity: 0.70
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.topMargin: -2; anchors.bottomMargin: -2
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: parent.height /2; anchors.rightMargin: 5;
        color: background_color
    }



    // left arrow if visible
    Item {
        id: left_arrow_background
        visible: left_direction
        height: arrow_size_ + 8
        width: arrow_size_ + 2
        opacity: 0.7
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left

        Canvas {
            id: left_canvas_background

            anchors.centerIn: parent

            height: parent.height / 2
            width: parent.width

            antialiasing:true; smooth:true

            onPaint: {
                var ctx = left_canvas_background.getContext('2d')

                ctx.strokeStyle = "white"
                ctx.lineWidth = left_canvas_background.width * 0.1
                ctx.beginPath()
                ctx.moveTo(left_canvas_background.width, left_canvas_background.height * 0.001)
                ctx.lineTo(12, left_canvas_background.height / 2 - 6)
                ctx.lineTo(12, left_canvas_background.height / 2 + 6)
                ctx.lineTo(left_canvas_background.width, left_canvas_background.height * 0.999)
                ctx.stroke()
            }
        }
    }


    Item {
        id: left_arrow
        visible: left_direction
        height: arrow_size_
        width: arrow_size_
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left

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

    // main connection
    Rectangle {
        id: base_arrow
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: left_direction ? 8 : 0
        anchors.rightMargin: right_direction ? 8 : 0
        color: arrow_color
    }

    // right arrow if visible
    Item {
        id: right_arrow
        visible: right_direction
        height: arrow_size_
        width: arrow_size_
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right; anchors.rightMargin: parent.height /2 + 2

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
                ctx.lineTo(right_canvas.width, right_canvas.height / 2 -1)
                ctx.lineTo(0, right_canvas.height * 0.95)
                ctx.stroke()
            }
        }
    }
}
