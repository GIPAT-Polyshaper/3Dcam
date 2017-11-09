import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item
{
    id: item1
    width: 800
    height: 600
    property alias labelXOffset: labelXOffset
    property alias labelYOffset: labelYOffset
    property alias sliderXAxis: sliderXAxis

    property alias sliderYAxis: sliderYAxis
    property alias fileDialog1: fileDialog
    property alias buttonFileDialog: buttonFileDialog
    property alias rectangle3DModel: rectangle3DModel
    property alias boxMovimenti: boxMovimenti

    FileDialog
    {
        id: fileDialog
        title: "Apri file"
        folder: shortcuts.home
        modality: Qt.NonModal
    }

    Button
    {
        id: buttonFileDialog
        x: 16
        y: 262
        text: qsTr("Apri file")
        padding: 8
        bottomPadding: 10
        topPadding: 10
        anchors.topMargin: 16
        anchors.left: rectangle3DModel.left
        anchors.leftMargin: 0
        anchors.top: rectangle3DModel.bottom

        background: BorderImage
        {
            id: immaginebottone
            horizontalTileMode: BorderImage.Stretch
            verticalTileMode: BorderImage.Stretch
            source: buttonFileDialog.pressed ? "images/button-pressed.png" : "images/button.png"
            border.left: 4 ; border.right: 4 ; border.top: 4 ; border.bottom: 4
            width: buttonFileDialog.width
            height: buttonFileDialog.height
        }
    }

    Rectangle
    {
        id: rectangle3DModel
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.topMargin: 16
        width: parent.width * 0.5 - rectangle3DModel.anchors.leftMargin - (boxParametri.anchors.leftMargin / 2)
        height: parent.height * 0.5 - rectangle3DModel.anchors.topMargin
        border.color: "#bbbbbb"
        anchors.top: parent.top
        border { width: 1 }

        ScrollView
        {
            id: view
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            width: rectangle3DModel.width
            height: rectangle3DModel.height
            clip: true

            TextArea
            {
                id: textArea
                renderType: Text.NativeRendering
                opacity: 1
                readOnly: true
                width: rectangle3DModel.width
                height: rectangle3DModel.height
                anchors.left: parent.left
                anchors.leftMargin: -10
                anchors.top: parent.top
                anchors.topMargin: -6
                selectByMouse: true
                selectByKeyboard: true
            }
        }
    }

    Frame
    {
        id: boxMovimenti
        anchors.left: buttonFileDialog.left
        anchors.leftMargin: 0
        anchors.top: buttonFileDialog.bottom
        anchors.topMargin: 16

        Label
        {
            text: "Sposta oggetto"
            horizontalAlignment: Text.AlignHCenter
            width: implicitWidth + 4
            anchors.top: parent.top
            anchors.topMargin: -20
            renderType: Text.NativeRendering

            background: Rectangle
            {
                color: "#eeeeee"
                width: parent.width
                height: parent.height
            }
        }

        width: parent.width * 0.3
        height: parent.height - rectangle3DModel.height
                - (rectangle3DModel.anchors.topMargin + buttonFileDialog.anchors.topMargin + boxMovimenti.anchors.topMargin * 2)
                - buttonFileDialog.height

        background: Rectangle
        {
            y: boxMovimenti.topPadding - boxMovimenti.padding
            width: parent.width
            height: parent.height - boxMovimenti.topPadding + boxMovimenti.padding
            color: "transparent"
            border.color: "#bbbbbb"
            radius: 2
        }

        Slider
        {
            id: sliderYAxis
            y: 0
            width: 30
            height: (parent.height - labelXAxis.height - labelXAxis.anchors.topMargin - sliderXAxis.height) < (parent.width - sliderYAxis.x - sliderYAxis.width)
                    ? (parent.height - labelXAxis.height - labelXAxis.anchors.topMargin - sliderXAxis.height)
                    : (parent.width - sliderYAxis.x - sliderYAxis.width)
            stepSize: 1
            to: 20
            anchors.left: labelYAxis.right
            anchors.leftMargin: 6
            anchors.bottom: sliderXAxis.top
            anchors.bottomMargin: 0
            orientation: Qt.Vertical
            value: 0
            snapMode: Slider.SnapAlways

            background: Rectangle
            {
                x: sliderYAxis.leftPadding + sliderYAxis.availableWidth /2 - width /2
                y: sliderXAxis.topPadding /*+ sliderXAxis.availableHeight / 2 - height / 2*/
                implicitWidth: 4
                implicitHeight: 100
                width: implicitWidth
                height: sliderYAxis.availableHeight
                radius: 2
                color: "#888888"

                Rectangle
                {
                    width: parent.width
                    height: sliderYAxis.visualPosition * parent.height
                    color: "#888888"
                    radius: 2
                }
            }

            handle: Rectangle
            {
                y: sliderXAxis.topPadding + sliderYAxis.visualPosition * (sliderYAxis.availableHeight - height)
                x: sliderYAxis.leftPadding + sliderYAxis.availableWidth / 2 - width / 2
                implicitWidth: 18
                implicitHeight: implicitWidth
                radius: implicitHeight / 2
                color: sliderYAxis.pressed ? "#f0f0f0" : "#f6f6f6"
                border.color: "#888888"
            }
        }

        Slider
        {
            width: (parent.width - sliderYAxis.x - sliderYAxis.width) < (parent.height - labelXAxis.height - labelXAxis.anchors.topMargin - sliderXAxis.height)
                   ? (parent.width - sliderYAxis.x - sliderYAxis.width)
                   : (parent.height - labelXAxis.height - labelXAxis.anchors.topMargin - sliderXAxis.height)
            height: 30
            stepSize: 1
            to: 20
            anchors.left: sliderYAxis.right
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 21
            id: sliderXAxis
            y: 121
            value: 0
            snapMode: Slider.SnapAlways

            background: Rectangle
            {
                x: sliderXAxis.leftPadding
                y: sliderXAxis.topPadding + sliderXAxis.availableHeight / 2 - height / 2
                implicitWidth: 100
                implicitHeight: 4
                width: sliderXAxis.availableWidth
                height: implicitHeight
                radius: 2
                color: "#888888"

                Rectangle
                {
                    width: sliderXAxis.visualPosition * parent.width
                    height: parent.height
                    color: "#888888"
                    radius: 2
                }
            }

            handle: Rectangle
            {
                x: sliderXAxis.leftPadding + sliderXAxis.visualPosition * (sliderXAxis.availableWidth - width)
                y: sliderXAxis.topPadding + sliderXAxis.availableHeight / 2 - height / 2
                implicitWidth: 18
                implicitHeight: implicitWidth
                radius: implicitHeight / 2
                color: sliderXAxis.pressed ? "#f0f0f0" : "#f6f6f6"
                border.color: "#888888"
            }
        }

        Label
        {
            id: labelYAxis
            y: 79
            text: qsTr("Asse Y")
            renderType: Text.NativeRendering
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: sliderYAxis.verticalCenter
        }

        Label
        {
            id: labelXAxis
            text: qsTr("Asse X")
            renderType: Text.NativeRendering
            anchors.top: sliderXAxis.bottom
            anchors.topMargin: 6
            anchors.horizontalCenter: sliderXAxis.horizontalCenter
        }

        Label {
            id: labelYOffset
            y: 65
            text: qsTr("0mm")
            anchors.verticalCenter: sliderYAxis.verticalCenter
            anchors.left: sliderYAxis.right
            anchors.leftMargin: 6
        }

        Label {
            id: labelXOffset
            x: 130
            y: 121
            text: qsTr("0mm")
            anchors.horizontalCenter: sliderXAxis.horizontalCenter
            anchors.bottom: sliderXAxis.top
            anchors.bottomMargin: 6
        }
    }

    Frame
    {
        id: boxParametri
        width: parent.width * 0.5 - 24
        height: 400
        anchors.left: rectangle3DModel.right
        anchors.leftMargin: 16
        anchors.top: parent.top
        anchors.topMargin: 16

        background: Rectangle
        {
            y: boxParametri.topPadding - boxParametri.padding
            width: parent.width
            height: parent.height - boxParametri.topPadding + boxParametri.padding
            color: "transparent"
            border.color: "#bbbbbb"
            radius: 2
        }

        Label
        {
            text: "Parametri"
            horizontalAlignment: Text.AlignHCenter
            width: implicitWidth + 4
            anchors.top: parent.top
            anchors.topMargin: -20
            renderType: Text.NativeRendering

            background: Rectangle
            {
                color: "#eeeeee"
                width: parent.width
                height: parent.height
                opacity: 1
            }
        }

        Frame
        {
            id: boxVolumeLavoro
            x: 0
            y: 13
            width: 352
            height: boxVolumeLavoro.topPadding * 4 + textVolumeX.height * 3

            background: Rectangle
            {
                y: boxVolumeLavoro.topPadding - boxVolumeLavoro.padding
                width: parent.width
                height: parent.height - boxVolumeLavoro.topPadding + boxVolumeLavoro.padding
                color: "transparent"
                border.color: "#bbbbbb"
                radius: 2
            }

            Label
            {
                text: "Volume di lavoro"
                horizontalAlignment: Text.AlignHCenter
                width: implicitWidth + 4
                anchors.top: parent.top
                anchors.topMargin: -20
                renderType: Text.NativeRendering

                background: Rectangle
                {
                    color: "#eeeeee"
                    width: parent.width
                    height: parent.height
                    opacity: 1
                }
            }

            TextField
            {
                id: textVolumeX
                x: 128
                text: qsTr("")
                anchors.top: parent.top
                anchors.topMargin: 0
                renderType: Text.NativeRendering
                height: implicitHeight - 12
            }

            TextField
            {
                id: textVolumeY
                x: 128
                y: 46
                text: qsTr("")
                renderType: Text.NativeRendering
                height: implicitHeight - 12
                anchors.top: textVolumeX.bottom
                anchors.topMargin: boxVolumeLavoro.topPadding
            }

            TextField
            {
                id: textVolumeZ
                x: 128
                y: 92
                text: qsTr("")
                bottomPadding: 3
                topPadding: 3
                font.pointSize: 9
                renderType: Text.NativeRendering
                height: implicitHeight - 12
                anchors.top: textVolumeY.bottom
                anchors.topMargin: boxVolumeLavoro.topPadding
            }

            Label
            {
                id: label
                x: 90
                y: 7
                text: qsTr("Asse x:")
                anchors.verticalCenter: textVolumeX.verticalCenter
                anchors.right: textVolumeX.left
                anchors.rightMargin: 6
            }

            Label
            {
                id: label1
                x: 79
                y: 47
                text: qsTr("Asse y:")
                anchors.right: textVolumeY.left
                anchors.rightMargin: 6
                anchors.verticalCenter: textVolumeY.verticalCenter
            }

            Label
            {
                id: label2
                x: 79
                y: 80
                text: qsTr("Asse z:")
                anchors.verticalCenter: textVolumeZ.verticalCenter
                anchors.right: textVolumeZ.left
                anchors.rightMargin: 6
            }
        }

        Frame
        {
            id: boxUtensile
            x: 0
            y: 164
            width: 352
            height: boxUtensile.topPadding * 6 + textDiametroUtensile.height * 5

            Label
            {
                width: implicitWidth + 4
                text: "Utensile"
                anchors.top: parent.top
                anchors.topMargin: -20
                horizontalAlignment: Text.AlignHCenter
                background: Rectangle
                {
                    width: parent.width
                    height: parent.height
                    color: "#eeeeee"
                    opacity: 1
                }
                renderType: Text.NativeRendering
            }

            TextField
            {
                id: textDiametroUtensile
                x: 128
                height: implicitHeight - 12
                text: qsTr("")
                anchors.top: parent.top
                anchors.topMargin: 0
                renderType: Text.NativeRendering
            }

            TextField
            {
                id: textAltezzaUtensile
                x: 128
                y: 46
                height: implicitHeight - 12
                text: qsTr("")
                anchors.top: textDiametroUtensile.bottom
                anchors.topMargin: boxUtensile.topPadding
                renderType: Text.NativeRendering
            }

            TextField
            {
                id: textVelocitaUtensile
                x: 128
                y: 92
                height: implicitHeight - 12
                text: qsTr("")
                font.pointSize: 9
                topPadding: 3
                anchors.top: textAltezzaUtensile.bottom
                anchors.topMargin: boxUtensile.topPadding
                renderType: Text.NativeRendering
                bottomPadding: 3
            }

            Label
            {
                id: label3
                x: 90
                y: 7
                text: qsTr("Diametro:")
                anchors.right: textDiametroUtensile.left
                anchors.rightMargin: 6
                anchors.verticalCenter: textDiametroUtensile.verticalCenter
            }

            Label
            {
                id: label4
                x: 79
                y: 47
                text: qsTr("Altezza:")
                anchors.right: textAltezzaUtensile.left
                anchors.rightMargin: 6
                anchors.verticalCenter: textAltezzaUtensile.verticalCenter
            }

            Label
            {
                id: label5
                x: 79
                y: 80
                text: qsTr("Velocità (mm/min):")
                anchors.right: textVelocitaUtensile.left
                anchors.rightMargin: 6
                anchors.verticalCenter: textVelocitaUtensile.verticalCenter
            }

            ComboBox
            {
                id: comboFormaUtensile
                x: 208
                y: 114
                height: textDiametroUtensile.height
                rightPadding: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                width: textVelocitaUtensile.width
                anchors.top: textVelocitaUtensile.bottom
                anchors.topMargin: boxUtensile.topPadding
                model: ["Sferica", "Candela"]
            }

            SpinBox
            {
                id: spinBoxOverlap
                x: 41
                y: 27
                height: textDiametroUtensile.height
                value: 50
                to: 100
                anchors.top: comboFormaUtensile.bottom
                anchors.topMargin: boxUtensile.topPadding
                anchors.right: parent.right
                anchors.rightMargin: 0
                width: comboFormaUtensile.width
            }

            Label
            {
                id: label6
                x: 90
                y: 127
                text: qsTr("Forma:")
                anchors.verticalCenter: comboFormaUtensile.verticalCenter
                anchors.right: comboFormaUtensile.left
                anchors.rightMargin: 6
            }

            Label
            {
                id: label7
                x: 90
                y: 167
                text: qsTr("Overlap passate (%):")
                anchors.right: spinBoxOverlap.left
                anchors.rightMargin: 6
                anchors.verticalCenter: spinBoxOverlap.verticalCenter
            }

            background: Rectangle
            {
                y: boxUtensile.topPadding - boxUtensile.padding
                width: parent.width
                height: parent.height - boxUtensile.topPadding + boxUtensile.padding
                color: "#00000000"
                radius: 2
                border.color: "#bbbbbb"
            }
        }
    }

    Button
    {
        id: buttonCodeGeneration
        text: qsTr("Genera codice")
        clip: false
        anchors.top: boxParametri.bottom
        anchors.topMargin: 16
        anchors.left: boxParametri.left
        anchors.leftMargin: 0
        topPadding: 10
        bottomPadding: 10
        padding: 8
        width: implicitWidth
        height: implicitHeight

        background: BorderImage
        {
            id: immaginebottone1
            width: buttonCodeGeneration.width
            height: buttonCodeGeneration.height
            horizontalTileMode: BorderImage.Stretch
            verticalTileMode: BorderImage.Stretch
            border.left: 4
            border.top: 4
            source: buttonCodeGeneration.pressed ? "images/button-pressed.png" : "images/button.png"
            border.right: 4
            border.bottom: 4
        }

    }
}

