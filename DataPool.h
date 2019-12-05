#ifndef DATAPOOL_H
#define DATAPOOL_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QString>
#include <QtCore/QFile>

#include "LockHelper.h"

class DataPool : public QObject
{
Q_OBJECT
    Q_PROPERTY(QString logFile READ logFile WRITE setlogFile NOTIFY logFileChanged)
    Q_PROPERTY(int sampleLength READ sampleLength WRITE setsampleLength NOTIFY sampleLengthChanged)
public:
    DataPool();
    Q_INVOKABLE void setSensorValues(double paX, double paY, double paZ);
    Q_INVOKABLE void setPosition(double longitude, double latitude);
    Q_INVOKABLE void startLogging();
    Q_INVOKABLE void stopLogging();

    static void registerMetaData();
private:
    QString logFile();
    void setlogFile(QString paData);
    int sampleLength();
    void setsampleLength(int paLength);

    double meX;
    double meY;
    double meZ;
    double meLongitude;
    double meLatitude;

    QTimer meLogTimer;
    QString meLogFileName;
    QFile meLogFile;
    int meSampleLength;

    QString meLogFilename;

    KeepAwakeHelper* meKeepAwakeHelper;

private slots:
    void logTimerFired();
signals:
    void logFileChanged();
    void sampleLengthChanged();
};

#endif // DATAPOOL_H
