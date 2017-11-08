import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item
{
    id: item1
    width: 800
    height: 600

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
        width: parent.width * 0.5 -16
        height: parent.height * 0.5 -16
        border.color: "#bbbbbb"
        anchors.top: parent.top
        border { width: 1 }

        ScrollView
        {
            id: view
            x: 3
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
//                text: test.textChange
                renderType: Text.NativeRendering
                opacity: 1
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                readOnly: true
                width: rectangle3DModel.width
                height: rectangle3DModel.height
                selectByMouse: true
                selectByKeyboard: true
            }
        }
    }

    GroupBox
    {
        id: boxMovimenti
        anchors.left: buttonFileDialog.left
        anchors.leftMargin: 0
        anchors.top: buttonFileDialog.bottom
        anchors.topMargin: 16
        title: "Spostamenti"
        width: rectangle3DModel.width
        height: parent.height * 0.33

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
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            id: sliderXAxis
            value: 0.5

            background: Rectangle
            {
                x: sliderXAxis.leftPadding
                y: sliderXAxis.topPadding + sliderXAxis.availableHeight / 2 - height / 2
                implicitWidth: 200
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
                border.color: "#bdbebf"
            }
        }
    }
}

