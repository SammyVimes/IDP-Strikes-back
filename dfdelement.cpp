#include "dfdelement.h"

DFDElement::DFDElement(int type)
{
    this->type = type;
}


std::ostream& operator<< (std::ostream& os, const DFDElement* dt) {
    dt->printToStream(os);
}
