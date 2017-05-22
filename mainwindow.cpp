#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cbf = new CheckBoxFabric(this);

    connect(ui->birthDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
    connect(ui->fioLineEdit, SIGNAL(textChanged(QString)), this, SLOT(validate()));

    addPill(Pill("Бисептол", 10, true, 0b011, "2 таб"));
    addFood(Food("Макароны по-флотски", "макароны, фарш из свинины, лук", 3, 4));

    ui->birthDateEdit->setDateRange(QDate(1940, 1, 1), QDate::currentDate().addMonths(-3));
    validate();
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
        valid = false;
    }
    ui->createPlanPushButton->setEnabled(valid);
}

void MainWindow::on_createPlanPushButton_clicked()
{
    PlanWindow *pw = new PlanWindow(this);
    pw->show();
    pw->raise();
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
