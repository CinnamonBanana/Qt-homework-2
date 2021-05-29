#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>
#include <QPainter>

class NodeItem : public QGraphicsItem
{
public:
    NodeItem(int value);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
private:
    int value = 0;
};

#endif // NODEITEM_H
