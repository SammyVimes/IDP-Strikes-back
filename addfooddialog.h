#ifndef ADDFOODDIALOG_H
#define ADDFOODDIALOG_H

#include <QDialog>
#include "food.h"
#include "ui_addfooddialog.h"

class AddFoodDialog : public QDialog, public Ui::addFoodDialog
{
    Q_OBJECT
public:
    explicit AddFoodDialog(QWidget *parent = 0);

signals:
    void readyToAddFood(Food f);
public slots:
private slots:
    void on_addFoodDialog_accepted();
};

#endif // ADDFOODDIALOG_H
