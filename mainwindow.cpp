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
    MNode* node1FromGraph1 = graph->getFirstNodes()[0];
    graph->addNode(node1FromGraph1, 1337);

    DirectedGraph<int>* graph2 = new DirectedGraph<int>;
    graph2->addNode(228);
    MNode* node1FromGraph2 = graph2->getFirstNodes()[0];
    graph2->addNode(node1FromGraph2, 1588);

    try {
        graph->addNode(node1FromGraph2, 337);
        exit(0);
    } catch (BadGraphException& e) {

    }
    try {
        graph->linkNodes(node1FromGraph1, node1FromGraph2);
        exit(0);
    } catch (BadGraphException& e) {

    }


    delete graph;
    delete graph2;
}

MainWindow::~MainWindow()
{
    delete ui;
}
