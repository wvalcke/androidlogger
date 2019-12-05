import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtSensors 5.9
import QtPositioning 5.12
import com.bep.qmlcomponents 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Item {
        id: root
        property string longitude: "Unknown"
        property string latitude: "Unknown"
        property double accelX: 0
        property double accelY: 0
        property double accelZ: 0
        property string speed: "Unknown"
        property double speedValue: 0.0
        anchors.fill: parent

        Component.onCompleted: {
            console.log("Position state valid "+src.valid)
        }

        Accelerometer {
            id: accel
            dataRate: 15
            active: true

            onReadingChanged: {
                DataPool.setSensorValues(accel.reading.x, accel.reading.y, accel.reading.z)
                root.accelX = accel.reading.x
                root.accelY = accel.reading.y
                root.accelZ = accel.reading.z
            }
        }

        PositionSource {
            id: src
            updateInterval: 1000
            preferredPositioningMethods: PositionSource.SatellitePositioningMethods
            active: true

            onPositionChanged: {
                var coord = src.position.coordinate;
                if (coord.isValid)
                {
                    DataPool.setPosition(coord.longitude, coord.latitude)
                    root.longitude = coord.longitude.toFixed(6)
                    root.latitude = coord.latitude.toFixed(6)
                }
                else
                {
                    root.longitude = "Unknown"
                    root.latitude = "Unknown"
                }
                if (position.speedValid)
                {
                    root.speedValue = (position.speed*3.6).toFixed(1)
                    root.speed = root.speedValue
                }
                else
                {
                    root.speed = "Unknown"
                    root.speedValue = 0.0
                }
            }
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            spacing: 5

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: "Logger application"
                font.pixelSize: 20
                font.bold: true
            }
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: false

                Button {
                    text : "Start logging"
                    onClicked: DataPool.startLogging()
                    Layout.fillWidth: true
                }
                Button {
                    text : "Stop logging"
                    onClicked: DataPool.stopLogging()
                    Layout.fillWidth: true
                }
                Text {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Loggin to file : "+ DataPool.logFile
                    wrapMode: Text.WrapAnywhere
                }
            }
            Text {
                Layout.fillWidth: true
                text: "Log counter : " + DataPool.sampleLength
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 30

                        ColumnLayout {
                            anchors.fill: parent
                            Text {
                                text: "Acceleration sensor data"
                                Layout.alignment: Qt.AlignHCenter
                            }

                            RowLayout {
                                Layout.fillHeight: true
                                Layout.fillWidth: true

                                ColumnLayout {
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 1
                                    SimpleGauge {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: height
                                        height: width
                                        minValue: -15
                                        maxValue: 15
                                        value: root.accelX
                                        GaugeScale {
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: parent.width*0.9
                                            height: parent.height*0.9
                                            minValue: -15
                                            maxValue: 15
                                            minAngle: -135
                                            maxAngle: 135
                                            scaleColor: "white"
                                            scaleFontSize: scaleTextXaccel.font.pixelSize*1.5
                                            scalePrecision: 1
                                            tickList: [-15, -10, -5, 0, 5, 10, 15]
                                        }

                                        Text {
                                            id: scaleTextXaccel
                                            anchors.bottom: parent.bottom
                                            anchors.bottomMargin: parent.height*0.1
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            text: root.accelX.toFixed(2)
                                            color: "white"
                                        }
                                    }
                                    Text {
                                        text: "X acceleration"
                                        Layout.alignment: Qt.AlignHCenter
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 1
                                    SimpleGauge {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: height
                                        height: width
                                        minValue: -15
                                        maxValue: 15
                                        value: root.accelY
                                        GaugeScale {
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: parent.width*0.9
                                            height: parent.height*0.9
                                            minValue: -15
                                            maxValue: 15
                                            minAngle: -135
                                            maxAngle: 135
                                            scaleColor: "white"
                                            scaleFontSize: scaleTextXaccel.font.pixelSize*1.5
                                            scalePrecision: 1
                                            tickList: [-15, -10, -5, 0, 5, 10, 15]
                                        }

                                        Text {
                                            anchors.bottom: parent.bottom
                                            anchors.bottomMargin: parent.height*0.1
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            text: root.accelY.toFixed(2)
                                            color: "white"
                                        }
                                    }
                                    Text {
                                        text: "Y acceleration"
                                        Layout.alignment: Qt.AlignHCenter
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 1
                                    SimpleGauge {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: height
                                        height: width
                                        minValue: -15
                                        maxValue: 15
                                        value: root.accelZ
                                        GaugeScale {
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: parent.width*0.9
                                            height: parent.height*0.9
                                            minValue: -15
                                            maxValue: 15
                                            minAngle: -135
                                            maxAngle: 135
                                            scaleColor: "white"
                                            scaleFontSize: scaleTextXaccel.font.pixelSize*1.5
                                            scalePrecision: 1
                                            tickList: [-15, -10, -5, 0, 5, 10, 15]
                                        }

                                        Text {
                                            anchors.bottom: parent.bottom
                                            anchors.bottomMargin: parent.height*0.1
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            text: root.accelZ.toFixed(2)
                                            color: "white"
                                        }
                                    }
                                    Text {
                                        text: "Z acceleration"
                                        Layout.alignment: Qt.AlignHCenter
                                    }
                                }
                            }
                        }

                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 30

                        ColumnLayout {
                            anchors.fill: parent
                            RowLayout {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                Text {
                                    text: "X : "
                                    Layout.alignment: Qt.AlignVCenter
                                }
                                BarGraph {
                                    Layout.alignment: Qt.AlignVCenter
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    value: root.accelX
                                    target: 0
                                    greenLowertolerance: 5
                                    greenUppertolerance: 5
                                    orangeLowertolerance: 2
                                    orangeUppertolerance: 2
                                }

                            }
                            RowLayout {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                Text {
                                    text: "Y : "
                                    Layout.alignment: Qt.AlignVCenter
                                }
                                BarGraph {
                                    Layout.alignment: Qt.AlignVCenter
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    value: root.accelY
                                    target: 0
                                    greenLowertolerance: 5
                                    greenUppertolerance: 5
                                    orangeLowertolerance: 2
                                    orangeUppertolerance: 2
                                }
                            }
                            RowLayout {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                Text {
                                    text: "Z : "
                                    Layout.alignment: Qt.AlignVCenter
                                }
                                BarGraph {
                                    Layout.alignment: Qt.AlignVCenter
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    value: root.accelZ
                                    target: 0
                                    greenLowertolerance: 5
                                    greenUppertolerance: 5
                                    orangeLowertolerance: 2
                                    orangeUppertolerance: 2
                                }
                            }
                        }
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 30

                        RowLayout {
                            anchors.fill: parent
                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    Text {
                                        text: "GPS coordinates"
                                        font.bold: true
                                    }
                                    Text {
                                        text : "Longitude : " + root.longitude
                                    }
                                    Text {
                                        text: "Latitude : " + root.latitude
                                    }
                                }
                            }

                            Item {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    Text {
                                        Layout.alignment: Qt.AlignHCenter
                                        text: "Speed"
                                        font.bold: true
                                    }

                                    SimpleGauge {
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: height
                                        Layout.alignment: Qt.AlignHCenter
                                        minValue: 0
                                        maxValue: 220
                                        value: root.speedValue
                                        GaugeScale {
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: parent.width*0.9
                                            height: parent.height*0.9
                                            minValue: 0
                                            maxValue: 220
                                            minAngle: -135
                                            maxAngle: 135
                                            scaleColor: "white"
                                            scaleFontSize: speedScale.font.pixelSize*1.5
                                            scalePrecision: 0
                                            tickList: [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220]
                                        }

                                        Text {
                                            id: speedScale
                                            anchors.bottom: parent.bottom
                                            anchors.bottomMargin: parent.height*0.1
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            text: root.speedValue.toFixed(1)
                                            color: "white"
                                        }
                                    }


                                    Text {
                                        text: "Speed (km/h) : " + root.speed
                                    }
                                    Item {
                                        height: 10
                                    }
                                }
                            }
                        }
                    }
                }

            /*    ColumnLayout {
                    anchors.fill: parent
                    spacing: 0



                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredHeight: 30
                        Rectangle {
                            anchors.fill: parent
                            z: -1
                            color: "purple"
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            Text {
                                Layout.fillWidth: true
                                text: "GPS data"
                                font.pixelSize: 30
                                font.bold: true
                            }

                            Text {
                                text: "Longitude : "+ root.longitude
                                font.pixelSize: 20
                                Layout.fillWidth: true
                            }
                            Text {
                                text: "Latitude : "+ root.latitude
                                font.pixelSize: 20
                                Layout.fillWidth: true
                            }
                            Text {
                                text: "Speed (km/h) : "+ root.speed
                                font.pixelSize: 20
                                Layout.fillWidth: true
                            }
                        }
                    }
                }*/
            }
        }
    }
}
