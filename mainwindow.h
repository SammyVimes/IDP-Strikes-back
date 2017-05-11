#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "food.h"
#include "planwindow.h"
#include "addpilldialog.h"
#include "addfooddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_createPlanPushButton_clicked();
    void on_addPillPushButton_clicked();
    void on_addFoodPushButton_clicked();
    void addFood(Food f);
    void addPill(Pill p);
    void refreshFoodDesc();
    void refreshPillDesc();

private:
    Ui::MainWindow *ui;
    AddPillDialog *apd = NULL;
    AddFoodDialog *afd = NULL;
};

#endif // MAINWINDOW_H
