#ifndef _ARROW_H
#define _ARROW_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtQuick/QtQuick>

class clArrow : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor arrowColor READ getArrowColor WRITE setArrowColor)
    Q_PROPERTY(ArrowDirection arrowDirection READ getArrowDirection WRITE setArrowDirection)

public:
    enum ArrowDirection {
        DirectionLeft, DirectionRight, DirectionUp, DirectionDown
    };

    Q_ENUMS(ArrowDirection);

    clArrow(QQuickItem *paParent = 0);
protected:
    QColor getArrowColor() const;
    void setArrowColor(QColor paColor);
    ArrowDirection getArrowDirection() const;
    void setArrowDirection(ArrowDirection paValue);

    void paint(QPainter *painter);

private:
    QColor meColor;
    ArrowDirection meDirection;
};

#endif

