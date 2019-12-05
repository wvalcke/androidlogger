#include <iostream>
#include "verticalBargraph.h"
#include <QtGui/QPainter>

VerticalBarGraph::VerticalBarGraph(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    meValue = 0;
    meTarget = 0;
    meGreenLowertolerance = 50;
    meOrangeLowertolerance = 30;
    meGreenUppertolerance = 50;
    meOrangeUppertolerance = 30;
    meStatus = LowerGreen;
    meGlossy = true;
    meForceCompleteRedraw = false;
    setWidth(50);
    setHeight(200);

    adjustZones();
}

double VerticalBarGraph::getTarget() const
{
    return meTarget;
}

void VerticalBarGraph::setTarget(double paTarget)
{
    meTarget = paTarget;
    checkStatus();
    adjustZones();
    update();
}

double VerticalBarGraph::getGreenLowertolerance() const
{
    return meGreenLowertolerance;
}

void VerticalBarGraph::setGreenLowertolerance(double paGreentolerance)
{
    if (paGreentolerance > 0)
    {
        meGreenLowertolerance = paGreentolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double VerticalBarGraph::getOrangeLowertolerance() const
{
    return meOrangeLowertolerance;
}

void VerticalBarGraph::setOrangeLowertolerance(double paOrangetolerance)
{
    if (paOrangetolerance >= 0)
    {
        meOrangeLowertolerance = paOrangetolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double VerticalBarGraph::getGreenUppertolerance() const
{
    return meGreenUppertolerance;
}

void VerticalBarGraph::setGreenUppertolerance(double paGreentolerance)
{
    if (paGreentolerance > 0)
    {
        meGreenUppertolerance = paGreentolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double VerticalBarGraph::getOrangeUppertolerance() const
{
    return meOrangeUppertolerance;
}

void VerticalBarGraph::setOrangeUppertolerance(double paOrangetolerance)
{
    if (paOrangetolerance >= 0)
    {
        meOrangeUppertolerance = paOrangetolerance;
        checkStatus();
        adjustZones();
        update();
    }
}

double VerticalBarGraph::getValue() const
{
    return meValue;
}

void VerticalBarGraph::setValue(double paValue)
{
    meValue = paValue;
    checkStatus();
    adjustZones();
    update();
}

bool VerticalBarGraph::getGlossy() const
{
    return meGlossy;
}

void VerticalBarGraph::setGlossy(bool paGlossy)
{
    if (meGlossy != paGlossy)
    {
        meForceCompleteRedraw = true;
        update();
        meGlossy = paGlossy;
    }
}

void VerticalBarGraph::checkStatus()
{
    Status loOldStatus = meStatus;
    if (meValue >= meTarget) // we are at the right side with the actual value
    {
        if (fabs(meTarget - meValue) <= meGreenUppertolerance) 
        {
            meStatus = UpperGreen;
        }
        else if (fabs(meTarget-meValue) <= (meGreenUppertolerance+meOrangeUppertolerance))
        {
            meStatus = UpperOrange;
        }
        else
        {
            meStatus = UpperRed;
        }
    }
    else // we are at the left side with the actual value
    {
        if (fabs(meTarget - meValue) <= meGreenLowertolerance) 
        {
            meStatus = LowerGreen;
        }
        else if (fabs(meTarget-meValue) <= (meGreenLowertolerance+meOrangeLowertolerance))
        {
            meStatus = LowerOrange;
        }
        else
        {
            meStatus = LowerRed;
        }
    }
    if (loOldStatus != meStatus)
    {
        emit statusChanged();
    }
}

VerticalBarGraph::Status VerticalBarGraph::getStatus() const
{
    return meStatus;
}

bool VerticalBarGraph::drawConstraintsFail()
{
    if (meGreenUppertolerance <= 0 || meGreenLowertolerance <= 0)
    {
        return true;
    }
    if (meOrangeUppertolerance < 0 || meOrangeLowertolerance < 0)
    {
        return true;
    }
    return false;
}

void VerticalBarGraph::adjustZones()
{
    meLowerRedZone = 0.2 * (meGreenLowertolerance + meOrangeLowertolerance);
    meUpperRedZone = 0.2 * (meGreenUppertolerance + meOrangeUppertolerance);
    double scaleFactor = 1;

    if (meValue >= meTarget) // We are at the right side of the VerticalBarGraph
    {
        while (true)
        {
            double loInRedZone = qAbs(meTarget - meValue) - meGreenUppertolerance - meOrangeUppertolerance;
            if (loInRedZone > 2.0 / 3.0 * meUpperRedZone)
            {
                meUpperRedZone *= 2;
                scaleFactor *= 2;
            }
            else
            {
                break;
            }
        }
        meLowerRedZone = scaleFactor*meLowerRedZone;
    }
    else // we are at the left side of the VerticalBarGraph
    {
        while (true)
        {
            double loInRedZone = qAbs(meTarget - meValue) - meGreenLowertolerance - meOrangeLowertolerance;
            if (loInRedZone > 2.0 / 3.0 * meLowerRedZone)
            {
                meLowerRedZone *= 2;
                scaleFactor *= 2;
            }
            else
            {
                break;
            }
        }
        meUpperRedZone = scaleFactor*meUpperRedZone;
    }
}

void VerticalBarGraph::redrawPixmaps(QSize paSize)
{
    int loWidth = paSize.width();
    int loHeight = paSize.height();
    meRedbar = QPixmap(loWidth, loHeight);
    meOrangebar = QPixmap(loWidth, loHeight);
    meGreenbar = QPixmap(loWidth, loHeight);
    meIndicatorbar = QPixmap(loWidth, loHeight);

    QPainter loPainter(&meGreenbar);

    loPainter.setWindow(0, -100, 50, 200);
    loPainter.setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient loGreenGradient(0, 0, 50, 0);
    QColor loGreen("#17d531");
    loGreenGradient.setColorAt(0.0, loGreen);
    if (meGlossy)
    {
        loGreenGradient.setColorAt(0.5, loGreen.lighter(200)); 
    }
    loGreenGradient.setColorAt(1.0, loGreen);
    loPainter.setBrush(loGreenGradient);
    loPainter.setPen(Qt::NoPen);

    loPainter.drawRect(QRectF(0, -100, 50, 200));
    loPainter.end();

    loPainter.begin(&meOrangebar);
    loPainter.setWindow(0, -100, 50, 200);
    loPainter.setRenderHint(QPainter::Antialiasing, true);
    loPainter.setPen(Qt::NoPen);

    QLinearGradient loOrangeGradient(0, 0, 50, 0);
    QColor loOrange("#e7bb23");
    loOrangeGradient.setColorAt(0.0, loOrange);
    if (meGlossy)
    {
        loOrangeGradient.setColorAt(0.5, loOrange.lighter(170)); 
    }
    loOrangeGradient.setColorAt(1.0, loOrange);

    loPainter.setBrush(loOrangeGradient);
    loPainter.drawRect(QRectF(0, -100, 50, 200));
    loPainter.end();

    loPainter.begin(&meRedbar);
    loPainter.setWindow(0, -100, 50, 200);
    loPainter.setRenderHint(QPainter::Antialiasing, true);
    loPainter.setPen(Qt::NoPen);

    QLinearGradient loRedGradient(0, 0, 50, 0);
    QColor loRed("#f30a0a");
    loRedGradient.setColorAt(0.0, loRed);
    if (meGlossy)
    {
        loRedGradient.setColorAt(0.5, loRed.lighter(170)); 
    }
    loRedGradient.setColorAt(1.0, loRed);

    loPainter.setBrush(loRedGradient);
    loPainter.drawRect(QRectF(0, -100, 50, 200));
    loPainter.end();

    meIndicatorbar.fill(Qt::transparent);

    loPainter.begin(&meIndicatorbar);
    loPainter.setWindow(0, -100, 50, 200);
    loPainter.setRenderHint(QPainter::Antialiasing, true);
    loPainter.setPen(Qt::NoPen);

    QLinearGradient loValueGradient(0, -2, 0, 2);
    loValueGradient.setColorAt(0.0, Qt::black);
    //loValueGradient.setColorAt(0.5, Qt::white);
    loValueGradient.setColorAt(0.5, Qt::black);
    loValueGradient.setColorAt(1.0, Qt::black);
    loPainter.setBrush(loValueGradient);
    loPainter.drawRoundRect(QRectF(0, -2, 50, 4));

    loPainter.end();
}

void VerticalBarGraph::paint(QPainter *painter)
{
    if (drawConstraintsFail())
    {
        return;
    }
    // Check if the size has changed
    QRectF loBoundRect = boundingRect();
    QSize loSize = loBoundRect.size().toSize();
    if (loSize != meRedbar.size() || meForceCompleteRedraw)
    {
        meForceCompleteRedraw = false;
        redrawPixmaps(loSize);
    }

    double loGreenLowerValue = meGreenLowertolerance/(meGreenLowertolerance+meOrangeLowertolerance+meLowerRedZone)*100;
    double loOrangeLowerValue = meOrangeLowertolerance/(meGreenLowertolerance+meOrangeLowertolerance+meLowerRedZone)*100;
    double loRedLowerValue = 100-loGreenLowerValue-loOrangeLowerValue;

    double loGreenUpperValue = meGreenUppertolerance/(meGreenUppertolerance+meOrangeUppertolerance+meUpperRedZone)*100;
    double loOrangeUpperValue = meOrangeUppertolerance/(meGreenUppertolerance+meOrangeUppertolerance+meUpperRedZone)*100;
    double loRedUpperValue = 100-loGreenUpperValue-loOrangeUpperValue;

    double loLineValue;
    if (meValue >= meTarget) // we are at the right side of the VerticalBarGraph
    {
        loLineValue = 100 * (meValue - meTarget) / (meGreenUppertolerance + meOrangeUppertolerance + meUpperRedZone); 
    }
    else // we are at the left side of the VerticalBarGraph
    {
        loLineValue = 100 * (meValue - meTarget) / (meGreenLowertolerance + meOrangeLowertolerance + meLowerRedZone); 
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->scale(loBoundRect.width()/50, loBoundRect.height()/200);
    painter->translate(0, 100);

    QTransform loTransform;
    loTransform.scale(loBoundRect.width()/50, loBoundRect.height()/200);
    loTransform.translate(0, 100);

    painter->drawPixmap(QRectF(0, -loGreenUpperValue, 50, loGreenLowerValue+loGreenUpperValue), meGreenbar, loTransform.mapRect(QRectF(0, -loGreenUpperValue, 50, loGreenLowerValue+loGreenUpperValue)));

    painter->drawPixmap(QRectF(0, -loOrangeUpperValue-loGreenUpperValue, 50, loOrangeUpperValue), meOrangebar, loTransform.mapRect(QRectF(0, -loOrangeUpperValue-loGreenUpperValue, 50, loOrangeUpperValue)));
    painter->drawPixmap(QRectF(0, loGreenLowerValue, 50, loOrangeLowerValue), meOrangebar, loTransform.mapRect(QRectF(0, loGreenLowerValue, 50, loOrangeLowerValue)));

    painter->drawPixmap(QRectF(0, -100, 50, loRedUpperValue), meRedbar, loTransform.mapRect(QRectF(0, -100, 50, loRedUpperValue)));
    painter->drawPixmap(QRectF(0, loGreenLowerValue+loOrangeLowerValue, 50, loRedLowerValue), meRedbar, loTransform.mapRect(QRectF(0, loGreenLowerValue+loOrangeLowerValue, 50, loRedLowerValue)));

    painter->translate(0, -loLineValue);
    painter->drawPixmap(QRectF(0, -2, 50, 4), meIndicatorbar, loTransform.mapRect(QRectF(0, -2, 50, 4)));
    painter->restore();
}

