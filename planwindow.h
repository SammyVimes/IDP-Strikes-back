#ifndef PLANWINDOW_H
#define PLANWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <map>
#include "displayabledfdelement.h"
#include "directedgraph.h"
#include "dfdelement.h"
#include <QDate>
#include "clickableellipseitem.h"

namespace Ui {
class PlanWindow;
}

class PlanWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlanWindow(QWidget *parent = 0);
    ~PlanWindow();
    void drawDFD(bool rebuildMap);

private:
    Ui::PlanWindow *ui;
    DirectedGraph<DFDElement> *graph;
    std::map <int, DisplayableDFDElement*> elMap;
};

#endif // PLANWINDOW_H
