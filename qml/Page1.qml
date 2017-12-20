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
        viewer3d.update()
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
        labelAzimuthOffset.text = Math.floor(sliderAzimuth.value) + qsTr("°")
        gcodeGenerator.setAzimuth(Math.floor(sliderAzimuth.value))
        viewer3d.update()
    }

    sliderElevation.onValueChanged:
    {
        labelElevationOffset.text = Math.floor(sliderElevation.value) + qsTr("°")
        gcodeGenerator.setElevation(Math.floor(sliderElevation.value))
        viewer3d.update()
    }

    sliderDistance.onValueChanged:
    {
        labelDistanceOffset.text = Math.floor(sliderDistance.value*10)/10
        gcodeGenerator.setDistance(Math.floor(sliderDistance.value*10)/10)
        viewer3d.update()
    }

    textDiametroUtensile.onTextChanged:
    {
        var parse = parseFloat(textDiametroUtensile.text)
        if (isNaN(parse))
        {
            parse = 0
        }
        gcodeGenerator.setDiametro(parse)
    }

    textAltezzaUtensile.onTextChanged:
    {
        var parse = parseFloat(textAltezzaUtensile.text)
        if (isNaN(parse))
        {
            parse = 0
        }
        gcodeGenerator.setAltezza(parse)
    }

    textVelocitaUtensile.onTextChanged:
    {
        var parse = parseFloat(textVelocitaUtensile.text)
        if (isNaN(parse))
        {
            parse = 0
        }
        gcodeGenerator.setVelocita(parse)
    }

    textVolumeX.onTextChanged:
    {
        var parse = parseFloat(textVolumeX.text)
        if (isNaN(parse))
        {
            parse = 0
        }
        gcodeGenerator.setVolumeX(parse)
    }

    textVolumeY.onTextChanged:
    {
        var parse = parseFloat(textVolumeY.text)
        if (isNaN(parse))
        {
            parse = 0
        }
        gcodeGenerator.setVolumeY(parse)
    }

    textVolumeZ.onTextChanged:
    {
        var parse = parseFloat(textVolumeZ.text)
        if (isNaN(parse))
        {
            parse = 0
        }
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
