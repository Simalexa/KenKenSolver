#include "solver.h"
#include <QFile>
#include <QtMath>
#include <QVector>


void Solver::openfile(struct rule *&r, QString fileName)
{
    QFile List(fileName);
    int k=0, n=0;
    if (List.open(QIODevice::ReadOnly))
    {
       QTextStream in(&List);
       while (!in.atEnd())
       {
           QString line = in.readLine();
           bool flag=true;
           bool flag1 = false;
           r[n].opNumber=0;
           for(int i=0; i<line.size();i++)
           {
               if(line[i].isDigit() && i<line.size()-1)
               {
                   if(flag==true)
                   {
                       r[n].X[k]=line[i].digitValue();
                       flag=false;
                   }
                   else if(flag==false)
                   {
                       r[n].Y[k]=line[i].digitValue();
                       k++;
                       flag=true;
                   }
               }
               if(flag1 == true)
               {
                   r[n].opNumber+=qPow(10,line.size()-i-1)*line[i].digitValue();
               }
               if(line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i]== '=' || line[i]== '/')
               {
                   r[n].op=line[i];
                   flag1 = true;
               }
           }
           r[n].quantity=k;
           qDebug()<<r[n].op<<" "<<r[n].opNumber<<" "<<r[n].quantity;
           n++;
           k=0;
           ruleQuantity++;
           flag=true;
           flag1=false;
       }
    }
    else
        qDebug()<<"Error";
    List.close();
    max=r[0].X[0];
    for(int i=0; i< ruleQuantity - 1; i++)
        for(int j=0; j < r[i].quantity;j++)
            if(r[i].X[j] > max)
                max=r[i].X[j];
}
int Solver::FindPos(struct rule*& r, struct variation *&v)
{
   for(int j = 0; j < ruleQuantity - 1 ;j++)
   {
    int minN = 1;
    int maxN = max;
    int k = 0, *a;
    a = new int[r[j].quantity];
    for (int i = 0; i < r[j].quantity; i++)
        a[i] = minN;
    if (ruleCheck(a, r, j))
    {
        for (int i = 0; i < r[j].quantity; i++)
        {
            v[j].Coord[k][i] = a[i];
        }
        k++;
    }
    while (NextPos(a, maxN, r[j].quantity))
    {
        if (ruleCheck(a, r, j))
        {
            for (int i = 0; i < r[j].quantity; i++)
            {
                v[j].Coord[k][i] = a[i];
            }
            k++;
        }
    }
    for (int i = 0; i < r[j].quantity; i++)
        a[i] = maxN;
    if (ruleCheck(a, r, j))
    {
        for (int i = 0; i < r[j].quantity; i++)
        {
            v[j].Coord[k][i] = a[i];
        }
        k++;
    }
    if(k==0)
    {
        qDebug()<<"Error";
        return 0;
    }
    v[j].number = k-1;
   }
   return 0;
}

bool Solver::NextPos(int *&a, int maxN, int quantity)
{
    int numOfMax = quantity + 1;
    bool flag = true, flag1=false;
    for (int i = quantity - 1; i > 0 ; i--)
        if (a[i] == maxN && flag == true)
            numOfMax = i;
        else
            flag = false;
    for (int i = quantity; i >= numOfMax; i--)
    {
        a[i] = 1;
        flag1 = true;
    }
    if (flag1 == true)
        a[numOfMax - 1]++;
    else
        a[quantity - 1]++;

    for(int i=0 ; i < quantity ; i++)
        if(a[i] != maxN)
            return true;
    return false;
}

