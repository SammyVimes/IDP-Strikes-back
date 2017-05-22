#ifndef PLANWINDOW_H
#define PLANWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <map>
#include "displayabledfdelement.h"
#include "directedgraph.h"
#include "dfdelement.h"
#include <QDate>
#include "cookingprocess.h"
#include "eatingprocess.h"
#include "medsprocess.h"
#include "clickableellipseitem.h"
#include <iostream>

#include "pill.h"
#include "food.h"

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
    DirectedGraph<DFDElement*> *graph;
    std::map <int, DisplayableDFDElement*> elMap;
    void testGraph();
};

#endif // PLANWINDOW_H
