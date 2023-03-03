#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include<QVector>

class Interpolation
{
public:
    Interpolation();
    QVector<double> solve(QVector<double> a,QVector<double> b,QVector<double> x);

};

#endif // INTERPOLATION_H
