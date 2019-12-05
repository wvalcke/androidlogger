#include <iostream>
#include "Meter.h"

using namespace std;

clMeter::clMeter(QQuickItem *paParent) : QQuickPaintedItem(paParent)
{
    meValue = 0;
    meTarget = 0;
    meGreenLowertolerance = 50;
    meOrangeLowertolerance = 30;
    meGreenUppertolerance = 50;
    meOrangeUppertolerance = 30;
    meForceCompleteDraw = false;

    setWidth(150);
    setHeight(150);

    adjustZones();
}

double clMeter::getTarget() const
{
    return meTarget;
}

void clMeter::setTarget(double paTarget)
{
    meTarget = paTarget;
    checkStatus();
    adjustZones();
    update();
}

double clMeter::getGreenLowertolerance() const
{
    return meGreenLowertolerance;
}

void clMeter::setGreenLowertolerance(double paGreentolerance)
{
    if (paGreentolerance > 0)
    {
        meGreenLowertolerance = paGreentolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double clMeter::getOrangeLowertolerance() const
{
    return meOrangeLowertolerance;
}

void clMeter::setOrangeLowertolerance(double paOrangetolerance)
{
    if (paOrangetolerance >= 0)
    {
        meOrangeLowertolerance = paOrangetolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double clMeter::getGreenUppertolerance() const
{
    return meGreenUppertolerance;
}

void clMeter::setGreenUppertolerance(double paGreentolerance)
{
    if (paGreentolerance > 0)
    {
        meGreenUppertolerance = paGreentolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double clMeter::getOrangeUppertolerance() const
{
    return meOrangeUppertolerance;
}

void clMeter::setOrangeUppertolerance(double paOrangetolerance)
{
    if (paOrangetolerance >= 0)
    {
        meOrangeUppertolerance = paOrangetolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double clMeter::getValue() const
{
    return meValue;
}

void clMeter::setValue(double paValue)
{
    meValue = paValue;
    checkStatus();
    adjustZones();
    update();
}

void clMeter::checkStatus()
{
    Status loOldStatus = meStatus;
    if (meValue >= meTarget) // we are at the right side with the actual value
    {
        if (fabs(meTarget - meValue) <= meGreenUppertolerance) 
        {
            meStatus = Green;
        }
        else if (fabs(meTarget-meValue) <= (meGreenUppertolerance+meOrangeUppertolerance))
        {
            meStatus = Orange;
        }
        else
        {
            meStatus = Red;
        }
    }
    else // we are at the left side with the actual value
    {
        if (fabs(meTarget - meValue) <= meGreenLowertolerance) 
        {
            meStatus = Green;
        }
        else if (fabs(meTarget-meValue) <= (meGreenLowertolerance+meOrangeLowertolerance))
        {
            meStatus = Orange;
        }
        else
        {
            meStatus = Red;
        }
    }
    if (loOldStatus != meStatus)
    {
        emit statusChanged();
    }
}

clMeter::Status clMeter::getStatus() const
{
    return meStatus;
}

bool clMeter::drawConstraintsFail()
{
    if (meGreenLowertolerance <= 0 || meGreenUppertolerance <= 0)
    {
        return true;
    }
    if (meOrangeLowertolerance < 0 || meOrangeUppertolerance < 0)
    {
        return true;
    }
    return false;
}

void clMeter::initCoordinateSystem(QPainter *paPainter)
{
    paPainter->scale(mePixmap.width()/336.0, mePixmap.height()/336.0);
    paPainter->translate(168, 168);
}

void clMeter::drawWidget()
{
    static const int scaleTriangle[6] = { 141,-6,141,6,129,0};

    mePixmap.fill(Qt::transparent);
    QPainter loPainter(&mePixmap);
    loPainter.setRenderHint(QPainter::Antialiasing);
    initCoordinateSystem(&loPainter);

    QRadialGradient loGradient1(QPointF(0,0), 180, QPointF(-35, 145));
    loGradient1.setColorAt(0.0, QColor(250, 250, 250));
    loGradient1.setColorAt(1.0, QColor(20, 20, 20));

    QRadialGradient loGradient2(QPointF(0, 0), 225, QPointF(76.5, 135));
    loGradient2.setColorAt(0.0, QColor(10, 10, 10));
    loGradient2.setColorAt(1.0, QColor(250, 250, 250));

    QRadialGradient loShield(QPointF(0, 0), 182, QPointF(-12, -15));
    loShield.setColorAt(0.0, Qt::white);
    loShield.setColorAt(0.5, QColor(240, 240, 240));
    loShield.setColorAt(1.0, QColor(215, 215, 215));

    QPen loPen(Qt::black);
    loPen.setWidth(2);
    loPainter.setPen(loPen);

    loPainter.setBrush(loGradient1);
    loPainter.drawEllipse(-162, -162, 324, 324);
    loPainter.setPen(Qt::NoPen);
    loPainter.setBrush(loGradient2);
    loPainter.drawEllipse(-152, -152, 304, 304);

    loPainter.setPen(loPen);
    loPainter.setBrush(loShield);
    loPainter.drawEllipse(-142, -142, 284, 284);

    double loGreenUpperValue = meGreenUppertolerance/(meGreenUppertolerance+meOrangeUppertolerance+meUpperRedZone)*100;
    double loOrangeUpperValue = meOrangeUppertolerance/(meGreenUppertolerance+meOrangeUppertolerance+meUpperRedZone)*100;
    double loRedUpperValue = 100-loGreenUpperValue-loOrangeUpperValue;
    double loGreenLowerValue = meGreenLowertolerance/(meGreenLowertolerance+meOrangeLowertolerance+meLowerRedZone)*100;
    double loOrangeLowerValue = meOrangeLowertolerance/(meGreenLowertolerance+meOrangeLowertolerance+meLowerRedZone)*100;
    double loRedLowerValue = 100-loGreenLowerValue-loOrangeLowerValue;

    loPainter.setBrush(Qt::red);
    loPainter.setPen(Qt::NoPen);
    loPainter.drawPie(QRect(-141,-141,282,282), -30*16, 240*16);
    loPainter.setBrush(QColor(0, 200, 0));
    loPainter.drawPie(QRect(-141,-141,282,282), -30*16+240*16*(loRedUpperValue+loOrangeUpperValue)/100.0/2.0, 120*16*(loGreenUpperValue+loGreenLowerValue)/100.0);
    loPainter.setBrush(QColor ("#e7bb23"));
    loPainter.drawPie(QRect(-141,-141,282,282), -30*16+240*16*loRedUpperValue/100.0/2.0, 240*16*loOrangeUpperValue/100.0/2.0);
    loPainter.drawPie(QRect(-141,-141,282,282), -30*16+240*16-(240*16*(loRedLowerValue+loOrangeLowerValue)/100.0/2.0), 240*16*loOrangeLowerValue/100.0/2.0);

    loPainter.setBrush(loShield);
    loPainter.drawEllipse(-119, -119, 238, 238);

    loPainter.save();
    loPainter.rotate(-210.0);
    loPainter.setBrush(Qt::black);
    loPainter.setPen(loPen);
    for (int loCounter = 0; loCounter < 33; loCounter++)
    {
        loPainter.setPen(loPen);
        loPainter.save();
        loPainter.rotate(loCounter*7.5);
        if (loCounter % 4)
        {
            int loLineLength = 10;
            if (loCounter % 2)
            {
                loLineLength = 5;
            }
            loPainter.drawLine(140, 0, 140-loLineLength, 0);
        }
        else
        {
            loPainter.setPen(Qt::NoPen);
            loPainter.drawConvexPolygon(QPolygon(3, scaleTriangle));
        }
        loPainter.restore();
    }

    loPainter.restore();
    meForceCompleteDraw = false;
}

void clMeter::paint(QPainter *paPainter)
{
    if (drawConstraintsFail())
    {
        return;
    }
    // Check if the size has changed
    QRectF loBoundRect = boundingRect();
    QSize loSize = loBoundRect.size().toSize();
    if (loSize != mePixmap.size())
    {
        mePixmap = QPixmap(loSize);
        drawWidget();
    }
    if (meForceCompleteDraw)
    {
        drawWidget();
    }

    paPainter->save();
    paPainter->setRenderHint(QPainter::Antialiasing);
    paPainter->setRenderHint(QPainter::SmoothPixmapTransform);
    paPainter->drawPixmap(0, 0, mePixmap);

    initCoordinateSystem(paPainter);

    static const int hand[12] = {-4, 0, -1, 129, 1, 129, 4, 0, 8,-50, -8,-50};

    QPainterPath hand_path;
    hand_path.moveTo(QPointF(hand[0],hand[1]));

    for (int i=2;i<10;i+=2)
        hand_path.lineTo(hand[i],hand[i+1]);

    hand_path.cubicTo ( 8.1,-51.0, 5.0,-48.0,   0.0,-48.0);
    hand_path.cubicTo(  -5.0,-48.0, -8.1,-51.0, -8.0,-50.0);

    paPainter->setPen(Qt::NoPen);
    paPainter->setBrush(Qt::black);

    paPainter->save();

    paPainter->rotate(-180);

    double loNeedleValue;
    if (meValue >= meTarget)
    {
        loNeedleValue = 100 * (meValue - meTarget) / (meGreenUppertolerance + meOrangeUppertolerance + meUpperRedZone); 
    }
    else
    {
        loNeedleValue = 100 * (meValue - meTarget) / (meGreenLowertolerance + meOrangeLowertolerance + meLowerRedZone); 
    }

    paPainter->rotate(120*loNeedleValue/100.0);
    paPainter->drawPath(hand_path);
    paPainter->drawEllipse(-10, -10, 20, 20);

    paPainter->restore();

    paPainter->restore();
}

void clMeter::adjustZones()
{
    double loPrevLowerRedZone = meLowerRedZone;
    double loPrevUpperRedZone = meUpperRedZone;

    meLowerRedZone = 0.2*(meGreenLowertolerance+meOrangeLowertolerance);
    meUpperRedZone = 0.2*(meGreenUppertolerance+meOrangeUppertolerance);

    double scaleFactor = 1;

    if (meValue >= meTarget) // we're at the right side of the target
    {
        while (true) 
        {
            double loInRedZone = qAbs(meTarget-meValue)-meGreenUppertolerance-meOrangeUppertolerance;
            if (loInRedZone > 2.0/3.0*meUpperRedZone)
            {
                meUpperRedZone *= 2;
                scaleFactor *= 2;
            }
            else
            {
                break;
            }
        }
        if (loPrevUpperRedZone != meUpperRedZone)
        {
            meForceCompleteDraw = true;
        }
        meLowerRedZone = scaleFactor*meLowerRedZone;
    }
    else // we're at the left side of the target
    {
        while (true) 
        {
            double loInRedZone = qAbs(meTarget-meValue)-meGreenLowertolerance-meOrangeLowertolerance;
            if (loInRedZone > 2.0/3.0*meLowerRedZone)
            {
                meLowerRedZone *= 2;
                scaleFactor *= 2;
            }
            else
            {
                break;
            }
        }
        if (loPrevLowerRedZone != meLowerRedZone)
        {
            meForceCompleteDraw = true;
        }
        meUpperRedZone = scaleFactor*meUpperRedZone;
    }
}

