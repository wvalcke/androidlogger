#ifndef _GAUGEZONES_H
#define _GAUGEZONES_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtQuick/QtQuick>

class clGaugeZones : public QQuickPaintedItem
{
    Q_OBJECT
public:
    clGaugeZones(QQuickItem *paParent = 0);
    Q_PROPERTY(QVariantList colorZones READ getColorZones WRITE setColorZones)
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double minAngle READ getMinAngle WRITE setMinAngle)
    Q_PROPERTY(double maxAngle READ getMaxAngle WRITE setMaxAngle)
protected:
    QVariantList getColorZones() const;
    void setColorZones(QVariantList paValues);
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
    struct tyColorZoneInfo
    {
        tyColorZoneInfo() {
            meStart = 0;
            meSpan = 1;
            meColor = Qt::red;
        }
        tyColorZoneInfo(double paStart, double paSpan, QColor paColor)
        {
            meStart = paStart;
            meSpan = paSpan;
            meColor = paColor;
        }
        double meStart;
        double meSpan;
        QColor meColor;
    };

    bool checkConsistency() const;

    double meMinValue, meMaxValue;
    double meMinAngle, meMaxAngle;
    QList<tyColorZoneInfo> meColorZones;
};

#endif