bool Solver::ruleCheck(int *&a, struct rule *&r, int j)
{
    int res = 0;
    for(int i=0;i<r[j].quantity;i++)
        for(int k=0;k<r[j].quantity;k++)
        {
            if(a[i]==a[k] && (r[j].X[i]==r[j].X[k] || r[j].Y[i]==r[j].Y[k]) && i!=k)
                return false;
        }
    for(int i=0;i<r[j].quantity;i++)
        if(a[i]<1 || a[i]>max)
            return false;
    if (r[j].op == "+")
    {
        for (int i = 0; i < r[j].quantity; i++)
            res += a[i];
        if (res == r[j].opNumber)
        {
            return true;
        }else
            return false;
    }
    if (r[j].op == "-")
    {
        res=a[0]-a[1];
        if (res == r[j].opNumber || res == -r[j].opNumber)
            return true;
        else
            return false;
    }
    if (r[j].op == "/")
    {
        if(a[0] % a[1] == 0 || a[1] % a[0] == 0)
        {
            if(a[0] % a[1] == 0)
                res=a[0]/a[1];
            else
                res=a[1]/a[0];
            if (res == r[j].opNumber || 1/res == -r[j].opNumber)
                return true;
            else
               return false;
        }
        else
            return false;
    }
    if (r[j].op == "*")
    {
        res=1;
        for (int i = 0; i < r[j].quantity; i++)
            res *= a[i];
        if (res == r[j].opNumber)
        {
            return true;
        }else
        return false;
    }
    if(r[j].op == "=")
    {
        if(a[0] == r[j].opNumber)
            return true;
        else
            return false;
    }
    return false;
}

bool Solver::CreateMassive(int *&a,struct variation *v, struct rule *r)
{
    int XY[max][max];
    for(int i=0 ; i < max ; i++)
        for(int j=0 ; j < max ; j++)
            for(int k=0; k < ruleQuantity - 1; k++)
                for(int m=0; m < r[k].quantity ; m++)
                    if(r[k].X[m] == i + 1 && r[k].Y[m] == j + 1)
                        XY[i][j] = v[k].Coord[a[k]][m];
    for(int i=0; i< max; i++)
        for(int j=0 ; j< max ; j++)
            for(int k=0 ; k< max ; k++)
                if((XY[i][j] == XY[i][k] || XY[j][i] == XY[k][i])&& j!=k)
                    return false;
    return true;
}
void Solver::getMatrix(int *&a,struct variation *v, struct rule *r, int **&XY)
{
    //int XY[max][max];
    for(int i=0 ; i < max ; i++)
        for(int j=0 ; j < max ; j++)
            for(int k=0; k < ruleQuantity - 1; k++)
                for(int m=0; m < r[k].quantity ; m++)
                    if(r[k].X[m] == i + 1 && r[k].Y[m] == j + 1)
                        XY[i][j] = v[k].Coord[a[k]][m];
}

bool Solver::NextPosMas(int *&a, int *maxN, int quantity)
{
    int numOfMax = quantity + 1;
    bool flag = true, flag1=false;
    for (int i = quantity - 1; i > 0 ; i--)
        if (a[i] == maxN[i] && flag == true)
            numOfMax = i;
        else
            flag = false;
    for (int i = quantity; i >= numOfMax; i--)
    {
        a[i] = 0;
        flag1 = true;
    }
    if (flag1 == true)
        a[numOfMax - 1]++;
    else
        a[quantity - 1]++;
    if(a[0]>maxN[0])
        return false;
    return true;
}

int **Solver::findSolution(struct variation *&v,struct rule *&r)
{
    int minN = 0, *a, *maxN, **XY;
    bool flag = false;
    a = new int[ruleQuantity - 1];
    maxN = new int[ruleQuantity - 1];
    XY = new int*[max];
    for(int i=0;i<max;i++)
        XY[i] = new int[max];
    for(int i=0; i < ruleQuantity - 1; i++)
    {
        maxN[i]=v[i].number;
        a[i] = minN;
    }
   while (NextPosMas(a, maxN, ruleQuantity - 1))
    {
       if(CreateMassive(a,v,r))
       {
           flag = true;
           break;
       }
    }
   if(flag==true)
   {
       getMatrix(a, v , r, XY);
       return XY;
   }
   else
        qDebug()<<"Not Found";
   return 0;
}
void Solver::printSolution(int **XY)
{
    for(int i=0;i < max;i++)
    {
        QStringList strin;
        for(int j=0;j < max;j++)
            strin.append(QString::number(XY[i][j]));
        qDebug()<<strin;
    }
}
