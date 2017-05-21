#include "eatingprocess.h"

vector<Pill> EatingProcess::getMedsBeforeEating() const
{
    return medsBeforeEating;
}

void EatingProcess::setMedsBeforeEating(const vector<Pill> &value)
{
    medsBeforeEating = value;
}

Food EatingProcess::getFood() const
{
    return food;
}

void EatingProcess::setFood(const Food &value)
{
    food = value;
}

vector<Pill> EatingProcess::getMedsAfterEating() const
{
    return medsAfterEating;
}

void EatingProcess::setMedsAfterEating(const vector<Pill> &value)
{
    medsAfterEating = value;
}


void EatingProcess::printToStream(ostream &os) const
{
    os << "<eating>" << endl;

    os << "<before>";
    std::for_each (medsBeforeEating.begin(), medsBeforeEating.end(), [&os](Pill i)
    {
        i.printStream(os);
    });
    os << "</before>";

    food.printStream(os);

    os << "<after>";
    std::for_each (medsAfterEating.begin(), medsAfterEating.end(), [&os](Pill i)
    {
        i.printStream(os);
    });
    os << "</after>";

    os << "</eating>" << endl;
}
