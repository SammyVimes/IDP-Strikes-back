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

// <graph>
DirectedGraph<DFDElement*>* deserializeGraph(QDomNode graph) {
    QDomNode graphElement = graph.firstChild();
    DirectedGraph<DFDElement*>* dfd = new DirectedGraph<DFDElement*>;

    // <nodes></nodes><outgoing></outgoing>

    while (!graphElement.isNull()) {
        QString tagName = graphElement.nodeName();

        // <nodes>
        if (tagName == "nodes") {
            QDomNode graphNode = graphElement.firstChild();
            // list :: <node>
             while (!graphNode.isNull()) {
                 QDomNode nodeElement = graphNode.firstChild();
                 int nodeId = -1;
                 DFDElement* dfdElement = nullptr;
                 // <id></id><value></value>
                 while (!nodeElement.isNull()) {
                     QString neTag = nodeElement.nodeName();
                     if (neTag == "id") {
                        nodeId = nodeElement.nodeValue().toInt();
                     } else if (neTag == "value") {
                        QDomNode valueNode = nodeElement.firstChild();
                        if (!valueNode.isNull()) {
                            QString valName = valueNode.nodeName();
                            if (valName == "dfd") {
                                dfdElement = DFDElement::deserialize(valueNode);
                            } else if (valName == "cooking") {
                                dfdElement = CookingProcess::deserialize(valueNode);
                            } else if (valName == "eating") {
                                dfdElement = EatingProcess::deserialize(valueNode);
                            } else if (valName == "meds") {
                                dfdElement = MedsProcess::deserialize(valueNode);
                            }
                        }
                     }
                     nodeElement = nodeElement.nextSibling();
                 }

                 graphNode = graphNode.nextSibling();
             }
        // <outgoing>
        } else if (tagName == "outgoing") {

        }
        graphElement = graphElement.nextSibling();
    }
}

void Plan::deserialize(istream &is)
{
    std::string str(std::istreambuf_iterator<char>(is), {});
    QString qStr = QString::fromStdString(str);
    Plan* plan = new Plan();
    QDomDocument domDoc;
    if(domDoc.setContent(qStr)) {
        QDomElement domElement = domDoc.documentElement();
        QDomNode planElement = domElement.firstChild();
        while (!planElement.isNull()) {
            QString tagName = planElement.nodeName();
            if (tagName == "name") {
                plan->setName(planElement.nodeValue());
            } else if (tagName == "birthTimestamp") {
                plan->setBirthTimestamp(planElement.nodeValue().toInt());
            } else if (tagName == "days") {
                plan->setDays(planElement.nodeValue().toInt());
            } else if (tagName == "foodChangeThreshold") {
                plan->setFoodChangeThreshold(planElement.nodeValue().toInt());
            } else if (tagName == "graph") {
                DirectedGraph<DFDElement*>* graph = deserializeGraph(planElement);
                plan->setGraph(graph);
            }
            planElement = planElement.nextSibling();
        }
    }

}

