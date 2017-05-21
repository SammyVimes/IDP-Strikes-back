#include "cookingprocess.h"

vector<Food> CookingProcess::getMenu() const
{
    return menu;
}

void CookingProcess::setMenu(const vector<Food> &value)
{
    menu = value;
}


void CookingProcess::printToStream(ostream &os)
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
