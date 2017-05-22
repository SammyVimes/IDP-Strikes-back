#include "checkboxfabric.h"

CheckBoxFabric::CheckBoxFabric(QWidget *parent) :
    m_parent(parent)
{

}

QCheckBox *CheckBoxFabric::getCheckBox(Pill p)
{
    QCheckBox * res = new PillCheckBox(m_parent);
    QString name = p.name();
    res->setText(name);
    Pill *pp = new Pill(p);
    res->setProperty("val", qVariantFromValue((void *)pp));
    return res;
}

QCheckBox *CheckBoxFabric::getCheckBox(Food f)
{
    QCheckBox * res = new FoodCheckBox(m_parent);
    res->setText(f.name());
    Food *fp = new Food(f);
    res->setProperty("val", qVariantFromValue((void *)fp));
    return res;
}
