#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DirectedGraph<int>* graph = new DirectedGraph<int>;
    graph->addNode(50);
    using MNode = DirectedGraph<int>::Node;
    MNode* queq = graph->getFirstNodes()[0];
    graph->addNode(queq, 1337);

    delete graph;
}

MainWindow::~MainWindow()
{
    delete ui;
}
