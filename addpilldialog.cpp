#include "addpilldialog.h"

AddPillDialog::AddPillDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    this->pillAfterRadioButton->setChecked(true);
    this->pillBeforeRadioButton->setChecked(false);
    this->pillNameLineEdit->clear();
    this->amountLineEdit->clear();
    // remove question mark from the title bar
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void AddPillDialog::on_addPillDialog_accepted()
{
    int mask = 0;
    mask |= (this->pillBreakfastCheckBox->isChecked() << 2);
    mask |= (this->pillLunchCheckBox->isChecked() << 1);
    mask |= (this->pillDinnerCheckBox->isChecked());
    emit readyToAddPill(Pill(this->pillNameLineEdit->text(), this->pillLifeTimeSpinBox->value(), this->pillBeforeRadioButton->isChecked(), mask, this->amountLineEdit->text()));
}
