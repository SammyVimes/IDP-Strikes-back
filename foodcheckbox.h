#ifndef FOODCHECKBOX_H
#define FOODCHECKBOX_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>

class FoodCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    FoodCheckBox();
    FoodCheckBox(QWidget *parent);
    void leaveEvent(QEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void refreshDescription();
    void clearDescription();
};

#endif // FOODCHECKBOX_H
