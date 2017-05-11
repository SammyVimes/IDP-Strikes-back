#ifndef ADDPILLDIALOG_H
#define ADDPILLDIALOG_H

#include <QDialog>
#include "ui_addpilldialog.h"
#include "pill.h"

class AddPillDialog : public QDialog, public Ui::addPillDialog
{
    Q_OBJECT
public:
    explicit AddPillDialog(QWidget *parent = 0);

signals:
    void readyToAddPill(Pill p);

public slots:
private slots:
    void on_addPillDialog_accepted();
};

#endif // ADDPILLDIALOG_H
