#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*w.on_pushButton_3_clicked();
    w.on_pushButton_3_clicked();
    w.on_pushButton_3_clicked();
    w.on_pushButton_3_clicked();
    w.on_pushButton_3_clicked();*/
    return a.exec();
}
