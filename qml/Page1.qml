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
    }

    dialogError.onAccepted:
    {
        applicationControl.setError(false)
    }

    fileWriteDialog.onAccepted:
    {
        applicationControl.createFile(fileWriteDialog.fileUrl.toString())
    }

    sliderYAxis.onValueChanged:
    {
        applicationControl.setObjectOffsetY(Math.floor(sliderYAxis.value))
    }

    sliderXAxis.onValueChanged:
    {
        applicationControl.setObjectOffsetX(Math.floor(sliderXAxis.value))
    }

    sliderAzimuth.onValueChanged:
    {
        applicationControl.setAzimuth(Math.floor(sliderAzimuth.value))
    }

    sliderElevation.onValueChanged:
    {
        applicationControl.setElevation(Math.floor(sliderElevation.value))
    }

    sliderDistance.onValueChanged:
    {
        applicationControl.setDistance(Math.floor(sliderDistance.value*10)/10)
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
    }

    textVolumeY.onTextChanged:
    {
        var parse = parseInt(textVolumeY.text)
        applicationControl.setVolumeY(parse)
    }

    textVolumeZ.onTextChanged:
    {
        var parse = parseInt(textVolumeZ.text)
        applicationControl.setVolumeZ(parse)
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
