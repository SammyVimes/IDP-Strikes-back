#ifndef DFDELEMENT_H
#define DFDELEMENT_H


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

private:
    int type;

};

#endif // DFDELEMENT_H
