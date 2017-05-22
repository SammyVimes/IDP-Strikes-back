#include "pillcheckbox.h"

PillCheckBox::PillCheckBox()
{

}

PillCheckBox::PillCheckBox(QWidget *parent) : QCheckBox(parent)
{

}

void PillCheckBox::leaveEvent(QEvent *e)
{
    emit clearDescription();
}

void PillCheckBox::mouseMoveEvent(QMouseEvent *e)
{
    emit refreshDescription();
}
