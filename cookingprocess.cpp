#include "cookingprocess.h"

vector<Food> CookingProcess::getMenu() const
{
    return menu;
}

void CookingProcess::setMenu(const vector<Food> &value)
{
    menu = value;
}

DFDElement *CookingProcess::deserialize(QDomNode node) {
    QDomNode cookElem = node.firstChild();
    CookingProcess* cookingProcess = new CookingProcess();
    while (!cookElem.isNull()) {
        QString nodeName = cookElem.nodeName();
        if (nodeName == "menu") {
            auto food = deserializeFood(cookElem);
            cookingProcess->setMenu(food);
        }
        cookElem = cookElem.nextSibling();
    }
    return cookingProcess;
}


void CookingProcess::printToStream(ostream &os) const
{
    os << "<cooking>" << endl;

     os << "<menu>";
     std::for_each (menu.begin(), menu.end(), [&os](Food i)
     {
         i.printStream(os);
     });
     os << "</menu>";

     os << "</cooking>" << endl;
}
