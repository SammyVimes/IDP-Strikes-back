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
}

void AddFoodDialog::on_addFoodDialog_accepted()
{
    emit readyToAddFood(Food(this->nameLineEdit->text(), this->compLineEdit->text(), this->foodLifetimeSpinBox->value(), this->foodAmountSpinBox->value()));
}
