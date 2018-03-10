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
        applicationControl.openFile(fileDialog1.fileUrl.toString())
        viewer3d.update()
    }

    fileWriteDialog.onAccepted:
    {
        applicationControl.createFile(fileWriteDialog.fileUrl.toString())
//        gcodeGenerator.getPolyhedron()
    }

    sliderYAxis.onValueChanged:
    {
        applicationControl.setObjectOffsetY(Math.floor(sliderYAxis.value))
        viewer3d.update()
    }

    sliderXAxis.onValueChanged:
    {
        applicationControl.setObjectOffsetX(Math.floor(sliderXAxis.value))
        viewer3d.update()
    }

    sliderAzimuth.onValueChanged:
    {
        applicationControl.setAzimuth(Math.floor(sliderAzimuth.value))
        viewer3d.update()
    }

    sliderElevation.onValueChanged:
    {
        applicationControl.setElevation(Math.floor(sliderElevation.value))
        viewer3d.update()
    }

    sliderDistance.onValueChanged:
    {
        applicationControl.setDistance(Math.floor(sliderDistance.value*10)/10)
        viewer3d.update()
    }

    textDiametroUtensile.onTextChanged:
    {
        var parse = parseInt(textDiametroUtensile.text)
        applicationControl.setDiametro(parse)
    }

    textAltezzaUtensile.onTextChanged:
    {
        var parse = parseInt(textAltezzaUtensile.text)
        applicationControl.setAltezza(parse)
    }

    textVelocitaUtensile.onTextChanged:
    {
        var parse = parseInt(textVelocitaUtensile.text)
        applicationControl.setVelocita(parse)
    }

    textVolumeX.onTextChanged:
    {
        var parse = parseInt(textVolumeX.text)
        applicationControl.setVolumeX(parse)
        viewer3d.update()
    }

    textVolumeY.onTextChanged:
    {
        var parse = parseInt(textVolumeY.text)
        applicationControl.setVolumeY(parse)
        viewer3d.update()
    }

    textVolumeZ.onTextChanged:
    {
        var parse = parseInt(textVolumeZ.text)
        applicationControl.setVolumeZ(parse)
        viewer3d.update()
    }

    spinBoxOverlap.onValueChanged:
    {
        applicationControl.setOverlap(spinBoxOverlap.value)
    }

    comboFormaUtensile.onCurrentTextChanged:
    {
        applicationControl.setForma(comboFormaUtensile.currentText)
    }
}
