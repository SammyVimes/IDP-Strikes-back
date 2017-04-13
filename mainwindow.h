#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <map>
#include "displayabledfdelement.h"
#include "directedgraph.h"
#include "dfdelement.h"
#include <QDate>
#include "clickableellipseitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawDFD(bool rebuildMap);

private:
    Ui::MainWindow *ui;
    DirectedGraph<DFDElement> *graph;
    std::map <int, DisplayableDFDElement*> elMap;
};

#endif // MAINWINDOW_H
