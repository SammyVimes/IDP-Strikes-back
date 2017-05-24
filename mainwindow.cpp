#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cbf = new CheckBoxFabric(ui->pillsVerticalLayout->parentWidget(), ui->foodVerticalLayout->parentWidget());

    connect(ui->birthDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
    connect(ui->fioLineEdit, SIGNAL(textChanged(QString)), this, SLOT(validate()));

    ui->birthDateEdit->setDateRange(QDate(1940, 1, 1), QDate::currentDate().addMonths(-3));
    validate();

    checkXMLPresent();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cbf;
}

void MainWindow::validate()
{
    bool valid = true;
    QRegExp re("\\w+\\s+\\w+\\s+\\w{2,}");
    if (!re.exactMatch(ui->fioLineEdit->text())) {
        ui->statusBar->showMessage("ФИО введено неверно.");
        ui->createPlanPushButton->setEnabled(false);
        return;
    }

    //TODO не используется
    if (ui->birthDateEdit->date() < QDate(1940, 1, 1)) {
        ui->statusBar->showMessage("Дата введена неверно.");
        ui->createPlanPushButton->setEnabled(false);
        return;
    }

    ui->statusBar->showMessage("Готово к созданию плана питания");
    ui->createPlanPushButton->setEnabled(true);
    return;
}

void MainWindow::showHelp()
{
    QMessageBox::about(this, "Помощь", "Оно должно работать!");
}

void MainWindow::getPillList(QList<Pill *> &ptoOut)
{
    QObjectList pills = ui->pillsVerticalLayout->parentWidget()->children();
    for (QObject *o : pills)
    {
        Pill *p = (Pill *) o->property("val").value<void *>();
        if (p != NULL)
        {
            ptoOut.append(p);
        }
    }
}

