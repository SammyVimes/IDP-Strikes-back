#ifndef EATINGPROCESS_H
#define EATINGPROCESS_H

#include "dfdelement.h"
#include "food.h"
#include "pill.h"
#include "vector"

using namespace std;

class EatingProcess : public DFDElement
{
public:

    EatingProcess(int type):DFDElement(type) {

    }

    EatingProcess():DFDElement() {

    }

    vector<Pill> getMedsBeforeEating() const;

    void setMedsBeforeEating(const vector<Pill> &value);

    Food getFood() const;

    void setFood(const Food &value);

    vector<Pill> getMedsAfterEating() const;

    void setMedsAfterEating(const vector<Pill> &value);



private:
    vector<Pill> medsBeforeEating;

    Food food;

    vector<Pill> medsAfterEating;


    // DFDElement interface
public:
    void printToStream(ostream &os);
};

#endif // EATINGPROCESS_H
