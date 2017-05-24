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

    addPill(Pill("Бисептол", 10, true, 0b011, "2 таб"));
    addPill(Pill("Бисептол2", 10, true, 0b011, "2 таб"));
    addFood(Food("Макароны по-флотски", "макароны, фарш из свинины, лук", 3, 4));
    addFood(Food("Макароны по-флотски2", "макароны, фарш из свинины, лук", 3, 4));

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

void MainWindow::closeEvent(QCloseEvent *e)
{
    bool errFlag = false;
    QList<Food *> ftoOut;
    QObjectList food = ui->foodVerticalLayout->parentWidget()->children();
    for (QObject *o : food)
    {
        Food *f = (Food *) o->property("val").value<void *>();
        if (f != NULL)
        {
            ftoOut.append(f);
        }
    }

    QList<Pill *> ptoOut;
    QObjectList pills = ui->foodVerticalLayout->parentWidget()->children();
    for (QObject *o : pills)
    {
        Pill *p = (Pill *) o->property("val").value<void *>();
        if (p != NULL)
        {
            ptoOut.append(p);
        }
    }

    //TODO Serialize ftoOut and ptoOut

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

void MainWindow::on_createPlanPushButton_clicked()
{

    Pill nimesil(QString("Нимесил"), 5, true, 1, QString::number(5));
    Pill aspirine(QString("Aспирин"), 5, true, 1, QString::number(11));
    Pill pinosol(QString("Пиносол"), 5, true, 1, QString::number(9));
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
    vector<Pill> before = {aspirine};
    vector<Pill> after = {nimesil};
    p2->setMedsAfterEating(after);
    p2->setMedsBeforeEating(before);


    MedsProcess* p3 = new MedsProcess(2);
    p3->setPills({pinosol});
    p3->setRejectedFood({"Мука", "Перец", "Картошка"});

    DNode* n11 = dfd->addNode(cooking, p);
    DNode* n12 = dfd->addNode(cooking, new DFDElement(2));
    DNode* n13 = dfd->addNode(n11, new DFDElement(2));
    DNode* n21 = dfd->addNode(n13, new DFDElement(2));
    DNode* n22 = dfd->addNode(n12, p2);
    DNode* n23 = dfd->addNode(doctor, new DFDElement(2));
    DNode* n31 = dfd->addNode(n23, p3);
    DNode* n32 = dfd->addNode(n31, new DFDElement(2));
    DNode* n33 = dfd->addNode(n32, new DFDElement(2));
    dfd->linkNodes(doctor, n11);
    dfd->linkNodes(doctor, n13);
    dfd->linkNodes(doctor, n21);
    dfd->linkNodes(doctor, n31);
    dfd->linkNodes(n22, n32);
    dfd->linkNodes(doctor, n33);

    Plan* plan = new Plan();
    plan->setGraph(dfd);
    plan->setBirthTimestamp(100);
    plan->setName("Иванов Иван Иванович");
    plan->setFoodChangeThreshold(1000);
    plan->setDays(1337);

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
    QFile pfile("pills.xml");
    QFileInfo fi(pfile);
    if (!pfile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Не могу открыть pills.xml", "Ошибка при открытии " + fi.absoluteFilePath());
    }
    else
    {
        QDomDocument doc("pills");
        if (!doc.setContent(&pfile))
        {
            pfile.close();
            QMessageBox::warning(this, "Не могу открыть pills.xml", "Ошибка при открытии " + fi.absoluteFilePath());
        }
        else
        {
            QDomElement docElem = doc.documentElement();
            QDomNode n = docElem.firstChild();
            while(!n.isNull())
            {
                Pill::deserialize(n);
                n = n.nextSibling();
            }
            pfile.close();
        }
    }

    QFile ffile("food.xml");
    QFileInfo ffi(ffile);
    if (!ffile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Не могу открыть food.xml", "Ошибка при открытии " + ffi.absoluteFilePath());
    }
    else
    {
        QDomDocument doc("food");
        if (!doc.setContent(&ffile)) {
            ffile.close();
            QMessageBox::warning(this, "Не могу открыть food.xml", "Ошибка при открытии " + ffi.absoluteFilePath());
            return;
        }
        ffile.close();

        QDomElement docElem = doc.documentElement();
        QDomNode n = docElem.firstChild();
        while(!n.isNull())
        {
            Food::deserialize(n);
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
