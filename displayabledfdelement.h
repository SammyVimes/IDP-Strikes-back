#ifndef DISPLAYABLEDFDELEMENT_H
#define DISPLAYABLEDFDELEMENT_H

#include "dfdelement.h"
#include "QGraphicsItem"

class DisplayableDFDElement
{
public:
    DisplayableDFDElement(int id, int row, int col, DFDElement dfdElement);

    DisplayableDFDElement(){}

    inline void setRow(int row) {
        this->row = row;
    }

    inline void setCol(int col) {
        this->col = col;
    }

    inline int getRow() {
        return this->row;
    }

    inline int getCol() {
        return this->col;
    }

    inline int getId() {
        return this->id;
    }

    inline void setItem(QGraphicsItem* item) {
        this->item = item;
    }

    inline QGraphicsItem* getItem() {
        return this->item;
    }

    inline DFDElement getElement() {
        return this->element;
    }

private:

    int id;
    int row;
    int col;
    DFDElement element;
    QGraphicsItem* item = 0;
};

#endif // DISPLAYABLEDFDELEMENT_H
