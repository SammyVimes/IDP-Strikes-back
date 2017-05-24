#include "addpilldialog.h"

AddPillDialog::AddPillDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setWindowTitle("Добавить препарат");
    this->pillAfterRadioButton->setChecked(true);
    this->pillBeforeRadioButton->setChecked(false);
    this->pillNameLineEdit->clear();
    this->amountLineEdit->clear();
    // remove question mark from the title bar
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(this->pillNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(validate()));
    connect(this->pillBreakfastCheckBox, SIGNAL(toggled(bool)), this, SLOT(validate()));
    connect(this->pillDinnerCheckBox, SIGNAL(toggled(bool)), this, SLOT(validate()));
    connect(this->pillLunchCheckBox, SIGNAL(toggled(bool)), this, SLOT(validate()));
    connect(this->amountLineEdit, SIGNAL(textChanged(QString)), this, SLOT(validate()));
    validate();
}

void AddPillDialog::validate()
{
    bool res = true;
    res &= !(this->pillNameLineEdit->text().isEmpty());
    res &= !(this->amountLineEdit->text().isEmpty());
    res &= ((this->pillBreakfastCheckBox->isChecked()
            + this->pillDinnerCheckBox->isChecked()
            + this->pillLunchCheckBox->isChecked()) > 0);
    this->OKPushButton->setEnabled(res);
}

void AddPillDialog::on_addPillDialog_accepted()
{
    int mask = 0;
    mask |= (this->pillBreakfastCheckBox->isChecked() << 2);
    mask |= (this->pillLunchCheckBox->isChecked() << 1);
    mask |= (this->pillDinnerCheckBox->isChecked());
    emit readyToAddPill(Pill(this->pillNameLineEdit->text(), this->pillLifeTimeSpinBox->value(), this->pillBeforeRadioButton->isChecked(), mask, this->amountLineEdit->text()));
}
