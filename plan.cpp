#include "plan.h"

Plan::Plan()
{

}

DirectedGraph<DFDElement *> *Plan::getGraph() const
{
    return graph;
}

void Plan::setGraph(DirectedGraph<DFDElement *> *value)
{
    graph = value;
}

int Plan::getDays() const
{
    return days;
}

void Plan::setDays(int value)
{
    days = value;
}

int Plan::getFoodChangeThreshold() const
{
    return foodChangeThreshold;
}

void Plan::setFoodChangeThreshold(int value)
{
    foodChangeThreshold = value;
}

int Plan::getBirthTimestamp() const
{
    return birthTimestamp;
}

void Plan::setBirthTimestamp(int value)
{
    birthTimestamp = value;
}

QString Plan::getName() const
{
    return name;
}

void Plan::setName(const QString &value)
{
    name = value;
}

void Plan::serialize(ostream &os)
{
    os << "<plan>" << endl;
    os << "<name>" << name.toStdString() << "</name>" << endl;
    os << "<birthTimestamp>" << QString::number(birthTimestamp).toStdString() << "</birthTimestamp>" << endl;
    os << "<days>" << QString::number(days).toStdString() << "</days>" << endl;
    os << "<foodChangeThreshold>" << QString::number(foodChangeThreshold).toStdString() << "</foodChangeThreshold>" << endl;
    os << *this->graph;
    os << "</plan>" << endl;
}

