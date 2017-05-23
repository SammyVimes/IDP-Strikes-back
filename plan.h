#ifndef PLAN_H
#define PLAN_H

#include "directedgraph.h"
#include "dfdelement.h"
#include <iostream>


using namespace std;

class Plan
{
public:
    Plan();
    DirectedGraph<DFDElement *> *getGraph() const;
    void setGraph(DirectedGraph<DFDElement *> *value);

    int getDays() const;
    void setDays(int value);

    int getFoodChangeThreshold() const;
    void setFoodChangeThreshold(int value);

    int getBirthTimestamp() const;
    void setBirthTimestamp(int value);

    QString getName() const;
    void setName(const QString &value);

    void serialize(ostream& os);

private:
    DirectedGraph<DFDElement*> *graph;
    int days;
    int foodChangeThreshold;
    int birthTimestamp;
    QString name;
};

#endif // PLAN_H
