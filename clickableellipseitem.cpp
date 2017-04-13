#include "clickableellipseitem.h"

void ClickableEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (this->listener) {
        this->listener->onClick(this);
    }
}
