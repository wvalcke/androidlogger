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
                    root.speed = (position.speed*3.6).toFixed(1)
                }
                else
                {
                    root.speed = "Unknown"
                }
            }
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10

            Text {
                Layout.fillWidth: true
                text: "Logger application"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 30
                font.bold: true
            }

            Button {
                text : "Start logging"
                onClicked: DataPool.startLogging()
                Layout.fillWidth: true
            }

            Text {
                Layout.fillWidth: true
                text: "Loggin to file : "+ DataPool.logFile
                wrapMode: Text.WrapAnywhere
            }
            Text {
                Layout.fillWidth: true
                text: "Log counter : " + DataPool.sampleLength
            }

            Button {
                text : "Stop logging"
                onClicked: DataPool.stopLogging()
                Layout.fillWidth: true
            }

            Item {
                height: 10
                Layout.fillWidth: true
            }

            Text {
                Layout.fillWidth: true
                text: "Sensor data"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 30
                font.bold: true
            }

            RowLayout {
                Layout.preferredHeight: root.height*0.3
                SimpleGauge {
                    Layout.fillWidth: true
                    height: width
                }
                SimpleGauge {
                    Layout.fillWidth: true
                    height: width
                }
                SimpleGauge {
                    Layout.fillWidth: true
                    height: width
                }
            }

            RowLayout {
                Text {
                    text: "X : "
                    Layout.alignment: Qt.AlignVCenter
                }

                BarGraph {
                    height: 30
                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: 10
                    Layout.fillWidth: true
                    value: root.accelX
                    target: 0
                    greenLowertolerance: 5
                    greenUppertolerance: 5
                    orangeLowertolerance: 2
                    orangeUppertolerance: 2
                }
            }

            RowLayout {
                Text {
                    text: "Y : "
                    Layout.alignment: Qt.AlignVCenter
                }

                BarGraph {
                    height: 30
                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: 10
                    Layout.fillWidth: true
                    value: root.accelY
                    target: 0
                    greenLowertolerance: 5
                    greenUppertolerance: 5
                    orangeLowertolerance: 2
                    orangeUppertolerance: 2

                }
            }

            RowLayout {
                Text {
                    text: "Z : "
                    Layout.alignment: Qt.AlignVCenter
                }

                BarGraph {
                    height: 30
                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: 10
                    Layout.fillWidth: true
                    value: root.accelZ
                    target: 0
                    greenLowertolerance: 5
                    greenUppertolerance: 5
                    orangeLowertolerance: 2
                    orangeUppertolerance: 2

                }
            }

            Item {
                height: 10
                Layout.fillWidth: true
            }

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
}
