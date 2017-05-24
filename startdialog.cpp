#include "startdialog.h"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Стартовое окно");
    // remove question mark from the title bar
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    reloadPlans();
    validate();
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::reloadPlans()
{
    QStringList qsl = PlanFilesManager::getPlanList();
    this->ui->listWidget->clear();
    this->ui->listWidget->addItems(qsl);
    if (qsl.size() > 0) {
        QModelIndex modelIndex = this->ui->listWidget->rootIndex();
        this->ui->listWidget->setCurrentIndex(modelIndex);
    }
}

void StartDialog::validate()
{
    if (this->ui->listWidget->count() == 0) {
        this->ui->openPushButton->setEnabled(false);
        this->ui->deletePushButton->setEnabled(false);
    }
}

void StartDialog::on_openPushButton_clicked()
{
    std::ifstream is(this->ui->listWidget->currentItem()->text().toStdString());
    Plan *p = Plan::deserialize(is);
    PlanWindow *pw = new PlanWindow(p, this);
    pw->show();
    pw->raise();
    this->hide();
}

void StartDialog::on_createPushButton_clicked()
{
    this->parentWidget()->show();
    this->parentWidget()->raise();
    this->hide();
    validate();
}

void StartDialog::on_deletePushButton_clicked()
{
    int res = QMessageBox::question(this, "Вы уверены?", "Вы собираете удалить " + this->ui->listWidget->currentItem()->text() + ", продолжить?", QMessageBox::Yes, QMessageBox::No);
    if (res == QMessageBox::Yes)
    {
        QFile f(this->ui->listWidget->currentItem()->text());
        if (!f.remove()) {
            QMessageBox::information(this, "Ошибка", "Ошибка при удалении " + f.fileName(), QMessageBox::Ok);
        }
    }
}

void StartDialog::on_helpPushButton_clicked()
{
    QMessageBox::information(this, "Справка", "Тыкай кнопки чтобы выжить", QMessageBox::Ok);
}
