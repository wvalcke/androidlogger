import QtQuick 2.0

Item {

    property string skin: "skinblackA"
    property real minValue: -100
    property real maxValue: 100
    property real value: 0
    property real minAngle: -135
    property real maxAngle: 135

    id: main

    width: 200
    height: 200

    Image {
        anchors.fill: parent
        sourceSize.height: parent.height
        sourceSize.width: parent.width
        smooth: true
        source: "images/gauge/"+main.skin+"/background.svg"
    }

    Image {
        anchors.fill: parent
        sourceSize.height: parent.height
        sourceSize.width: parent.width
        smooth: true
        source: "images/gauge/"+main.skin+"/needle.svg"
        rotation: {
            (value-minValue)/(maxValue-minValue)*(maxAngle-minAngle)+minAngle
        }
        z: 1
    }

    Image {
        anchors.fill: parent
        sourceSize.height: parent.height
        sourceSize.width: parent.width
        smooth: true
        source: "images/gauge/"+main.skin+"/overlay.svg"
        z: 1
    }

}
