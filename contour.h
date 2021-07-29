#ifndef CONTOUR_H
#define CONTOUR_H
#include "mainwindow.h"
#include <QString>

class Contour
{
private:
public:
    Contour();
    ~Contour();
    QStringList findLines(int X, int Y);
    QStringList createContour(struct rule *&r, int i);
    QStringList deleteSameLines(QStringList Lines);
};

#endif // CONTOUR_H
