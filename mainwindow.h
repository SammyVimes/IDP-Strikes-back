#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <fstream>
#include "food.h"
#include "planwindow.h"
#include "addpilldialog.h"
#include "addfooddialog.h"
#include "pillcheckbox.h"
#include "foodcheckbox.h"
#include "checkboxfabric.h"
#include "plan.h"

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
    void showHelp();

protected:
    void closeEvent(QCloseEvent *e);

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
    AddPillDialog *apd = nullptr;
    AddFoodDialog *afd = nullptr;
    CheckBoxFabric *cbf = nullptr;
    void checkXMLPresent();
};

#endif // MAINWINDOW_H
