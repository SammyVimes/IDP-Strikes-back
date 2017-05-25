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

    MedsProcess(int type):DFDElement(1) {

    }

    MedsProcess():DFDElement(1) {

    }

    vector<QString> getRejectedFood() const;

    void setRejectedFood(const vector<QString> &value);

    vector<Pill> getPills() const;

    void setPills(const vector<Pill> &value);

    static DFDElement* deserialize (QDomNode node);

private:
    vector<QString> rejectedFood;
    vector<Pill> pills;


    // DFDElement interface
public:
    virtual void printToStream(ostream &os) const override;
};

#endif // MEDSPROCESS_H