void MainWindow::getFoodList(QList<Food *> &ftoOut)
{
    QObjectList food = ui->foodVerticalLayout->parentWidget()->children();
    for (QObject *o : food)
    {
        Food *f = (Food *) o->property("val").value<void *>();
        if (f != NULL)
        {
            ftoOut.append(f);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    bool errFlag = false;
    QList<Food *> ftoOut;
    getFoodList(ftoOut);

    QList<Pill *> ptoOut;
    getPillList(ptoOut);

    //TODO Serialize ftoOut and ptoOut

    stringstream pillsStream;
    stringstream foodStream;

    pillsStream << "<pills>";
    for (Pill* pill : ptoOut) {
        pill->printStream(pillsStream);
    }
    pillsStream << "</pills>";

    foodStream << "<food>";
    for (Food* food : ftoOut) {
        food->printStream(foodStream);
    }
    foodStream << "</food>";

    QFile pillsFile("pills.mdp");
    QFile foodFile("food.mdp");

    if (pillsFile.open(QIODevice::ReadWrite)) {
        QTextStream stream( &pillsFile );
        stream.setCodec("UTF-8");
        stream.setGenerateByteOrderMark(false);
        stream << QString::fromStdString(pillsStream.str());
        pillsFile.close();
    } else {
        errFlag = true;
    }

    if (foodFile.open(QIODevice::ReadWrite)) {
        QTextStream stream( &foodFile );
        stream.setCodec("UTF-8");
        stream.setGenerateByteOrderMark(false);
        stream << QString::fromStdString(foodStream.str());
        foodFile.close();
    } else {
        errFlag = true;
    }

    if (errFlag)
    {
        int res = QMessageBox::question(this, "Ошибка при записи файлов", "Некоторые данные не были сохранены. Уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);
        if (res == QMessageBox::Yes)
        {
            e->accept();
        }
        else
        {
            e->ignore();
        }
    }
    else
    {
        e->accept();
    }
}



struct ProcessingFood {

    Food food;
    int restPortions;
    int restTime;
    int lastEatingProcess;

    ProcessingFood(Food foodValue) {
        food = foodValue;
        restPortions = foodValue.amount();
        restTime = foodValue.expirationDate() * 3;

        // указываем на cooking process
        lastEatingProcess = 1;
    }

    ProcessingFood(const ProcessingFood& pFood) {
        this->food = pFood.food;
        this->restPortions = pFood.restPortions;
        this->restTime = pFood.restTime;
        this->lastEatingProcess = pFood.lastEatingProcess;
    }

};

struct FoodComputer {
    vector<ProcessingFood> idlingFood;
    ProcessingFood* currentFood = nullptr;
    int boringTime;
    QString lastBoredFood;
};

void MainWindow::on_createPlanPushButton_clicked()
{
    vector<Food> foodVec;
    vector<Pill> pillVec;
    QObjectList food = ui->foodVerticalLayout->parentWidget()->children();
    for (QObject *o : food)
    {
        Food *f = (Food *) o->property("val").value<void *>();
        if (f != nullptr)
        {
            QCheckBox* cBox = (QCheckBox*) o;
            if (cBox->checkState() == Qt::CheckState::Checked) {
                foodVec.push_back(Food(*f));
            }
        }
    }

    QObjectList pills = ui->pillsVerticalLayout->parentWidget()->children();
    for (QObject *o : pills)
    {
        QCheckBox* cBox = (QCheckBox*) o;
        Pill *p = (Pill *) o->property("val").value<void *>();
        if (p != nullptr)
        {
            if (cBox->checkState() == Qt::CheckState::Checked) {
                pillVec.push_back(Pill(*p));
            }
        }
    }

    MedsProcess* meds = new MedsProcess(0);
    meds->setPills(pillVec);
    meds->setRejectedFood({"Мука", "Перец", "Картошка"});
    CookingProcess *cooking = new CookingProcess(2);

    //выпилить говно

    cooking->setMenu(foodVec);


    using DNode = DirectedGraph<DFDElement*>::Node;
    DirectedGraph<DFDElement*>* dfd = new DirectedGraph<DFDElement*>;

    DNode* medsNode = dfd->addNode(meds);
    DNode* cookingNode = dfd->addNode(cooking);

    int planForDays = ui->scheduleDaysSpinBox->value();

    for (int i = 0; i < planForDays * 3; i++) {
        dfd->addNode(new EatingProcess());
    }

    auto nodes = dfd->getNodes();
    for (Pill pill : meds->getPills()) {
        for (int i = 2; i < nodes.size(); i++) {
            // вычитаем первые две фейковые ноды (медицину и холодильник)
            int nI = i - 2;
            if ((nI / 3) < pill.getLifeTime()) {
                bool ingestionMatches = false;
                switch (nI % 3) {
                case 0:
                    ingestionMatches = pill.breakfast();
                    break;
                case 1:
                    ingestionMatches = pill.lunch();
                    break;
                case  2:
                    ingestionMatches = pill.dinner();
                    break;
                }
                if (ingestionMatches) {
                    DirectedGraph<DFDElement*>::Node* node = nodes.at(i);
                    dfd->linkNodes(medsNode, node);
                    EatingProcess* eP = (EatingProcess*) node->getValue();
                    if (pill.beforeFlag()) {
                        vector<Pill> pls = eP->getMedsBeforeEating();
                        pls.push_back(pill);
                        eP->setMedsBeforeEating(pls);
                    } else {
                        vector<Pill> pls = eP->getMedsAfterEating();
                        pls.push_back(pill);
                        eP->setMedsAfterEating(pls);
                    }
                }
            } else {
                break;
            }
        }
    }

    FoodComputer fc;
    int boreTime = ui->changeScheduleSpinBox->value();
    fc.boringTime = boreTime;
    fc.lastBoredFood = QString("");

    for (int i = 2; i < nodes.size(); i++) {
        if (fc.currentFood == nullptr) {
            if ((fc.idlingFood.size() != 0) && (fc.idlingFood.at(0).food.name() != fc.lastBoredFood)) {
                ProcessingFood f = fc.idlingFood.at(0);
                fc.idlingFood.erase(fc.idlingFood.begin());
                fc.currentFood = new ProcessingFood(f);
            } else {
                vector<Food> menu = cooking->getMenu();
                bool found = false;
                for (Food f : menu) {
                    if (f.name() != fc.lastBoredFood) {
                        found = true;
                        fc.currentFood = new ProcessingFood(f);
                        break;
                    }
                }
                if (!found) {
                    // show error
                    return;
                }
            }
        }

        DNode* node = nodes.at(i);
        EatingProcess* eP = (EatingProcess*) node->getValue();
        eP->setFood(fc.currentFood->food);
        DNode* nodeFrom = nodes.at(fc.currentFood->lastEatingProcess);
        dfd->linkNodes(nodeFrom, node);

        // текущий eating process как источник для следующего
        fc.currentFood->lastEatingProcess = i;

        fc.boringTime--;
        if (fc.boringTime == 0) {
            fc.lastBoredFood = fc.currentFood->food.name();
        }

        fc.currentFood->restPortions--;
        fc.currentFood->restTime--;

        for (int i = fc.idlingFood.size() - 1; i >= 0; i--) {
            ProcessingFood idle = fc.idlingFood.at(i);
            idle.restTime--;
            fc.idlingFood[i] = idle;
            if (idle.restTime == 0) {
                fc.idlingFood.erase(fc.idlingFood.begin() + i);
            }
        }

        if (fc.currentFood->restTime == 0 || fc.currentFood->restPortions == 0) {
            delete fc.currentFood;
            fc.currentFood = nullptr;
        }

        if (fc.boringTime == 0) {
            if (fc.currentFood != nullptr) {
                fc.idlingFood.push_back(*fc.currentFood);
                fc.currentFood = nullptr;
            }
            fc.boringTime = boreTime;
        }
    }

    Plan* plan = new Plan();
    plan->setGraph(dfd);
    plan->setBirthTimestamp(100);
    plan->setName(ui->fioLineEdit->text());
    plan->setFoodChangeThreshold(boreTime);
    plan->setDays(planForDays);

    PlanWindow *pw = new PlanWindow(plan, this);
    pw->show();
    pw->raise();
    this->hide();
}

void MainWindow::on_addPillPushButton_clicked()
{
    if (this->apd == NULL) {
        apd = new AddPillDialog(this);
        connect(apd, SIGNAL(readyToAddPill(Pill)), this, SLOT(addPill(Pill)));
    }
    apd->show();
    apd->raise();
}

void MainWindow::on_addFoodPushButton_clicked()
{
    if (this->afd == NULL) {
        afd = new AddFoodDialog(this);
        connect(afd, SIGNAL(readyToAddFood(Food)), this, SLOT(addFood(Food)));
    }
    afd->show();
    afd->raise();
}

void MainWindow::addFood(Food f)
{
    QCheckBox *ch = cbf->getCheckBox(f);
    connect(ch, SIGNAL(refreshDescription()), this, SLOT(refreshFoodDesc()));
    connect(ch, SIGNAL(clearDescription()), ui->foodPlainTextEdit, SLOT(clear()));
    ui->foodVerticalLayout->addWidget(ch);
}

void MainWindow::addPill(Pill p)
{
    QCheckBox *ch = cbf->getCheckBox(p);
    connect(ch, SIGNAL(refreshDescription()), this, SLOT(refreshPillDesc()));
    connect(ch, SIGNAL(clearDescription()), ui->pillPlainTextEdit, SLOT(clear()));
    ui->pillsVerticalLayout->addWidget(ch);
}

void MainWindow::checkXMLPresent()
{
    //TODO Get pills and food from pills.xml and food.xml
    //TODO Use addPill() and addFood() to add objects
    QFile pfile("pills.mdp");
    QFileInfo fi(pfile);
    if (!pfile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Не могу открыть pills.mdp", "Ошибка при открытии " + fi.absoluteFilePath());
    }
    else
    {
        QDomDocument doc("pills");
        if (!doc.setContent(&pfile))
        {
            pfile.close();
            QMessageBox::warning(this, "Не могу открыть pills.mdp", "Ошибка при открытии " + fi.absoluteFilePath());
        }
        else
        {
            QDomElement docElem = doc.documentElement();
            QDomNode n = docElem.firstChild();
            while(!n.isNull())
            {
                addPill(Pill::deserialize(n));
                n = n.nextSibling();
            }
            pfile.close();
        }
    }

    QFile ffile("food.mdp");
    QFileInfo ffi(ffile);
    if (!ffile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Не могу открыть food.mdp", "Ошибка при открытии " + ffi.absoluteFilePath());
    }
    else
    {
        QDomDocument doc("food");
        if (!doc.setContent(&ffile)) {
            ffile.close();
            QMessageBox::warning(this, "Не могу открыть food.mdp", "Ошибка при открытии " + ffi.absoluteFilePath());
            return;
        }
        ffile.close();

        QDomElement docElem = doc.documentElement();
        QDomNode n = docElem.firstChild();
        while(!n.isNull())
        {
            addFood(Food::deserialize(n));
            n = n.nextSibling();
        }
        ffile.close();
    }
}

void MainWindow::refreshFoodDesc()
{
    QCheckBox *cb = (QCheckBox *) sender();
    Food *from = (Food *) cb->property("val").value<void *>();
    QString desc = "Название: " + from->name() +
            "\nСостав: " + from->comp() +
            "\nСрок  годности: " + QString::number(from->expirationDate()) + " дней" +
            "\nКоличество: " + QString::number(from->amount()) + " порции";
    this->ui->foodPlainTextEdit->setPlainText(desc);
}

void MainWindow::refreshPillDesc()
{
    QCheckBox *cb = (QCheckBox *) sender();
    Pill *from = (Pill *) cb->property("val").value<void *>();
    QString time = (from->beforeFlag()) ? "перед" : "после";
    QString times = "";
    times += (from->takeTimeMask() & 0b100 != 0) ? " завтрак" : "";
    times += (from->takeTimeMask() & 0b010 != 0) ? " обед" : "";
    times += (from->takeTimeMask() & 0b001 != 0) ? " ужин" : "";
    QString desc = "Название: " + from->name() +
            "\nУпотреблять: " + time + times +
            "\nВ течении: " + QString::number(from->getLifeTime()) + " дней";
    this->ui->pillPlainTextEdit->setPlainText(desc);
}
