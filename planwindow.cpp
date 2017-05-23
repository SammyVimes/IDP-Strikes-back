#include "planwindow.h"
#include "ui_planwindow.h"

PlanWindow::PlanWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlanWindow)
{
    ui->setupUi(this);

    connect(ui->closePlanAction, SIGNAL(triggered(bool)), parent, SLOT(raise()));
    connect(ui->closePlanAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    connect(ui->helpAction, SIGNAL(triggered(bool)), parent, SLOT(showHelp()));

    connect(ui->exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->exitAction, SIGNAL(triggered(bool)), parent, SLOT(close()));

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

    testGraph();
}

void PlanWindow::testGraph() {
    Pill nimesil(QString("Нимесил"), 5, true, 1, QString::number(5));
    Pill asspirine(QString("Assпирин"), 5, true, 1, QString::number(5));
    Food pizz(QString("Пепперони"), QString("Pickle x1, Box x1"), 15, 1);


    using DNode = DirectedGraph<DFDElement*>::Node;
    DirectedGraph<DFDElement*>* dfd = new DirectedGraph<DFDElement*>;
    DNode* cooking = dfd->addNode(new DFDElement(0));
    DNode* doctor = dfd->addNode(new DFDElement(1));
    CookingProcess *p = new CookingProcess(2);
    std::vector<Food> vec;
    vec.push_back(pizz);
    p->setMenu(vec);

    EatingProcess* p2 = new EatingProcess(2);
    p2->setFood(pizz);
    vector<Pill> before = {asspirine};
    vector<Pill> after = {nimesil};
    p2->setMedsAfterEating(after);
    p2->setMedsBeforeEating(before);

    DNode* n11 = dfd->addNode(cooking, p);
    DNode* n12 = dfd->addNode(cooking, new DFDElement(2));
    DNode* n13 = dfd->addNode(n11, new DFDElement(2));
    DNode* n21 = dfd->addNode(n13, new DFDElement(2));
    DNode* n22 = dfd->addNode(n12, p2);
    DNode* n23 = dfd->addNode(doctor, new DFDElement(2));
    DNode* n31 = dfd->addNode(n23, new DFDElement(2));
    DNode* n32 = dfd->addNode(n31, new DFDElement(2));
    DNode* n33 = dfd->addNode(n32, new DFDElement(2));
    dfd->linkNodes(doctor, n11);
    dfd->linkNodes(doctor, n13);
    dfd->linkNodes(doctor, n21);
    dfd->linkNodes(doctor, n31);
    dfd->linkNodes(n22, n32);
    dfd->linkNodes(doctor, n33);

    this->graph = dfd;
    drawDFD(true);
    stringstream ss;
    ss << *this->graph;

    QString filename="Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << QString::fromStdString(ss.str());
    }
    QTextStream ts( stdout );
    ts << QString::fromStdString(ss.str());
}

PlanWindow::~PlanWindow()
{
    delete ui;
}

static DisplayableDFDElement* lastSelected;

class IntakeClickListener : public OnClickListener {
public:

    DisplayableDFDElement* item;
    PlanWindow* window;

    IntakeClickListener(PlanWindow* mw, DisplayableDFDElement* item) {
        this->item = item;
        this->window = mw;
    }

    virtual void onClick(QGraphicsEllipseItem *clickedItem) {
        item->setSelected(true);
        if (lastSelected) {
            lastSelected->setSelected(false);
        }
        if (lastSelected == item) {
            lastSelected = nullptr;
        } else {
            lastSelected = item;
        }
        window->drawDFD(false);
    }
};


