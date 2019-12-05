#ifndef _WALLCLOCK_H
#define _WALLCLOCK_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtQuick/QtQuick>

class clWallClock : public QQuickPaintedItem
{
    Q_OBJECT
public:
    clWallClock(QQuickItem *paParent = 0);
protected:
    void paint(QPainter *painter);
private slots:
    void updateTime();
private:
    void initCoordinateSystem(QPainter *paPainter);

    QPixmap mePixmap;
    void drawWidget();

    QDateTime meDateTime;
};

#endif

