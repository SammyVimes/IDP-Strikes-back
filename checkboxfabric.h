#ifndef CHECKBOXFABRIC_H
#define CHECKBOXFABRIC_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QVariant>
#include "pillcheckbox.h"
#include "foodcheckbox.h"
#include "pill.h"
#include "food.h"

class CheckBoxFabric
{
public:
    CheckBoxFabric(QWidget *p_parent, QWidget *f_parent);
    QCheckBox *getCheckBox(Pill p);
    QCheckBox *getCheckBox(Food f);
private:
    QWidget *m_fparent;
    QWidget *m_pparent;
};

#endif // CHECKBOXFABRIC_H
