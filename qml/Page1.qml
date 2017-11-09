import QtQuick 2.7

Page1Form
{
    buttonFileDialog.onClicked:
    {
        fileDialog1.visible = true
    }

    fileDialog1.onAccepted:
    {
        gcodeGenerator.openFile(fileDialog1.fileUrl.toString())
    }

    sliderYAxis.onValueChanged:
    {
        labelYOffset.text = Math.floor(sliderYAxis.value) + qsTr("mm")
    }

    sliderXAxis.onValueChanged:
    {
        labelXOffset.text = Math.floor(sliderXAxis.value) + qsTr("mm")
    }
}
