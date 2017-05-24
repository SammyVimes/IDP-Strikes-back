#include "mainwindow.h"
#include "startdialog.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    StartDialog s(&w);
    s.show();
    //w.show();

    return a.exec();
}
