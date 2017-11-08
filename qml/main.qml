import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    color: "#eeeeee"
    title: qsTr("PolyShaper 3D CAM")

    SwipeView
    {
        id: container
        anchors.fill: parent

        Page1
        {

        }
    }
}
