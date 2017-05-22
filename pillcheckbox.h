#ifndef PILLCOMBOBOX_H
#define PILLCOMBOBOX_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>

class PillCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    PillCheckBox();
    PillCheckBox(QWidget *parent);
    void leaveEvent(QEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void refreshDescription();
    void clearDescription();
};

#endif // PILLCOMBOBOX_H
