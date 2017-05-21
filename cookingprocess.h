#ifndef COOKINGPROCESS_H
#define COOKINGPROCESS_H

#include "dfdelement.h"
#include "food.h"
#include "pill.h"
#include "vector"

using namespace std;

class CookingProcess : DFDElement
{
public:

    CookingProcess(int type):DFDElement(type) {

    }

    CookingProcess():DFDElement() {

    }

    vector<Food> getMenu() const;
    void setMenu(const vector<Food> &value);

private:
    vector<Food> menu;



    // DFDElement interface
public:
    void printToStream(ostream &os);
};

#endif // COOKINGPROCESS_H
