#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QGraphicsScene* scene = new QGraphicsScene(this);
    this->ui->graphicsView->setScene(scene);

    DirectedGraph<int>* graph = new DirectedGraph<int>;
    graph->addNode(50);
    using MNode = DirectedGraph<int>::Node;
    MNode* node1FromGraph1 = graph->getNodes()[0];
    graph->addNode(node1FromGraph1, 1337);

    DirectedGraph<int>* graph2 = new DirectedGraph<int>;
    graph2->addNode(228);
    MNode* node1FromGraph2 = graph2->getNodes()[0];
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



    using DNode = DirectedGraph<DFDElement>::Node;
    DirectedGraph<DFDElement>* dfd = new DirectedGraph<DFDElement>;
    DNode* cooking = dfd->addNode(DFDElement(0));
    DNode* doctor = dfd->addNode(DFDElement(1));
    DNode* n11 = dfd->addNode(cooking, DFDElement(2));
    DNode* n12 = dfd->addNode(cooking, DFDElement(2));
    DNode* n13 = dfd->addNode(n11, DFDElement(2));
    DNode* n21 = dfd->addNode(n13, DFDElement(2));
    DNode* n22 = dfd->addNode(n12, DFDElement(2));
    DNode* n23 = dfd->addNode(doctor, DFDElement(2));
    DNode* n31 = dfd->addNode(n23, DFDElement(2));
    DNode* n32 = dfd->addNode(n31, DFDElement(2));
    DNode* n33 = dfd->addNode(n32, DFDElement(2));
    dfd->linkNodes(doctor, n11);
    dfd->linkNodes(doctor, n13);
    dfd->linkNodes(doctor, n21);
    dfd->linkNodes(doctor, n31);
    dfd->linkNodes(n22, n32);
    dfd->linkNodes(doctor, n33);

    drawDFD(dfd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawDFD(DirectedGraph<DFDElement> *graph)
{
    QGraphicsView* gView = this->ui->graphicsView;
    QGraphicsScene* scene = gView->scene();
    using DNode = DirectedGraph<DFDElement>::Node;

    int row = 0;
    int col = 0;

    int offsetLeft = 100;
    int padding = 25;
    int elemSize = 50;

    int colOffset = elemSize + (padding * 2);

    std::map <int, DisplayableDFDElement> elMap;

    std::for_each(graph->begin(), graph->end(), [&elMap, offsetLeft, padding, elemSize, colOffset, &row, &col, graph, scene](DNode* n) {
        int type = n->getValue().getType();

        QBrush greenBrush(Qt::green);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);

        switch (type) {
        case 0:
            scene->addRect(0, 0, 80, 300);
            break;
        case 1:
            scene->addRect(offsetLeft + 0, 300, 300, 80);
            break;
        case 2:
            QGraphicsItem* item = scene->addEllipse(colOffset * col + padding + offsetLeft, colOffset * row + padding, elemSize, elemSize, outlinePen, greenBrush);
            DisplayableDFDElement displayable = DisplayableDFDElement(n->getId(), row, col, n->getValue());
            displayable.setItem(item);
            elMap[n->getId()] = displayable;

            col++;
            if (col > 2) {
                row++;
                col = 0;
            }
            break;
        }
    });

    std::for_each(graph->begin(), graph->end(), [&elMap, offsetLeft, padding, elemSize, colOffset, graph, scene](DNode* n) {
        int id = n->getId();
        std::vector<DNode*> outgoingNodes = n->getOutgoingNodes();
        DisplayableDFDElement selfNode = elMap[id];

        QGraphicsItem* node1 = selfNode.getItem();

        if (!node1) {
            return;
        }

        std::for_each(outgoingNodes.begin(), outgoingNodes.end(), [scene, node1, &elMap](DNode* outN) {
            DisplayableDFDElement el = elMap[outN->getId()];
            QGraphicsItem* node2 = el.getItem();

            if (!node2) {
                return;
            }

            QPen myPen;
            myPen.setWidth(10);
            myPen.setColor(QColor(100, 100, 100));
            qreal arrowSize = 20;
            QPointF pos1 =  node1->pos();
            QPointF pos2 =  node2->pos();
            QLineF line(pos1, pos2);

            QGraphicsLineItem* gLine = scene->addLine(node1->x(), node1->y(), node2->x(), node2->y(), myPen);

            double Pi = 3.1415926;

            double angle = ::acos(line.dx() / line.length());
            if (line.dy() >= 0) {
                angle = (Pi * 2) - angle;
            }
            QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                                  cos(angle + Pi / 3) * arrowSize);
            QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                                  cos(angle + Pi - Pi / 3) * arrowSize);
            QPolygonF arrowHead;
            arrowHead << line.p1() << arrowP1 << arrowP2;
            scene->addPolygon(arrowHead);
        });
    });
}
