#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <map>
#include "displayabledfdelement.h"
#include "directedgraph.h"
#include "dfdelement.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawDFD(DirectedGraph<DFDElement>* graph);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
