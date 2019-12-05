#include <iostream>
#include "WallClock.h"

using namespace std;

clWallClock::clWallClock(QQuickItem *paParent)
: QQuickPaintedItem(paParent)
{
    setWidth(150);
    setHeight(150);
    meDateTime = QDateTime::currentDateTime();
    QTimer *loTimer = new QTimer(this);
    loTimer->start(500);
    connect(loTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

void clWallClock::initCoordinateSystem(QPainter *paPainter)
{
    paPainter->scale(mePixmap.width()/240.0, mePixmap.height()/240.0);
    paPainter->translate(120, 120);
}

void clWallClock::drawWidget()
{
    QPainter loPainter(&mePixmap);
    loPainter.setRenderHint(QPainter::Antialiasing);
    loPainter.setRenderHint(QPainter::TextAntialiasing);
    initCoordinateSystem(&loPainter);

    QColor loRed(215, 0, 0);
    QRadialGradient loGradient1(QPointF(0,0), 135, QPointF(-27.5, 110));
    loGradient1.setColorAt(0.0, QColor(255, 255, 255));
    loGradient1.setColorAt(1.0, loRed);

    QRadialGradient loGradient2(QPointF(0, 0), 170, QPointF(57.5, 100));
    loGradient2.setColorAt(0.0, loRed);
    loGradient2.setColorAt(1.0, QColor(255, 255, 255));

    QRadialGradient loShield(QPointF(0, 0), 122, QPointF(-12, -15));
    loShield.setColorAt(0.0, Qt::white);
    loShield.setColorAt(0.5, QColor(240, 240, 240));
    loShield.setColorAt(1.0, QColor(215, 215, 215));

    QPen loPen(Qt::black);
    loPen.setWidth(2);
    loPainter.setPen(loPen);

    loPainter.setBrush(loGradient1);
    loPainter.drawEllipse(-116, -116, 232, 232);
    loPainter.setPen(Qt::NoPen);
    loPainter.setBrush(loGradient2);
    loPainter.drawEllipse(-109, -109, 218, 218);

    loPainter.setPen(loPen);
    loPainter.setBrush(loShield);
    loPainter.drawEllipse(-102, -102, 204, 204);

    /* draw the hour bullets */
    loPainter.setBrush(Qt::black);
    for (int loCounter = 0; loCounter < 12; loCounter++)
    {
        loPainter.save();
        loPainter.rotate(loCounter*30);
        loPainter.drawEllipse(94, -2, 4, 4);
        loPainter.restore();
    }

    loPainter.setPen(loPen);
    /* draw the minutes lines */
    for (int loCounter = 0; loCounter < 60; loCounter++)
    {
        if ((loCounter % 5) != 0) // we are not on an hour bullet
        {
            loPainter.save();
            loPainter.rotate(loCounter*6);
            loPainter.drawLine(94, 0, 97, 0);
            loPainter.restore();
        }
    }

    QFont loFont = QFont();
    loFont.setPixelSize(23);
    loPainter.setFont(loFont);
    /* draw the numbers on the clock */
    for (int loNumber = 1; loNumber <= 12; loNumber++)
    {
        QString loHour = QString("%1").arg(loNumber);
        QSize loSize = loPainter.fontMetrics().size(Qt::TextSingleLine, loHour);
        loPainter.save();
        loPainter.rotate(loNumber*30-90);
        loPainter.translate(75, 0);
        loPainter.rotate(-loNumber*30+90);
        loPainter.drawText(QPointF(loSize.width()/-2.0, loSize.height()/4.0), loHour);
        loPainter.restore();
    }
    //mePixmap.toImage().save("pixmap.png");
}

void clWallClock::paint(QPainter *paPainter)
{
    // Check if the size has changed
    QRectF loBoundRect = boundingRect();
    QSize loSize = loBoundRect.size().toSize();
    if (loSize != mePixmap.size())
    {
        //qDebug() << "Drawing pixmap " << loSize;
        mePixmap = QPixmap(loSize);
        mePixmap.fill(Qt::transparent);
        drawWidget();
    }
    static const int hourHand[8] = { -2, 18, 2, 18, 2, -60, -2, -60 };
    static const int minuteHand[8] = { -2, 28, 2, 28, 2, -80, -2, -80 };
    static const int secondHand[12] = {-1, 0, -1, -90, 1,-90, 1, 0, 4, 35, -4, 35};

    paPainter->save();
    paPainter->setRenderHint(QPainter::Antialiasing);
    paPainter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    paPainter->drawPixmap(0, 0, mePixmap);

    initCoordinateSystem(paPainter);

    QTime loTime = meDateTime.time();
    /* draw the hour hand */
    paPainter->setPen(Qt::NoPen);
    paPainter->setBrush(Qt::black);
    paPainter->save();
    paPainter->rotate(30.0*(loTime.hour()+loTime.minute()/60.0));
    paPainter->drawConvexPolygon(QPolygon(4, hourHand));
    paPainter->restore();

    /* draw the minute hand */
    paPainter->save();
    paPainter->rotate(6.0*(loTime.minute()+loTime.second()/60.0));
    paPainter->drawConvexPolygon(QPolygon(4, minuteHand));
    paPainter->restore();

    /* draw the second hand */
    paPainter->setBrush(Qt::red);
    paPainter->save();
    paPainter->rotate(6.0*loTime.second());
    paPainter->drawConvexPolygon(QPolygon(6, secondHand));
    paPainter->restore();
    paPainter->drawEllipse(-5, -5, 10, 10);

    paPainter->restore();
}

void clWallClock::updateTime()
{
    if (isVisible())
    {
        meDateTime = QDateTime::currentDateTime();
        update();
    }
}

