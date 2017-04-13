#ifndef CLICKABLEELLIPSEITEM_H
#define CLICKABLEELLIPSEITEM_H

#include <QGraphicsEllipseItem>

class OnClickListener {

public:

    virtual void onClick(QGraphicsEllipseItem* clickedItem) = 0;

    virtual ~OnClickListener() {

    }

};


class ClickableEllipseItem : public QGraphicsEllipseItem
{
public:

    ClickableEllipseItem() {
        this->setFlags(QGraphicsItem::ItemIsSelectable);
    }

    virtual ~ClickableEllipseItem() {
        if (listener) {;
            delete listener;
        }
    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    OnClickListener* listener = nullptr;
};

#endif // CLICKABLEELLIPSEITEM_H
