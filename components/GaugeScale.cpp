#include <iostream>
#include "GaugeScale.h"

using namespace std;

clGaugeScale::clGaugeScale(QQuickItem *paParent) : QQuickPaintedItem(paParent)
{
    meScaleColor = "white";
    meScalePrecision = 1;
    meScaleFontSize = 16;

    setWidth(150);
    setHeight(150);
}

bool clGaugeScale::checkConsistency() const
{
    return (meMinAngle != meMaxAngle && meMinValue != meMaxValue);
}

QString clGaugeScale::getScaleColor() const
{
    return meScaleColor;
}

void clGaugeScale::setScaleColor(QString paScaleColor)
{
    meScaleColor = paScaleColor;
    update();
}

int clGaugeScale::getScalePrecision() const
{
    return meScalePrecision;
}

void clGaugeScale::setScalePrecision(int paPrecision)
{
    meScalePrecision = paPrecision;
    update();
}

int clGaugeScale::getScaleFontSize() const
{
    return meScaleFontSize;
}

void clGaugeScale::setScaleFontSize(int paSize)
{
    meScaleFontSize = paSize;
    update();
}

QList<qreal> clGaugeScale::getTickList() const
{
    return meTickList;
}

void clGaugeScale::setTickList(QList<qreal> paTickList)
{
    meTickList = paTickList;
    update();
}

void clGaugeScale::setMinValue(double paValue)
{
    meMinValue = paValue;
    if (checkConsistency()) update();
}

double clGaugeScale::getMinValue() const
{
    return meMinValue;
}

void clGaugeScale::setMaxValue(double paValue)
{
    meMaxValue = paValue;
    if (checkConsistency()) update();
}

double clGaugeScale::getMaxValue() const
{
    return meMaxValue;
}

void clGaugeScale::setMinAngle(double paAngle)
{
    meMinAngle = paAngle;
    if (checkConsistency()) update();
}

double clGaugeScale::getMinAngle() const
{
    return meMinAngle;
}

void clGaugeScale::setMaxAngle(double paAngle)
{
    meMaxAngle = paAngle;
    if (checkConsistency()) update();
}

double clGaugeScale::getMaxAngle() const
{
    return meMaxAngle;
}

void clGaugeScale::paint(QPainter* paPainter)
{
    QRectF loBound = boundingRect();
    QSizeF loSize = loBound.size();
    qreal loMinSize = std::min(loSize.width(), loSize.height());

    paPainter->translate((width()-loMinSize)/2, (height()-loMinSize)/2);
    paPainter->scale(width()/300, height()/300);
    paPainter->translate(150, 150);
    paPainter->setRenderHints(QPainter::Antialiasing, true);
    QFont loFont;
    loFont.setPixelSize(meScaleFontSize);
    paPainter->setFont(loFont);
    QPen loPen(meScaleColor);
    loPen.setWidth(1);
    paPainter->setPen(loPen);
    QListIterator<qreal> loIt(meTickList);
    while (loIt.hasNext())
    {
        paPainter->save();
        double loValue = loIt.next();
        double loRotation = (loValue-meMinValue)/(meMaxValue-meMinValue)*(meMaxAngle-meMinAngle)+meMinAngle;
        paPainter->rotate(loRotation);
        paPainter->translate(0, -120);
        paPainter->rotate(-loRotation);
        //loPainter.scale(1, -1);
        QString loData = QString::number(loValue, 'f', meScalePrecision);
        QSize loSize = paPainter->fontMetrics().size(Qt::TextSingleLine, loData);
        //loPainter.drawText(loSize.width()/-2.0, -loSize.height()/2, loData);
        paPainter->drawText(QRectF(loSize.width()/-2.0, -loSize.height()/2, loSize.width(), loSize.height()), loData);
        paPainter->restore();
    }
}
