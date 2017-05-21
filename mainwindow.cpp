#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addPill(Pill("Бисептол", 10, true, 0b011, "2 таб"));
    addFood(Food("Макароны по-флотски", "макароны, фарш из свинины, лук", 3, 4));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QCheckBox *ch = new QCheckBox(this);
    ch->setText(f.name());
    Food *fp = new Food(f);
    ch->setProperty("val", qVariantFromValue((void *)fp));
    connect(ch, SIGNAL(clicked(bool)), this, SLOT(refreshFoodDesc()));
    ui->foodVerticalLayout->addWidget(ch);
}

void MainWindow::addPill(Pill p)
{
    QCheckBox *ch = new QCheckBox(this);
    ch->setText(p.name());
    Pill *pp = new Pill(p);
    ch->setProperty("val", qVariantFromValue((void *)pp));
    connect(ch, SIGNAL(clicked(bool)), this, SLOT(refreshPillDesc()));
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
