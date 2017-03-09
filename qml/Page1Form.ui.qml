import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias button1: button1
    property alias button2: button2
    property alias button3: button3
    property alias button4: button4

    RowLayout {
        anchors.centerIn: parent

        Button {
            id: button1
            text: qsTr("Antani 1")
        }

        Button {
            id: button2
            text: qsTr("Antani 2")
        }
    }

    Button {
        id: button3
        x: 225
        y: 51
        text: qsTr("frofri")
    }

    Button {
        id: button
        x: 153
        y: 129
        text: qsTr("Button")
    }

    Button {
        id: button4
        x: 217
        y: 299
        text: qsTr("Button")
    }
}
