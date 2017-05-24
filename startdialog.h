#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDir>
#include <QDialog>
#include <fstream>
#include "plan.h"
#include "planfilesmanager.h"
#include "planwindow.h"
#include "mainwindow.h"

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

public slots:
    void reloadPlans();
    void validate();

private slots:
    void on_openPushButton_clicked();
    void on_createPushButton_clicked();
    void on_deletePushButton_clicked();
    void on_helpPushButton_clicked();

private:
    Ui::StartDialog *ui;
};

#endif // STARTDIALOG_H
