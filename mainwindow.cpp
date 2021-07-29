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
    /*scene->clear();
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
    outlinePen.setWidth(2);
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
    }*/
}


void MainWindow::on_pushButton_2_clicked()
{
   // rule *r;
    //r = new rule[20];
    //Solver g;
    //variation *v;
    //v = new variation[g.ruleQuantity - 1];
    //QGraphicsTextItem *text;
    //QFont solutionNumbers("Arial", 35);
    //QElapsedTimer timer;
    //QString fileName1 = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(),"Text files (*.txt*)");
    //g.openfile(r,fileName1);
    //timer.start();
    //g.FindPos(r,v);
    //int **XY;
    /*XY = new int*[max];
    for(int i=0;i<max;i++)
        XY[i] = new int[max];
    for(int i=0;i<max;i++)
        for(int j=0;j<max;j++)
            XY[i][j]=1;*/
    //XY=g.findSolution(v,r);
    //g.printSolution(XY);
    //fileName1 = "";
    //r = {};
    //v = {};
    /*QMessageBox box;
    box.setWindowTitle("Time of the calculation");
    box.setText(QString::number(timer.nsecsElapsed()) + " nanoseconds");
    box.exec();*/
    /*for(int i=0 ; i < max ; i++)
        for(int j=0; j < max ; j++)
        {
            text = scene->addText(QString::number(XY[i][j]));
            text->setPos(j * step + step /4, i * step + step / 8);
            text->setFont(solutionNumbers);
        }*/
    //g.max=0;
}

void MainWindow::on_pushButton_3_clicked()
{
    rule *r;
    r = new rule[20];
    //Solver g;
    //variation *v;
    //v = new variation[g.ruleQuantity - 1];
    fileName = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(),"Text files (*.txt*)");
    g.openfile(r,fileName);
    //for(int i=0; i < g.ruleQuantity - 1; i++)
    //g.FindPos(r,v);
    //int **XY;
    //XY=g.findSolution(v,r);
    //g.printSolution(XY);
    //delete XY;
}
