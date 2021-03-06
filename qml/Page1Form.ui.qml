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
    property alias buttonCodeGeneration: buttonCodeGeneration
    property alias labelDistanceOffset: labelDistanceOffset
    property alias sliderDistance: sliderDistance
    property alias labelElevationOffset: labelElevationOffset
    property alias labelAzimuthOffset: labelAzimuthOffset
    property alias sliderElevation: sliderElevation
    property alias sliderAzimuth: sliderAzimuth
    property alias textVolumeZ: textVolumeZ
    property alias textVolumeY: textVolumeY
    property alias textVolumeX: textVolumeX
    property alias spinBoxOverlap: spinBoxOverlap
    property alias comboFormaUtensile: comboFormaUtensile
    property alias textVelocitaUtensile: textVelocitaUtensile
    property alias textAltezzaUtensile: textAltezzaUtensile
    property alias textDiametroUtensile: textDiametroUtensile

    property alias viewer3d: viewer3d
    property alias labelXOffset: labelXOffset
    property alias labelYOffset: labelYOffset
    property alias sliderXAxis: sliderXAxis
    property alias sliderYAxis: sliderYAxis
    property alias fileDialog1: fileDialog
    property alias fileWriteDialog: fileWriteDialog
    property alias buttonFileDialog: buttonFileDialog
    property alias rectangle3DModel: viewer3d
    property alias boxMovimenti: boxMovimenti
    property alias dialogError: dialogError

    FileDialog
    {
        id: fileDialog
        title: "Apri file"
        folder: shortcuts.home
        modality: Qt.NonModal
    }

    FileDialog
    {
        id: fileWriteDialog
        title: "Salva file"
        folder: shortcuts.home
        modality: Qt.NonModal
        selectExisting: false
    }

    MessageDialog
    {
        icon: StandardIcon.Critical
        id: dialogError
        title: "Errore"
        modality: Qt.NonModal
        visible: applicationControl.error
        text: applicationControl.lastError
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
            y: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            height: parent.height - 48
            Layout.minimumWidth: 376

            color: "#eeeeee"

            opacity: 1

            Viewer3D
            {
                id: viewer3d
                height: (parent.height - boxCamera.height -36 < parent.width) ? (parent.height - boxCamera.height - 36) : (parent.width)
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                width: (parent.height - boxCamera.height -36 < parent.width) ? (parent.height - boxCamera.height-36) : (parent.width)
            }

            Frame
            {
                id: boxCamera
                Layout.fillWidth: true
                height: sliderXAxis.height * 3 + labelYOffset.height * 3 + 18
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: viewer3d.bottom
                anchors.topMargin: 18
                width: viewer3d.width
                Layout.minimumWidth: 376


                Label
                {
                    text: "Sposta camera"
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
                    y: boxCamera.topPadding - boxCamera.padding
                    width: parent.width
                    height: parent.height - boxCamera.topPadding + boxCamera.padding
                    color: "transparent"
                    border.color: "#bbbbbb"
                    radius: 2
                }

                Slider {
                    id: sliderAzimuth
                    height: 30
                    from: -180
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.verticalCenter: labelAzimuth.verticalCenter
                    stepSize: 1
                    to: 180
                    anchors.left: labelAzimuth.right
                    anchors.leftMargin: 6
                    value: 0
                    snapMode: Slider.SnapAlways

                    background: Rectangle
                    {
                        x: sliderAzimuth.leftPadding
                        y: sliderAzimuth.topPadding + sliderAzimuth.availableHeight / 2 - height / 2
                        implicitWidth: 100
                        implicitHeight: 4
                        width: sliderAzimuth.availableWidth
                        height: implicitHeight
                        radius: 2
                        color: "#888888"

                        Rectangle
                        {
                            width: sliderAzimuth.visualPosition * parent.width
                            height: parent.height
                            color: "#888888"
                            radius: 2
                        }
                    }

                    handle: Rectangle
                    {
                        x: sliderAzimuth.leftPadding + sliderAzimuth.visualPosition
                           * (sliderAzimuth.availableWidth - width)
                        y: sliderAzimuth.topPadding + sliderAzimuth.availableHeight / 2 - height / 2
                        implicitWidth: 18
                        implicitHeight: implicitWidth
                        radius: implicitHeight / 2
                        color: sliderAzimuth.pressed ? "#f0f0f0" : "#f6f6f6"
                        border.color: "#888888"
                    }
                }

                Slider
                {
                    height: 30
                    from: -180
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.verticalCenter: labelElevation.verticalCenter
                    stepSize: 1
                    to: 180
                    anchors.left: labelAzimuth.right
                    anchors.leftMargin: 6
                    id: sliderElevation
                    y: 121
                    value: 20
                    snapMode: Slider.SnapAlways

                    background: Rectangle
                    {
                        x: sliderElevation.leftPadding
                        y: sliderElevation.topPadding + sliderElevation.availableHeight / 2 - height / 2
                        implicitWidth: 100
                        implicitHeight: 4
                        width: sliderElevation.availableWidth
                        height: implicitHeight
                        radius: 2
                        color: "#888888"

                        Rectangle
                        {
                            width: sliderElevation.visualPosition * parent.width
                            height: parent.height
                            color: "#888888"
                            radius: 2
                        }
                    }

                    handle: Rectangle
                    {
                        x: sliderElevation.leftPadding + sliderElevation.visualPosition
                           * (sliderElevation.availableWidth - width)
                        y: sliderElevation.topPadding + sliderElevation.availableHeight / 2 - height / 2
                        implicitWidth: 18
                        implicitHeight: implicitWidth
                        radius: implicitHeight / 2
                        color: sliderElevation.pressed ? "#f0f0f0" : "#f6f6f6"
                        border.color: "#888888"
                    }
                }

                Label
                {
                    id: labelAzimuth
                    text: qsTr("Azimuth")
                    anchors.top: parent.top
                    anchors.topMargin: 6
                    renderType: Text.NativeRendering
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }

                Label
                {
                    id: labelElevation
                    text: qsTr("Elevazione")
                    anchors.right: labelAzimuth.right
                    anchors.rightMargin: 0
                    anchors.top: labelAzimuthOffset.bottom
                    anchors.topMargin: 6
                    renderType: Text.NativeRendering
                }

                Label
                {
                    id: labelAzimuthOffset
                    text: viewer3d.azimuthCam + qsTr("°")
                    anchors.top: sliderAzimuth.bottom
                    anchors.topMargin: 0
                    anchors.horizontalCenter: sliderAzimuth.horizontalCenter
                }

                Label
                {
                    id: labelElevationOffset
                    x: 130
                    text: viewer3d.elevationCam + qsTr("°")
                    anchors.top: sliderElevation.bottom
                    anchors.topMargin: 0
                    anchors.horizontalCenter: sliderElevation.horizontalCenter
                }

                Slider
                {
                    height: 30
                    anchors.left: labelAzimuth.right
                    anchors.leftMargin: 6
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.verticalCenter: labelDistance.verticalCenter
                    from: 0
                    stepSize: 0.5
                    to: 10
                    id: sliderDistance
                    y: 121
                    value: 3
                    snapMode: Slider.SnapAlways

                    background: Rectangle
                    {
                        x: sliderDistance.leftPadding
                        y: sliderDistance.topPadding + sliderDistance.availableHeight / 2 - height / 2
                        implicitWidth: 100
                        implicitHeight: 4
                        width: sliderDistance.availableWidth
                        height: implicitHeight
                        radius: 2
                        color: "#888888"

                        Rectangle
                        {
                            width: sliderDistance.visualPosition * parent.width
                            height: parent.height
                            color: "#888888"
                            radius: 2
                        }
                    }

                    handle: Rectangle
                    {
                        x: sliderDistance.leftPadding + sliderDistance.visualPosition
                           * (sliderDistance.availableWidth - width)
                        y: sliderDistance.topPadding + sliderDistance.availableHeight / 2 - height / 2
                        implicitWidth: 18
                        implicitHeight: implicitWidth
                        radius: implicitHeight / 2
                        color: sliderDistance.pressed ? "#f0f0f0" : "#f6f6f6"
                        border.color: "#888888"
                    }
                }

                Label
                {
                    id: labelDistance
                    text: qsTr("Zoom")
                    anchors.right: labelAzimuth.right
                    anchors.rightMargin: 0
                    anchors.top: labelElevationOffset.bottom
                    anchors.topMargin: 6
                    renderType: Text.NativeRendering
                }

                Label
                {
                    id: labelDistanceOffset
                    text: viewer3d.distanceCam
                    anchors.top: sliderDistance.bottom
                    anchors.topMargin: 0
                    anchors.horizontalCenter: sliderDistance.horizontalCenter
                }

            }

        }

        Rectangle
        {
            id: rectangle1
            y: 0
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
                topPadding: 14
                bottomPadding: 14
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
                    text: applicationControl.toolW
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    renderType: Text.NativeRendering
                    validator: IntValidator {bottom: 0; top: 1000000;}
                }

                TextField
                {
                    id: textAltezzaUtensile
                    x: 128
                    y: 46
                    height: implicitHeight - 12
                    text: applicationControl.toolH
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: textDiametroUtensile.bottom
                    anchors.topMargin: boxUtensile.topPadding
                    renderType: Text.NativeRendering
                    validator: IntValidator {bottom: 0; top: 1000000;}
                }

                TextField {
                    id: textVelocitaUtensile
                    x: 128
                    y: 92
                    height: implicitHeight - 12
                    text: applicationControl.toolSp
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    font.pointSize: 9
                    topPadding: 3
                    anchors.top: textAltezzaUtensile.bottom
                    anchors.topMargin: boxUtensile.topPadding
                    renderType: Text.NativeRendering
                    bottomPadding: 3
                    validator: IntValidator {bottom: 0; top: 1000000;}
                }

                Label
                {
                    id: label3
                    x: 90
                    y: 7
                    text: qsTr("Diametro (mm):")
                    anchors.right: textDiametroUtensile.left
                    anchors.rightMargin: 6
                    anchors.verticalCenter: textDiametroUtensile.verticalCenter
                }

                Label
                {
                    id: label4
                    x: 79
                    y: 47
                    text: qsTr("Altezza (mm):")
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
                    model: ["Candela"]
                    currentIndex: 0
                }

                SpinBox
                {
                    id: spinBoxOverlap
                    x: 41
                    y: 27
                    height: textDiametroUtensile.height
                    value: applicationControl.overlap
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
                anchors.topMargin: 14
                width: parent.width
                bottomPadding: 14
                topPadding: 14

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
                    text: applicationControl.volumeX
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    renderType: Text.NativeRendering
                    height: implicitHeight - 12
                    validator: IntValidator {bottom: 0; top: 1000000;}
                }

                TextField
                {
                    id: textVolumeY
                    x: 128
                    y: 46
                    text: applicationControl.volumeY
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    renderType: Text.NativeRendering
                    height: implicitHeight - 12
                    anchors.top: textVolumeX.bottom
                    anchors.topMargin: boxVolumeLavoro.topPadding
                    validator: IntValidator {bottom: 0; top: 1000000;}
                }

                TextField
                {
                    id: textVolumeZ
                    x: 128
                    y: 92
                    text: applicationControl.volumeZ
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    bottomPadding: 3
                    topPadding: 3
                    font.pointSize: 9
                    renderType: Text.NativeRendering
                    height: implicitHeight - 12
                    anchors.top: textVolumeY.bottom
                    anchors.topMargin: boxVolumeLavoro.topPadding
                    validator: IntValidator {bottom: 0; top: 1000000;}
                }

                Label {
                    id: label
                    x: 90
                    y: 7
                    text: qsTr("Asse X (mm):")
                    anchors.verticalCenter: textVolumeX.verticalCenter
                    anchors.right: textVolumeX.left
                    anchors.rightMargin: 6
                }

                Label {
                    id: label1
                    x: 79
                    y: 47
                    text: qsTr("Asse Y (mm):")
                    anchors.right: textVolumeY.left
                    anchors.rightMargin: 6
                    anchors.verticalCenter: textVolumeY.verticalCenter
                }

                Label
                {
                    id: label2
                    x: 79
                    y: 80
                    text: qsTr("Asse Z (mm):")
                    anchors.verticalCenter: textVolumeZ.verticalCenter
                    anchors.right: textVolumeZ.left
                    anchors.rightMargin: 6
                }
            }

            Frame
            {
                id: boxMovimenti
                topPadding: 14
                bottomPadding: 1
                anchors.top: boxVolumeLavoro.bottom
                anchors.topMargin: 14
                height: sliderXAxis.height * 2 + labelYOffset.height * 2 + 18
                width: parent.width
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
                    to: applicationControl.volumeY
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
                    to: applicationControl.volumeX
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
                    text: applicationControl.objectOffsetY + qsTr("mm")
                    anchors.top: sliderYAxis.bottom
                    anchors.topMargin: 0
                    anchors.horizontalCenter: sliderYAxis.horizontalCenter
                }

                Label
                {
                    id: labelXOffset
                    x: 130
                    text: applicationControl.objectOffsetX + qsTr("mm")
                    anchors.top: sliderXAxis.bottom
                    anchors.topMargin: 0
                    anchors.horizontalCenter: sliderXAxis.horizontalCenter
                }
            }
            Rectangle
            {
                id: rectangle2
                x: 0
                width: parent.width
                height: buttonCodeGeneration.height + 24
                Layout.maximumWidth: buttonFileDialog.width + buttonCodeGeneration.width + 16
                color: "#eeeeee"
                anchors.top: boxMovimenti.bottom
                anchors.topMargin: 12
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Button
            {
                id: buttonFileDialog
                text: qsTr("Apri file")
                anchors.left: parent.left
                anchors.leftMargin: 48
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
                x: 204
                text: qsTr("Genera codice")
                anchors.right: parent.right
                anchors.rightMargin: 48
                anchors.verticalCenter: buttonFileDialog.verticalCenter
                clip: false

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
        }







    }
}
