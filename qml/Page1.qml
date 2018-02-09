import QtQuick 2.7

Page1Form
{
    buttonFileDialog.onClicked:
    {
        fileDialog1.visible = true
    }

    buttonCodeGeneration.onClicked:
    {
        fileWriteDialog.visible = true
    }

    fileDialog1.onAccepted:
    {
        gcodeGenerator.openFile(fileDialog1.fileUrl.toString())
        viewer3d.update()
    }

    fileWriteDialog.onAccepted:
    {
        gcodeGenerator.createFile(fileWriteDialog.fileUrl.toString())
//        gcodeGenerator.getPolyhedron()
    }

    sliderYAxis.onValueChanged:
    {
        labelYOffset.text = Math.floor(sliderYAxis.value) + qsTr("mm")
    }

    sliderXAxis.onValueChanged:
    {
        labelXOffset.text = Math.floor(sliderXAxis.value) + qsTr("mm")
    }

    sliderAzimuth.onValueChanged:
    {
        gcodeGenerator.setAzimuth(Math.floor(sliderAzimuth.value))
        viewer3d.update()
    }

    sliderElevation.onValueChanged:
    {
        gcodeGenerator.setElevation(Math.floor(sliderElevation.value))
        viewer3d.update()
    }

    sliderDistance.onValueChanged:
    {
        gcodeGenerator.setDistance(Math.floor(sliderDistance.value*10)/10)
        viewer3d.update()
    }

    textDiametroUtensile.onTextChanged:
    {
        var parse = parseInt(textDiametroUtensile.text)
        gcodeGenerator.setDiametro(parse)
    }

    textAltezzaUtensile.onTextChanged:
    {
        var parse = parseInt(textAltezzaUtensile.text)
        gcodeGenerator.setAltezza(parse)
    }

    textVelocitaUtensile.onTextChanged:
    {
        var parse = parseInt(textVelocitaUtensile.text)
        gcodeGenerator.setVelocita(parse)
    }

    textVolumeX.onTextChanged:
    {
        var parse = parseInt(textVolumeX.text)
        gcodeGenerator.setVolumeX(parse)
    }

    textVolumeY.onTextChanged:
    {
        var parse = parseInt(textVolumeY.text)
        gcodeGenerator.setVolumeY(parse)
    }

    textVolumeZ.onTextChanged:
    {
        var parse = parseInt(textVolumeZ.text)
        gcodeGenerator.setVolumeZ(parse)
    }

    spinBoxOverlap.onValueChanged:
    {
        gcodeGenerator.setOverlap(spinBoxOverlap.value)
    }

    comboFormaUtensile.onCurrentTextChanged:
    {
        gcodeGenerator.setForma(comboFormaUtensile.currentText)
    }
}
