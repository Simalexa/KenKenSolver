#include <iostream>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include "contour.h"

Contour::Contour()
{
}
Contour::~Contour()
{
}
QStringList Contour::findLines(int X, int Y)
{
    QStringList line;
    line.append(QString::number(X)+" "+QString::number(Y-1)+" "+QString::number(X)+" "+QString::number(Y));
    line.append(QString::number(X)+" "+QString::number(Y)+" "+QString::number(X-1)+" "+QString::number(Y));
    line.append(QString::number(X-1)+" "+QString::number(Y)+" "+QString::number(X-1)+" "+QString::number(Y-1));
    line.append(QString::number(X-1)+" "+QString::number(Y-1)+" "+QString::number(X)+" "+QString::number(Y-1));
    return line;
}
QStringList Contour::deleteSameLines(QStringList Lines)
{
    for (int i = 0; i < Lines.size(); i++)
        {
            QStringList CoordiantesI = Lines[i].split(" ");
            for (int j = 0; j < Lines.size(); j++)
            {
                QStringList CoordiantesJ = Lines[j].split(" ");
                if((CoordiantesI[0]==CoordiantesJ[2] && CoordiantesI[1]==CoordiantesJ[3] && CoordiantesI[2]==CoordiantesJ[0] && CoordiantesI[3]==CoordiantesJ[1]) || (CoordiantesI[0]==CoordiantesJ[0] && CoordiantesI[1]==CoordiantesJ[1] && CoordiantesI[2]==CoordiantesJ[2] && CoordiantesI[3]==CoordiantesJ[3]) && (i!=j))
                {
                    Lines.removeAll(Lines[j]);
                    Lines.removeAll(Lines[i]);
                }
            }
        }
    return Lines;
}
QStringList Contour::createContour(struct rule *&r, int i)
{
    QStringList lines;
    for(int j=0; j < r[i].quantity; j++)
         lines.append(findLines(r[i].X[j],r[i].Y[j]));
    lines=deleteSameLines(lines);
    return lines;
}

