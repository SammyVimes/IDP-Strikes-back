#ifndef DFDELEMENT_H
#define DFDELEMENT_H

#include <iostream>

class DFDElement
{
public:
    DFDElement(int type);

    DFDElement() {
        this->type = -1;
    }

    inline int getType() {
        return this->type;
    }

    friend std::ostream& operator<< (std::ostream& os, const DFDElement& dt);

private:
    int type;

};

#endif // DFDELEMENT_H
