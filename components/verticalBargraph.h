#ifndef VERTICAL_BARGRAPH_H
#define VERTICAL_BARGRAPH_H

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtQuick/QtQuick>

class VerticalBarGraph : public QQuickPaintedItem
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_PROPERTY(double target READ getTarget WRITE setTarget)
    Q_PROPERTY(double greenLowertolerance READ getGreenLowertolerance WRITE setGreenLowertolerance)
    Q_PROPERTY(double orangeLowertolerance READ getOrangeLowertolerance WRITE setOrangeLowertolerance)
    Q_PROPERTY(double greenUppertolerance READ getGreenUppertolerance WRITE setGreenUppertolerance)
    Q_PROPERTY(double orangeUppertolerance READ getOrangeUppertolerance WRITE setOrangeUppertolerance)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(Status status READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(bool glossy READ getGlossy WRITE setGlossy)
public:
    enum Status {
        LowerGreen, UpperGreen, LowerOrange, UpperOrange, LowerRed, UpperRed
    };
    VerticalBarGraph(QQuickItem *parent = 0);

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
    void setGlossy(bool paGlossy);
    bool getGlossy() const;

    void paint(QPainter *painter);
signals:
    void statusChanged();
private:
    bool drawConstraintsFail();
    void adjustZones();
    void redrawPixmaps(QSize loSize);
    void checkStatus();

    double meTarget;
    double meGreenLowertolerance;
    double meOrangeLowertolerance;
    double meGreenUppertolerance;
    double meOrangeUppertolerance;
    double meValue;
    Status meStatus;
    bool meGlossy;

    double meLowerRedZone;
    double meUpperRedZone;
    QPixmap meRedbar;
    QPixmap meOrangebar;
    QPixmap meGreenbar;
    QPixmap meIndicatorbar;
    bool meForceCompleteRedraw;
};

#endif