void PlanWindow::drawDFD(bool rebuildMap)
{
    QGraphicsView* gView = this->ui->graphicsView;
    QGraphicsScene* scene = gView->scene();
    scene->clear();

    if (rebuildMap) {
        elMap.clear();
    }

    using DNode = DirectedGraph<DFDElement*>::Node;

    int row = 0;
    int col = 0;

    int offsetLeft = 100;
    int padding = 25;
    int elemSize = 50;

    int colOffset = elemSize + (padding * 2);

    QDate curDate = QDate::currentDate();
    int curDay = 1;

    DirectedGraph<DFDElement*>* graph = this->graph;
    std::for_each(graph->begin(), graph->end(), [this, rebuildMap, &curDate, &curDay, offsetLeft, padding, elemSize, colOffset, &row, &col, graph, scene](DNode* n) {
        int type = n->getValue()->getType();

        QBrush greenBrush(Qt::green);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);

        switch (type) {
        case 0: {
            QGraphicsItem* item = scene->addRect(0, 0, 80, 300);
            item->setPos(0, 0);
            DisplayableDFDElement* displayable;
            if (rebuildMap) {
                displayable = new DisplayableDFDElement(n->getId(), -1, -1, n->getValue());
                this->elMap[n->getId()] = displayable;
            } else {
                displayable = this->elMap[n->getId()];
            }
            displayable->setItem(item);
            break;
        }
        case 1: {
            QGraphicsItem* item = scene->addRect(0, 0, 300, 80);
            item->setPos(offsetLeft + 0, 300);

            DisplayableDFDElement* displayable;
            if (rebuildMap) {
                displayable = new DisplayableDFDElement(n->getId(), -1, -1, n->getValue());
                this->elMap[n->getId()] = displayable;
            } else {
                displayable = this->elMap[n->getId()];
            }
            displayable->setItem(item);
            break;
        }
        case 2: {
            qreal x = colOffset * col + padding + offsetLeft;
            qreal y = colOffset * row + padding;
            ClickableEllipseItem* item = new ClickableEllipseItem();
            item->setRect(0, 0, elemSize, elemSize);
            item->setPos(x, y);
            item->setPen(outlinePen);
            item->setBrush(greenBrush);
            scene->addItem(item);
            DisplayableDFDElement* displayable;
            if (rebuildMap) {
                displayable = new DisplayableDFDElement(n->getId(), row, col, n->getValue());
                this->elMap[n->getId()] = displayable;
            } else {
                displayable = this->elMap[n->getId()];
            }
            displayable->setItem(item);
            item->listener = new IntakeClickListener(this, displayable);

            col++;
            if (col > 2) {
                qreal x = colOffset * col + padding + offsetLeft;
                qreal y = colOffset * row + padding;
                scene->addRect(x, y, elemSize * 2, elemSize);
                QGraphicsTextItem* text = scene->addText(QString("День ")
                                                         + QString::number(curDay)
                                                         + QString("\n")
                                                         + curDate.toString("dd MMMM"));
                text->setTextWidth(elemSize * 2);
                text->setPos(x, y);

                row++;
                col = 0;
                curDate = curDate.addDays(1);
                curDay++;
            }
            break;
        }
        }
    });

    std::for_each(graph->begin(), graph->end(), [this, offsetLeft, padding, elemSize, colOffset, graph, scene](DNode* n) {
        int id = n->getId();
        std::vector<DNode*> outgoingNodes = n->getOutgoingNodes();
        DisplayableDFDElement* selfNode = elMap[id];

        QGraphicsItem* node1 = selfNode->getItem();

        if (!node1) {
            return;
        }

        std::for_each(outgoingNodes.begin(), outgoingNodes.end(), [this, &selfNode, elemSize, scene, node1](DNode* outN) {
            DisplayableDFDElement* el = this->elMap[outN->getId()];
            QGraphicsItem* node2 = el->getItem();

            if (!node2) {
                return;
            }

            if (!selfNode->isSelected() && !el->isSelected()) {
                return;
            }

            QPen myPen;
            myPen.setWidth(2);
            myPen.setColor(QColor(100, 100, 100));
            qreal arrowSize = 20;
            QPointF pos1 =  QPointF(node1->x() + (elemSize / 2), node1->y() + (elemSize / 2));
            QPointF pos2 =  QPointF(node2->x() + (elemSize / 2), node2->y() + (elemSize / 2));

            QGraphicsLineItem* gLine = scene->addLine(pos1.x(), pos1.y(), pos2.x(), pos2.y(), myPen);

            double Pi = 3.1415926;

            QBrush blackBrush(Qt::black);
            QLineF line(pos2, pos1);
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
            scene->addPolygon(arrowHead, myPen, blackBrush);
        });
    });
}

