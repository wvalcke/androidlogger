#include <iostream>
#include "GaugeTicks.h"

using namespace std;

clGaugeTicks::clGaugeTicks(QQuickItem *paParent) : QQuickPaintedItem(paParent)
{
    meTickColor = "white";
    meMajorTick = 0.5;
    meMinorTick = 0.1;

    setWidth(150);
    setHeight(150);
}

bool clGaugeTicks::checkConsistency() const
{
    if (meMinAngle == meMaxAngle || meMinValue == meMaxValue)
        return false;
    if (meMinAngle > meMaxAngle)
        return false;
    if (meMinValue > meMaxValue)
        return false;
    return true;
}

QString clGaugeTicks::getTickColor() const
{
    return meTickColor;
}

void clGaugeTicks::setTickColor(QString paTickColor)
{
    meTickColor = paTickColor;
    update();
}

double clGaugeTicks::getMajorTick() const
{
    return meMajorTick;
}

void clGaugeTicks::setMajorTick(double paValue)
{
    meMajorTick = paValue;
    update();
}

double clGaugeTicks::getMinorTick() const
{
    return meMinorTick;
}

void clGaugeTicks::setMinorTick(double paValue)
{
    meMinorTick = paValue;
    update();
}

void clGaugeTicks::setMinValue(double paValue)
{
    meMinValue = paValue;
    if (checkConsistency()) update();
}

double clGaugeTicks::getMinValue() const
{
    return meMinValue;
}

void clGaugeTicks::setMaxValue(double paValue)
{
    meMaxValue = paValue;
    if (checkConsistency()) update();
}

double clGaugeTicks::getMaxValue() const
{
    return meMaxValue;
}

void clGaugeTicks::setMinAngle(double paAngle)
{
    meMinAngle = paAngle;
    if (checkConsistency()) update();
}

double clGaugeTicks::getMinAngle() const
{
    return meMinAngle;
}

void clGaugeTicks::setMaxAngle(double paAngle)
{
    meMaxAngle = paAngle;
    if (checkConsistency()) update();
}

double clGaugeTicks::getMaxAngle() const
{
    return meMaxAngle;
}

void clGaugeTicks::paint(QPainter* paPainter)
{
    QRectF loBound = boundingRect();
    QSizeF loSize = loBound.size();
    qreal loMinSize = std::min(loSize.width(), loSize.height());

    paPainter->translate((width()-loMinSize)/2, (height()-loMinSize)/2);
    paPainter->scale(width()/300, height()/300);
    paPainter->translate(150, 150);
    paPainter->setRenderHints(QPainter::Antialiasing, true);
    QPen loPen(meTickColor);
    loPen.setWidth(1);
    paPainter->setPen(loPen);

    int loNumberOfMajorTicks = qRound((meMaxValue-meMinValue)/meMajorTick)+1;
    double loMajorTickAngle = (meMaxAngle-meMinAngle)/(loNumberOfMajorTicks-1);
    int loNumberOfMinorTicks = qRound(meMajorTick/meMinorTick+1);
    double loMinorTickAngle = loMajorTickAngle/(loNumberOfMinorTicks-1);

    for (int loTickCount = 0; loTickCount < loNumberOfMajorTicks; loTickCount++)
    {
        paPainter->save();
        double loRotation = meMinAngle+loTickCount*loMajorTickAngle;
        paPainter->rotate(loRotation);
        paPainter->drawLine(0, -94, 0, -106);
        // draw sub tick marks
        // if dealing with last major tick, do not draw anymore the minor ticks
        if (loTickCount < loNumberOfMajorTicks-1)
        {
            for (int loMinorTickCount = 1; loMinorTickCount < loNumberOfMinorTicks-1; loMinorTickCount++)
            {
                paPainter->save();
                double loRotation = loMinorTickCount*loMinorTickAngle;
                paPainter->rotate(loRotation);
                paPainter->drawLine(0, -95, 0, -103);
                paPainter->restore();
            }
        }
        paPainter->restore();
    }
}
