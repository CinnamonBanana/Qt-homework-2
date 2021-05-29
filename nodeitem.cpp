#include "nodeitem.h"

NodeItem::NodeItem(int value) : QGraphicsItem()
{
    this->value = value;
}

QRectF NodeItem::boundingRect() const
{
    return QRectF(0,0, 30, 30);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::black);
    painter->drawEllipse(0,0,30,30);
    painter->setPen(QPen(Qt::white));
    painter->drawText(QRect(0,0,30,30), Qt::AlignCenter, QString::number(value));
}
