#ifndef COOKINGPROCESS_H
#define COOKINGPROCESS_H

#include "dfdelement.h"
#include "food.h"
#include "pill.h"
#include "vector"

using namespace std;

class CookingProcess : public DFDElement
{
public:

    CookingProcess(int type):DFDElement(0) {

    }

    CookingProcess():DFDElement(0) {

    }

    vector<Food> getMenu() const;
    void setMenu(const vector<Food> &value);

    static DFDElement* deserialize (QDomNode node);

private:
    vector<Food> menu;



    // DFDElement interface
public:
    virtual void printToStream(ostream &os) const override;
};

#endif // COOKINGPROCESS_H
