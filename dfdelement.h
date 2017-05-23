#ifndef DFDELEMENT_H
#define DFDELEMENT_H

#include <iostream>
#include <QtXml>
#include <vector>
#include "pill.h"
#include "food.h"

class DFDElement
{
public:
    DFDElement(int type);

    DFDElement() {
        this->type = -1;
    }

    inline int getType() {
        return this->type;
    }

    virtual void printToStream(std::ostream& os) const {
        os << "<dfd>";
        os << "<type>" << QString::number(type).toStdString() << "</type>";
        os << "</dfd>";
    }

    static DFDElement* deserialize (QDomNode node) {
        QDomNode type = node.firstChild();
        QString name = type.nodeName();
        QString val = type.firstChild().nodeValue();
        return new DFDElement(val.toInt());
    }

    friend std::ostream& operator<< (std::ostream& os, const DFDElement* dt);

    static vector<Pill> deserializePills(QDomNode node) {
        QDomNode el = node.firstChild();
        vector<Pill> pills;
        while (!el.isNull()) {
            Pill pill = Pill::deserialize(el);
            el = el.nextSibling();
            pills.push_back(pill);
        }
        return pills;
    }

    static vector<Food> deserializeFood(QDomNode node) {
        QDomNode el = node.firstChild();
        vector<Food> foods;
        while (!el.isNull()) {
            Food food = Food::deserialize(el);
            el = el.nextSibling();
            foods.push_back(food);
        }
        return foods;
    }

private:
    int type;

};

#endif // DFDELEMENT_H
