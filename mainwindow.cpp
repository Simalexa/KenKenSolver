#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solver.cpp"
#include "contour.cpp"
#include <QElapsedTimer>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    scene->clear();
    Solver g;
    rule *r = new rule[20];
    Contour c;
    QGraphicsTextItem *text;
    QStringList Lines;
    QPen gpen(Qt::blue);
    gpen.setWidth(3);
    fileName = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(),"Text files (*.txt*)");
    if(!fileName.isNull())
        qDebug()<<"Error";
    g.openfile(r,fileName);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(3);
    max = g.max;
    step = 80;
    for (int i = 0; i <= max; ++i)
    {
        scene->addLine(i*step,0,i*step,max*step,outlinePen);
        scene->addLine(0,i*step,max*step,i*step,outlinePen);
    }
    for(int j=0;j< g.ruleQuantity -1; j++)
    {
        Lines=c.createContour(r, j);
        for(int i=0;i < Lines.size();i++)
        {
            QStringList coordinates = Lines[i].split(" ");
            scene->addLine(coordinates[1].toInt()*step,coordinates[0].toInt()*step,coordinates[3].toInt()*step,coordinates[2].toInt()*step,gpen);
        }
        text = scene->addText(r[j].op + QString::number(r[j].opNumber));
        text->setPos((r[j].Y[0]-1)*step,(r[j].X[0]-1)*step);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    Solver g;
    rule *r;
    QGraphicsTextItem *text;
    QFont solutionNumbers("Arial", 35);
    QElapsedTimer timer;
    variation *v;
    int **XY;
    r = new rule[30];
    g.openfile(r,fileName);
    v = new variation[g.ruleQuantity - 1];
    timer.start();
    g.FindPos(r,v);
    XY=g.findSolution(v,r);
    QMessageBox box;
        box.setWindowTitle("Time of the calculation");
        box.setText(QString::number(timer.nsecsElapsed()*pow(10,-9)) + " seconds");
        box.exec();
    for(int i=0 ; i < max ; i++)
        for(int j=0; j < max ; j++)
        {
            text = scene->addText(QString::number(XY[i][j]));
            text->setPos(j * step + step /4, i * step + step / 8);
            text->setFont(solutionNumbers);
        }

}
