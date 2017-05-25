#include "checkboxfabric.h"

CheckBoxFabric::CheckBoxFabric(QWidget *p_parent, QWidget *f_parent) :
    m_pparent(p_parent), m_fparent(f_parent)
{

}

QCheckBox *CheckBoxFabric::getCheckBox(Pill p)
{
    QCheckBox * res = new PillCheckBox(m_pparent);
    QString name = p.name();
    res->setText(name);
    Pill *pp = new Pill(p);
    res->setProperty("val", qVariantFromValue((void *)pp));
    return res;
}

QCheckBox *CheckBoxFabric::getCheckBox(Food f)
{
    QCheckBox * res = new FoodCheckBox(m_fparent);
    res->setText(f.name());
    Food *fp = new Food(f);
    res->setProperty("val", qVariantFromValue((void *)fp));
    return res;
}
