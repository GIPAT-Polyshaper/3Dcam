import QtQuick 2.7

Page1Form
{

    buttonFileDialog.onClicked:
    {
        fileDialog1.visible = true
    }

    //    fileDialog1.onAccepted:
    //    {
    //        test.openFile(fileDialog1.fileUrl.toString())
    //    }
    //    button3.onClicked:
    //    {
    //        gcodeGenerator.readAndGenerate();
    //    }
}
