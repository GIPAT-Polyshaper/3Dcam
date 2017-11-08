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
}
