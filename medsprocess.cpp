#include "medsprocess.h"


vector<QString> MedsProcess::getRejectedFood() const
{
    return rejectedFood;
}

void MedsProcess::setRejectedFood(const vector<QString> &value)
{
    rejectedFood = value;
}

vector<Pill> MedsProcess::getPills() const
{
    return pills;
}

void MedsProcess::setPills(const vector<Pill> &value)
{
    pills = value;
}


void MedsProcess::printToStream(ostream &os)
{
    os << "<meds>" << endl;

    os << "<rejected>";
    std::for_each (rejectedFood.begin(), rejectedFood.end(), [&os](QString i)
    {
        os << "<rejected>" << endl;
        os << i.toStdString() << endl;
        os << "</rejected>" << endl;
    });
    os << "</rejected>";

    os << "<pills>";
    std::for_each (pills.begin(), pills.end(), [&os](Pill i)
    {
        i.printStream(os);
    });
    os << "</pills>";

    os << "</meds>" << endl;
}
