#include "foodcheckbox.h"

FoodCheckBox::FoodCheckBox()
{

}

FoodCheckBox::FoodCheckBox(QWidget *parent) : QCheckBox(parent)
{

}

void FoodCheckBox::leaveEvent(QEvent *e)
{
    emit clearDescription();
}

void FoodCheckBox::mouseMoveEvent(QMouseEvent *e)
{
    emit refreshDescription();
}
