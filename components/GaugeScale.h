#ifndef _GAUGESCALE_H
#define _GAUGESCALE_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtQuick/QtQuick>

class clGaugeScale : public QQuickPaintedItem
{
    Q_OBJECT
public:
    clGaugeScale(QQuickItem *paParent = 0);
    Q_PROPERTY(QString scaleColor READ getScaleColor WRITE setScaleColor)
    Q_PROPERTY(int scalePrecision READ getScalePrecision WRITE setScalePrecision)
    Q_PROPERTY(int scaleFontSize READ getScaleFontSize WRITE setScaleFontSize)
    Q_PROPERTY(QList<qreal> tickList READ getTickList WRITE setTickList)
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double minAngle READ getMinAngle WRITE setMinAngle)
    Q_PROPERTY(double maxAngle READ getMaxAngle WRITE setMaxAngle)
protected:
    QString getScaleColor() const;
    void setScaleColor(QString paColor);
    int getScalePrecision() const;
    void setScalePrecision(int paScalePrecision);
    int getScaleFontSize() const;
    void setScaleFontSize(int paScaleFontSize);
    QList<qreal> getTickList() const;
    void setTickList(QList<qreal> paTickList);
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

    QString meScaleColor;
    int meScalePrecision;
    int meScaleFontSize;
    QList<qreal> meTickList;
    double meMinValue, meMaxValue;
    double meMinAngle, meMaxAngle;
};

#endif

