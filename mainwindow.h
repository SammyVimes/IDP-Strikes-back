#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "food.h"
#include "planwindow.h"
#include "addpilldialog.h"
#include "addfooddialog.h"
#include "pillcheckbox.h"
#include "foodcheckbox.h"
#include "checkboxfabric.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void validate();

private slots:
    void on_createPlanPushButton_clicked();
    void on_addPillPushButton_clicked();
    void on_addFoodPushButton_clicked();
    void refreshFoodDesc();
    void refreshPillDesc();

    void addFood(Food f);
    void addPill(Pill p);
private:
    Ui::MainWindow *ui;
    AddPillDialog *apd = NULL;
    AddFoodDialog *afd = NULL;
    CheckBoxFabric *cbf = NULL;
};

#endif // MAINWINDOW_H
