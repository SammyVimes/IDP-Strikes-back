#include "addfooddialog.h"

AddFoodDialog::AddFoodDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    this->nameLineEdit->clear();
    this->compLineEdit->clear();
    this->foodAmountSpinBox->setValue(1);
    this->foodLifetimeSpinBox->setValue(1);
    // remove question mark from the title bar
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(this->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(validate()));
    connect(this->compLineEdit, SIGNAL(textChanged(QString)), this, SLOT(validate()));
    validate();
}

void AddFoodDialog::validate()
{
    bool res = true;
    res &= !(this->nameLineEdit->text().isEmpty());
    res &= !(this->compLineEdit->text().isEmpty());
    this->pushButton->setEnabled(res);
}

void AddFoodDialog::on_addFoodDialog_accepted()
{
    emit readyToAddFood(Food(this->nameLineEdit->text(), this->compLineEdit->text(), this->foodLifetimeSpinBox->value(), this->foodAmountSpinBox->value()));
}
