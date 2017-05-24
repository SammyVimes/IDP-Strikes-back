#ifndef PLAN_H
#define PLAN_H

#include "directedgraph.h"
#include "dfdelement.h"
#include "cookingprocess.h"
#include "medsprocess.h"
#include "eatingprocess.h"
#include <map>
#include <iostream>
#include <QtXml>


using namespace MDP;
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
    static Plan *deserialize(istream& is);

    EatingProcess *getEating() const;
    void setEating(EatingProcess *value);

    MedsProcess *getMeds() const;
    void setMeds(MedsProcess *value);

private:
    DirectedGraph<DFDElement*> *graph;
    EatingProcess* eating;
    MedsProcess* meds;
    int days;
    int foodChangeThreshold;
    int birthTimestamp;
    QString name;
};

#endif // PLAN_H
