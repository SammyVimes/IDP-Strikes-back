#include "pillcombobox.h"

PillCheckBox::PillCheckBox()
{

}

PillCheckBox::PillCheckBox(QWidget *parent) : QComboBox(parent)
{

}

void PillCheckBox::mouseMoveEvent(QMouseEvent *e)
{
    emit refreshDescription();
}
