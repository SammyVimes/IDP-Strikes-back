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

    void getPillList(QList<Pill *> &ptoOut);
    
    void getFoodList(QList<Food *> &ftoOut);
    
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

struct ProcessingFood {

    Food food;
    int restPortions;
    int restTime;
    int lastEatingProcess;

    ProcessingFood(Food foodValue) {
        food = foodValue;
        restPortions = foodValue.amount();
        restTime = foodValue.expirationDate() * 3;

        // указываем на cooking process
        lastEatingProcess = 1;
    }

    ProcessingFood(const ProcessingFood& pFood) {
        this->food = pFood.food;
        this->restPortions = pFood.restPortions;
        this->restTime = pFood.restTime;
        this->lastEatingProcess = pFood.lastEatingProcess;
    }

};

struct FoodComputer {
    vector<ProcessingFood> idlingFood;
    ProcessingFood* currentFood = nullptr;
    int boringTime;
    QString lastBoredFood;
};

#endif // MAINWINDOW_H
