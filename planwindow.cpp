#include "planwindow.h"
#include "ui_planwindow.h"

PlanWindow::PlanWindow(Plan *plan, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlanWindow)
{
    ui->setupUi(this);
    setWindowTitle("Окно просмотра плана питания");

    connect(ui->closePlanAction, SIGNAL(triggered(bool)), parent, SLOT(raise()));
    connect(ui->closePlanAction, SIGNAL(triggered(bool)), parent, SLOT(show()));
    connect(ui->closePlanAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    connect(ui->helpAction, SIGNAL(triggered(bool)), parent, SLOT(showHelp()));

    connect(ui->exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->exitAction, SIGNAL(triggered(bool)), parent, SLOT(close()));

    QGraphicsScene* scene = new QGraphicsScene(this);
    this->ui->graphicsView->setScene(scene);

    this->plan = plan;


    // отрисуем
    drawDFD(true);

    // сериализуем
    stringstream ss;
    plan->serialize(ss);

    QString filename = "plan_" + plan->getName() + ".mdp";
    //QString filename = PlanFilesManager::getNextFileNameAvailable();
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << QString::fromStdString(ss.str());
        file.close();
    }

    // десериализуем
    if ( file.open(QIODevice::ReadOnly) )
    {
        QTextStream stream( &file );
        string s = stream.readAll().toStdString();
        stringstream ss;
        ss << s;
        Plan* deserialized = Plan::deserialize(ss);
        file.close();

        // сериализуем снова, чтобы найти отличия
        QString newFileName="DataDeserialized.txt";
        QFile newFile( newFileName );
        if ( newFile.open(QIODevice::ReadWrite) )
        {
            QTextStream nStream( &newFile );
            stringstream nSS;
            deserialized->serialize(nSS);
            nStream << QString::fromStdString(nSS.str());
            newFile.close();
        }
    }
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
            window->clearInfo();
        } else {
            lastSelected = item;
            window->showInfo((EatingProcess*) item->getElement());
        }
        window->drawDFD(false);

    }
};

QString foodDesc(Food food) {
    QString desc = "Название: " + food.name() +
            "\nСостав: " + food.comp() +
            "\nСрок  годности: " + QString::number(food.expirationDate()) + " дней" +
            "\nКоличество: " + QString::number(food.amount()) + " порции";
    return desc;
}

QString pillDesc(Pill pill) {
    QString time = (pill.beforeFlag()) ? "перед" : "после";
    QString times = "";
    times += (pill.takeTimeMask() & 0b100 != 0) ? " завтрак" : "";
    times += (pill.takeTimeMask() & 0b010 != 0) ? " обед" : "";
    times += (pill.takeTimeMask() & 0b001 != 0) ? " ужин" : "";
    QString desc = "Название: " + pill.name() +
            "\nУпотреблять: " + time + times +
            "\nВ течении: " + QString::number(pill.getLifeTime()) + " дней";
    return desc;
}

void PlanWindow::showInfo(EatingProcess *ep)
{
    Food food = ep->getFood();
    vector<Pill> medsAfterEating = ep->getMedsAfterEating();
    vector<Pill> medsBeforeEating = ep->getMedsBeforeEating();

    ui->foodDesc->setText(foodDesc(food));

    QString before = "";
    for (Pill pill : medsBeforeEating) {
        before.append(pillDesc(pill)).append("\n");
    }
    ui->pillBeforeDesc->setText(before);

    QString after = "";
    for (Pill pill : medsAfterEating) {
        after.append(pillDesc(pill)).append("\n");
    }
    ui->pillAfterDesc->setText(after);
}

void PlanWindow::clearInfo()
{
    ui->foodDesc->clear();
    ui->pillAfterDesc->clear();
    ui->pillBeforeDesc->clear();
}

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

    DirectedGraph<DFDElement*>* graph = this->plan->getGraph();
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
            int rows = (graph->getNodes().size() - 2) / 3;
            item->setPos(offsetLeft + 0, (colOffset * rows) + padding);

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
            QLineF line(pos2, pos1);
            double angle = ::acos(line.dx() / line.length());
            double Pi = 3.1415926;
            if (line.dy() >= 0) {
                angle = (Pi * 2) - angle;
            }

            float ofX = (elemSize / 2) * ::cos(angle);
            float ofY = (elemSize / 2) * ::sin(angle);
            pos2 = QPointF(pos2.x() + ofX, pos2.y() - ofY);
            line = QLineF(pos2, pos1);


            QGraphicsLineItem* gLine = scene->addLine(pos1.x(), pos1.y(), pos2.x(), pos2.y(), myPen);


            QBrush blackBrush(Qt::black);

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


void PlanWindow::closeEvent(QCloseEvent *e)
{
    parentWidget()->show();
    parentWidget()->raise();
    e->accept();
//    connect(ui->closePlanAction, SIGNAL(triggered(bool)), parent, SLOT(show()));
//    connect(ui->closePlanAction, SIGNAL(triggered(bool)), parent, SLOT(raise()));
}

