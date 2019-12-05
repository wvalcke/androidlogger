#ifndef _METER_H
#define _METER_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtQuick/QtQuick>

class clMeter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_ENUMS(Status)
public:
    enum Status {
        Green, Orange, Red
    };
    clMeter(QQuickItem *paParent = 0);
    Q_PROPERTY(double target READ getTarget WRITE setTarget)
    Q_PROPERTY(double greenLowertolerance READ getGreenLowertolerance WRITE setGreenLowertolerance)
    Q_PROPERTY(double orangeLowertolerance READ getOrangeLowertolerance WRITE setOrangeLowertolerance)
    Q_PROPERTY(double greenUppertolerance READ getGreenUppertolerance WRITE setGreenUppertolerance)
    Q_PROPERTY(double orangeUppertolerance READ getOrangeUppertolerance WRITE setOrangeUppertolerance)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(Status status READ getStatus NOTIFY statusChanged)

protected:
    double getTarget() const;
    void setTarget(double paTarget);
    double getGreenLowertolerance() const;
    void setGreenLowertolerance(double paGreentolerance);
    double getOrangeLowertolerance() const;
    void setOrangeLowertolerance(double paOrangetolerance);
    double getGreenUppertolerance() const;
    void setGreenUppertolerance(double paGreentolerance);
    double getOrangeUppertolerance() const;
    void setOrangeUppertolerance(double paOrangetolerance);
    double getValue() const;
    void setValue(double paValue);
    Status getStatus() const;

    void paint(QPainter *painter);

signals:
    void statusChanged();
private:
    bool drawConstraintsFail();
    void initCoordinateSystem(QPainter *paPainter);
    void adjustZones();
    void checkStatus();

    QPixmap mePixmap;
    void drawWidget();

    double meTarget;
    double meGreenLowertolerance;
    double meOrangeLowertolerance;
    double meGreenUppertolerance;
    double meOrangeUppertolerance;
    double meValue;
    Status meStatus;

    double meLowerRedZone;
    double meUpperRedZone;
    bool meForceCompleteDraw;
};

#endif

