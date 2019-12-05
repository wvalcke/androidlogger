#include <iostream>
#include "Arrow.h"

using namespace std;

clArrow::clArrow(QQuickItem *paParent) : QQuickPaintedItem(paParent)
{
    meColor = QColor("green");
    meDirection = clArrow::DirectionLeft;
    setWidth(150);
    setHeight(150);
}

QColor clArrow::getArrowColor() const
{
    return meColor;
}

void clArrow::setArrowColor(QColor paColor)
{
    meColor = paColor;
    update();
}

clArrow::ArrowDirection clArrow::getArrowDirection() const
{
    return meDirection;
}

void clArrow::setArrowDirection(ArrowDirection paDirection)
{
    meDirection = paDirection;
    update();
}

void clArrow::paint(QPainter* paPainter)
{
    QRectF loBound = boundingRect();
    QSizeF loSize = loBound.size();

    paPainter->scale(width()/300, height()/300);
    paPainter->translate(150, 150);
    paPainter->setRenderHints(QPainter::Antialiasing, true);
    QPen loPen(Qt::black);
    loPen.setWidth(10);
    paPainter->setPen(loPen);

    QPainterPath path;
    if (meDirection == clArrow::DirectionRight)
    {
    }
    else if (meDirection == clArrow::DirectionLeft)
    {
        paPainter->rotate(180);
    }
    else if (meDirection == clArrow::DirectionDown)
    {
        paPainter->rotate(90);
    }
    else
    {
        paPainter->rotate(270);
    }
    path.moveTo(150, 0);
    path.lineTo(0, -150);
    path.lineTo(8, -44);
    path.lineTo(-150, -65);
    path.lineTo(-150, 65);
    path.lineTo(8, 44);
    path.lineTo(0, 150);
    path.closeSubpath();

    paPainter->setBrush(meColor);

    paPainter->drawPath(path);
}
