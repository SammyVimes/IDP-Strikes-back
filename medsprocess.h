#ifndef MEDSPROCESS_H
#define MEDSPROCESS_H

#include "dfdelement.h"
#include "food.h"
#include "pill.h"
#include "vector"

using namespace std;

class MedsProcess : public DFDElement
{
public:

    MedsProcess(int type):DFDElement(type) {

    }

    MedsProcess():DFDElement() {

    }

    vector<QString> getRejectedFood() const;

    void setRejectedFood(const vector<QString> &value);

    vector<Pill> getPills() const;

    void setPills(const vector<Pill> &value);

private:
    vector<QString> rejectedFood;
    vector<Pill> pills;

    // DFDElement interface
public:
    void printToStream(ostream &os);
};

#endif // MEDSPROCESS_H
