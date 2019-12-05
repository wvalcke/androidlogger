#include <iostream>
#include "GaugeZones.h"

using namespace std;

clGaugeZones::clGaugeZones(QQuickItem *paParent) : QQuickPaintedItem(paParent)
{
    setWidth(150);
    setHeight(150);
}

bool clGaugeZones::checkConsistency() const
{
    if (meMinAngle == meMaxAngle || meMinValue == meMaxValue)
        return false;
    if (meMinAngle > meMaxAngle)
        return false;
    if (meMinValue > meMaxValue)
        return false;
    return true;
}

QVariantList clGaugeZones::getColorZones() const
{
    QVariantList loList;
    QList<tyColorZoneInfo>::const_iterator loIt = meColorZones.begin();
    for (; loIt != meColorZones.end(); loIt++)
    {
        QVariantMap loMap;
        loMap["color"] = loIt->meColor.name();
        loMap["start"] = loIt->meStart;
        loMap["span"] = loIt->meSpan;
        loList.append(loMap);
    }
    return loList;
}

void clGaugeZones::setColorZones(QVariantList paZones)
{
    meColorZones.clear();
    QVariantList::iterator loIt = paZones.begin();
    for (; loIt != paZones.end(); loIt++)
    {
        QVariant loV = *loIt;
        QMap<QString, QVariant> loMap = loV.toMap();
        if (loMap.contains("start") && loMap.contains("span") && loMap.contains("color"))
        {
            tyColorZoneInfo loInfo;
            loInfo.meColor = loMap["color"].toString();
            loInfo.meStart = loMap["start"].toDouble();
            loInfo.meSpan = loMap["span"].toDouble();
            meColorZones.append(loInfo);
        }
    }
    update();
}

void clGaugeZones::setMinValue(double paValue)
{
    meMinValue = paValue;
    if (checkConsistency()) update();
}

double clGaugeZones::getMinValue() const
{
    return meMinValue;
}

void clGaugeZones::setMaxValue(double paValue)
{
    meMaxValue = paValue;
    if (checkConsistency()) update();
}

double clGaugeZones::getMaxValue() const
{
    return meMaxValue;
}

void clGaugeZones::setMinAngle(double paAngle)
{
    meMinAngle = paAngle;
    if (checkConsistency()) update();
}

double clGaugeZones::getMinAngle() const
{
    return meMinAngle;
}

void clGaugeZones::setMaxAngle(double paAngle)
{
    meMaxAngle = paAngle;
    if (checkConsistency()) update();
}

double clGaugeZones::getMaxAngle() const
{
    return meMaxAngle;
}

void clGaugeZones::paint(QPainter* paPainter)
{
    QRectF loBound = boundingRect();
    QSizeF loSize = loBound.size();
    qreal loMinSize = std::min(loSize.width(), loSize.height());

    paPainter->translate((width()-loMinSize)/2, (height()-loMinSize)/2);
    paPainter->scale(width()/300, height()/300);
    paPainter->translate(150, 150);
    paPainter->setRenderHints(QPainter::Antialiasing, true);
    QPen loPen;
    loPen.setWidth(16);
    loPen.setCapStyle(Qt::FlatCap);

    double loAngleSpan = meMaxAngle-meMinAngle;
    double loValueSpan = meMaxValue-meMinValue;

    // draw color zones
    QListIterator<tyColorZoneInfo> loZoneIt(meColorZones);
    while (loZoneIt.hasNext())
    {
        paPainter->save();
        tyColorZoneInfo loColorZone = loZoneIt.next();
        loPen.setColor(loColorZone.meColor);
        paPainter->setPen(loPen);
        double loStartAngle = (loColorZone.meStart-meMinValue)/(loValueSpan)*(loAngleSpan)+meMinAngle;
        paPainter->rotate(loStartAngle);
        double loSpan = loColorZone.meSpan/loValueSpan*loAngleSpan;
        paPainter->drawArc(QRectF(-142, -142, 284, 284), 90*16, -loSpan*16);
        paPainter->restore();
    }
}
