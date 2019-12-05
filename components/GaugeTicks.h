#ifndef _GAUGETICKS_H
#define _GAUGETICKS_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtQuick/QtQuick>

class clGaugeTicks : public QQuickPaintedItem
{
    Q_OBJECT
public:
    clGaugeTicks(QQuickItem *paParent = 0);
    Q_PROPERTY(QString tickColor READ getTickColor WRITE setTickColor)
    Q_PROPERTY(double majorTick READ getMajorTick WRITE setMajorTick)
    Q_PROPERTY(double minorTick READ getMinorTick WRITE setMinorTick)
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double minAngle READ getMinAngle WRITE setMinAngle)
    Q_PROPERTY(double maxAngle READ getMaxAngle WRITE setMaxAngle)
protected:
    QString getTickColor() const;
    void setTickColor(QString paColor);
    double getMajorTick() const;
    void setMajorTick(double paValue);
    double getMinorTick() const;
    void setMinorTick(double paValue);
    double getMinValue() const;
    void setMinValue(double paValue);
    double getMaxValue() const;
    void setMaxValue(double paValue);
    double getMinAngle() const;
    void setMinAngle(double paAngle);
    double getMaxAngle() const;
    void setMaxAngle(double paAngle);

    void paint(QPainter *painter);

private:
    bool checkConsistency() const;

    QString meTickColor;
    double meMajorTick, meMinorTick;
    double meMinValue, meMaxValue;
    double meMinAngle, meMaxAngle;
};

#endif

