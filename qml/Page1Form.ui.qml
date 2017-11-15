import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import PolyShaper3Dcam 1.0

Item
{
    id: item1
    width: 800
    height: 600

    property alias viewer3d: viewer3d
    property alias labelXOffset: labelXOffset
    property alias labelYOffset: labelYOffset
    property alias sliderXAxis: sliderXAxis
    property alias sliderYAxis: sliderYAxis
    property alias fileDialog1: fileDialog
    property alias buttonFileDialog: buttonFileDialog
    property alias rectangle3DModel: viewer3d
    property alias boxMovimenti: boxMovimenti

    FileDialog
    {
        id: fileDialog
        title: "Apri file"
        folder: shortcuts.home
        modality: Qt.NonModal
    }

    GridLayout
    {
        rowSpacing: 16
        columnSpacing: 16
        anchors.rightMargin: 16
        anchors.leftMargin: 16
        anchors.bottomMargin: 16
        anchors.topMargin: 16
        anchors.fill: parent
        columns: 2

        Rectangle
        {
            id: rectangle
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 376
            Layout.minimumHeight: 276
            color: "#eeeeee"
            opacity: 1

            Viewer3D
            {
                id: viewer3d
                height: (parent.height < parent.width) ? (parent.height) : (parent.width)
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: (parent.height < parent.width) ? (parent.height) : (parent.width)
            }
        }

        Rectangle
        {
            id: rectangle1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 376
            Layout.maximumWidth: 376 < parent.width * 0.3 ? parent.width * 0.3 : 376
            //            height: boxUtensile.height + boxVolumeLavoro.height
            color: "#eeeeee"

            Frame
            {
                id: boxUtensile
                height: boxUtensile.topPadding * 6 + textDiametroUtensile.height * 5
                anchors.top: parent.top
                anchors.topMargin: 0
                width: parent.width

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
                    anchors.right: parent.right
                    anchors.rightMargin: 0
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
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: textDiametroUtensile.bottom
                    anchors.topMargin: boxUtensile.topPadding
                    renderType: Text.NativeRendering
                }

                TextField {
                    id: textVelocitaUtensile
                    x: 128
                    y: 92
                    height: implicitHeight - 12
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
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

            Frame
            {
                id: boxVolumeLavoro

                height: boxVolumeLavoro.topPadding * 4 + textVolumeX.height * 3
                anchors.top: boxUtensile.bottom
                anchors.topMargin: 16
                width: parent.width

                background: Rectangle
                {
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
                    anchors.right: parent.right
                    anchors.rightMargin: 0
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
                    anchors.right: parent.right
                    anchors.rightMargin: 0
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
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    bottomPadding: 3
                    topPadding: 3
                    font.pointSize: 9
                    renderType: Text.NativeRendering
                    height: implicitHeight - 12
                    anchors.top: textVolumeY.bottom
                    anchors.topMargin: boxVolumeLavoro.topPadding
                }

                Label {
                    id: label
                    x: 90
                    y: 7
                    text: qsTr("Asse x:")
                    anchors.verticalCenter: textVolumeX.verticalCenter
                    anchors.right: textVolumeX.left
                    anchors.rightMargin: 6
                }

                Label {
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
        }

        Rectangle
        {
            id: rectangle2
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: buttonFileDialog.width + buttonCodeGeneration.width + 16
            color: "#eeeeee"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Button
            {
                id: buttonFileDialog
                text: qsTr("Apri file")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 0
                padding: 8
                bottomPadding: 10
                topPadding: 10

                background: BorderImage
                {
                    id: immaginebottone
                    horizontalTileMode: BorderImage.Stretch
                    verticalTileMode: BorderImage.Stretch
                    source: buttonFileDialog.pressed ? "images/button-pressed.png" : "images/button.png"
                    border.left: 4
                    border.right: 4
                    border.top: 4
                    border.bottom: 4
                    width: buttonFileDialog.width
                    height: buttonFileDialog.height
                }
            }

            Button
            {
                id: buttonCodeGeneration
                text: qsTr("Genera codice")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: buttonFileDialog.right
                clip: false
                anchors.topMargin: 16

                anchors.leftMargin: 16
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

        Frame
        {
            id: boxMovimenti
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: sliderXAxis.height * 2 + labelYOffset.height * 2 + 18
            Layout.maximumHeight: sliderXAxis.height * 2 + labelYOffset.height * 2 + 18
            Layout.maximumWidth:  376 < parent.width * 0.3 ? parent.width * 0.3 : 376

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

            background: Rectangle
            {
                y: boxMovimenti.topPadding - boxMovimenti.padding
                width: parent.width
                height: parent.height - boxMovimenti.topPadding + boxMovimenti.padding
                color: "transparent"
                border.color: "#bbbbbb"
                radius: 2
            }

            Slider {
                id: sliderYAxis
                height: 30
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.verticalCenter: labelYAxis.verticalCenter
                stepSize: 1
                to: 20
                anchors.left: labelYAxis.right
                anchors.leftMargin: 6
                value: 0
                snapMode: Slider.SnapAlways

                background: Rectangle
                {
                    x: sliderYAxis.leftPadding
                    y: sliderYAxis.topPadding + sliderYAxis.availableHeight / 2 - height / 2
                    implicitWidth: 100
                    implicitHeight: 4
                    width: sliderYAxis.availableWidth
                    height: implicitHeight
                    radius: 2
                    color: "#888888"

                    Rectangle
                    {
                        width: sliderYAxis.visualPosition * parent.width
                        height: parent.height
                        color: "#888888"
                        radius: 2
                    }
                }

                handle: Rectangle
                {
                    x: sliderYAxis.leftPadding + sliderYAxis.visualPosition
                       * (sliderYAxis.availableWidth - width)
                    y: sliderYAxis.topPadding + sliderYAxis.availableHeight / 2 - height / 2
                    implicitWidth: 18
                    implicitHeight: implicitWidth
                    radius: implicitHeight / 2
                    color: sliderYAxis.pressed ? "#f0f0f0" : "#f6f6f6"
                    border.color: "#888888"
                }
            }

            Slider
            {
                height: 30
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.verticalCenter: labelXAxis.verticalCenter
                stepSize: 1
                to: 20
                anchors.left: labelYAxis.right
                anchors.leftMargin: 6
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
                    x: sliderXAxis.leftPadding + sliderXAxis.visualPosition
                       * (sliderXAxis.availableWidth - width)
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
                text: qsTr("Asse Y")
                anchors.top: parent.top
                anchors.topMargin: 6
                renderType: Text.NativeRendering
                anchors.left: parent.left
                anchors.leftMargin: 0
            }

            Label
            {
                id: labelXAxis
                text: qsTr("Asse X")
                anchors.top: labelYOffset.bottom
                anchors.topMargin: 6
                anchors.left: labelYAxis.left
                anchors.leftMargin: 0
                renderType: Text.NativeRendering
            }

            Label
            {
                id: labelYOffset
                text: qsTr("0mm")
                anchors.top: sliderYAxis.bottom
                anchors.topMargin: 0
                anchors.horizontalCenter: sliderYAxis.horizontalCenter
            }

            Label
            {
                id: labelXOffset
                x: 130
                text: qsTr("0mm")
                anchors.top: sliderXAxis.bottom
                anchors.topMargin: 0
                anchors.horizontalCenter: sliderXAxis.horizontalCenter
            }
        }
    }
}
