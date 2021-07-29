#ifndef SOLVER_H
#define SOLVER_H

#include <QString>
#include <QDebug>
struct rule
{
    int X[5];
    int Y[5];
    int quantity;
    int opNumber;
    QString op;
};
struct variation
{
    int Coord[40][4];
    int number;
};

class Solver {
private:
public:
    int ruleQuantity = 1;
    int max;
    void openfile(struct rule *&r, QString fileName);
    int FindPos(struct rule*& r, struct variation *&v);
    bool NextPos(int *&a, int maxN, int quantity);
    bool ruleCheck(int *&a, struct rule *&r, int j);
    bool CreateMassive(int *&a,struct variation *v, struct rule *r);
    bool NextPosMas(int *&a, int *maxN, int quantity);
    int **findSolution(struct variation *&v,struct rule *&r);
    void getMatrix(int *&a,struct variation *v, struct rule *r, int **&XY);
    void printSolution(int **XY);
};


#endif // SOLVER_H
