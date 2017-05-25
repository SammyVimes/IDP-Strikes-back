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

DFDElement *MedsProcess::deserialize(QDomNode node) {
    QDomNode eatElem = node.firstChild();
    MedsProcess* eatingProcess = new MedsProcess();
    while (!eatElem.isNull()) {
        QString nodeName = eatElem.nodeName();
        if (nodeName == "rejected") {
            QDomNode el = eatElem.firstChild();
            vector<QString> els;
            while (!el.isNull()) {
                els.push_back(el.firstChild().nodeValue());
                el = el.nextSibling();
            }
            eatingProcess->setRejectedFood(els);
        } else if (nodeName == "pills") {
            auto pills = deserializePills(eatElem);
            eatingProcess->setPills(pills);
        }
        eatElem = eatElem.nextSibling();
    }
    return eatingProcess;
}


void MedsProcess::printToStream(ostream &os) const
{
    os << "<meds>" << endl;

    os << "<rejected>";
    std::for_each (rejectedFood.begin(), rejectedFood.end(), [&os](QString i)
    {
        os << "<elem>" << endl;
        os << i.toStdString() << endl;
        os << "</elem>" << endl;
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
