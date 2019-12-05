#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>
#include <QtQml/QQmlEngine>
#include "DataPool.h"

#include "components/Meter.h"
#include "components/WallClock.h"
#include "components/bargraph.h"
#include "components/verticalBargraph.h"
#include "components/Arrow.h"

DataPool::DataPool()
{
    meX = 0.0;
    meY = 0.0;
    meZ = 0.0;
    meLatitude = 0.0;
    meLongitude = 0.0;

    meSampleLength = 0;

    meKeepAwakeHelper = nullptr;

    setlogFile("No logging active");

    connect(&meLogTimer, &QTimer::timeout, this, &DataPool::logTimerFired);
}

void DataPool::registerMetaData()
{
    // register custom CPP QML items
    /*qmlRegisterType<CameraItem>("com.bep.qmlcomponents", 1, 0, "CameraItem");
    qmlRegisterType<clAquaLabel>("com.bep.qmlcomponents", 1, 0, "AquaLabel");*/
    qmlRegisterType<BarGraph>("com.bep.qmlcomponents", 1, 0, "BarGraph");
    qmlRegisterType<VerticalBarGraph>("com.bep.qmlcomponents", 1, 0, "VerticalBarGraph");
//    qmlRegisterType<clGaugeScale>("com.bep.qmlcomponents", 1, 0, "GaugeScale");
//    qmlRegisterType<clGaugeTicks>("com.bep.qmlcomponents", 1, 0, "GaugeTicks");
//    qmlRegisterType<clGaugeZones>("com.bep.qmlcomponents", 1, 0, "GaugeZones");
//    qmlRegisterType<clGlossyLabel>("com.bep.qmlcomponents", 1, 0, "GlossyLabel");
//    qmlRegisterType<clGraph>("com.bep.qmlcomponents", 1, 0, "Graph");
    qmlRegisterType<clMeter>("com.bep.qmlcomponents", 1, 0, "Meter");
    qmlRegisterType<clWallClock>("com.bep.qmlcomponents", 1, 0, "WallClock");
    qmlRegisterType<clArrow>("com.bep.qmlcomponents", 1, 0, "Arrow");
}

void DataPool::setSensorValues(double paX, double paY, double paZ)
{
    meX = paX;
    meY = paY;
    meZ = paZ;
}

void DataPool::setPosition(double longitude, double latitude)
{
    meLongitude = longitude;
    meLatitude = latitude;
}

void DataPool::startLogging()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    qDebug() << "Writable path : " << path;

    QString fileName = path+"/"+QDateTime::currentDateTime().toString("Log_yyyy_MM_dd_hh_mm_ss.log");
    qDebug() << "Log file name is " << fileName;
    meLogFile.setFileName(fileName);
    QFileInfo loFI(meLogFile);
    qDebug() << "Opening file " << loFI.absoluteFilePath();
    if (meLogFile.open(QIODevice::WriteOnly))
    {
        meLogTimer.start(1000);
        meSampleLength = 0;
        setsampleLength(meSampleLength);
        setlogFile(loFI.absoluteFilePath());
    }
    if (meKeepAwakeHelper == nullptr)
    {
        meKeepAwakeHelper = new KeepAwakeHelper;
    }
}

void DataPool::stopLogging()
{
    meLogTimer.stop();
    meLogFile.close();
    meSampleLength = 0;
    setlogFile("No logging active");
    if (meKeepAwakeHelper)
    {
        delete meKeepAwakeHelper;
        meKeepAwakeHelper = nullptr;
    }
}

void DataPool::logTimerFired()
{
    qDebug() << "Log timer fired";
    meLogFile.write(QString("%1, %2, %3, %4, %5\n").arg(meX, 0, 'f', 2).arg(meY, 0, 'f', 2).arg(meZ, 0, 'f', 2)
                    .arg(meLongitude, 0, 'f', 6).arg(meLatitude, 0, 'f', 6)
                    .toLatin1());
    setsampleLength(meSampleLength+1);
}

QString DataPool::logFile()
{
    return meLogFileName;
}

void DataPool::setlogFile(QString paData)
{
   meLogFileName = paData;
   emit logFileChanged();
}

int DataPool::sampleLength()
{
    return meSampleLength;
}

void DataPool::setsampleLength(int paLength)
{
    if (meSampleLength != paLength)
    {
        meSampleLength = paLength;
        emit sampleLengthChanged();
    }
}
