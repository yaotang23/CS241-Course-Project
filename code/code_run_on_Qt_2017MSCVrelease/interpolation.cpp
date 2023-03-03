#include "interpolation.h"
const double zero=0;
Interpolation::Interpolation()
{

}

QVector<double> Interpolation::solve(QVector<double> x, QVector<double> y, QVector<double> a)//Lagrange interpolation
{
    int n=x.size();
    QVector<double> res(a.size(),zero);
    for(int k=0;k<a.size();k++)
    {
        double s;
        for(int i=0;i<n;i++)
        {
            s=y[i];
            for(int j=0;j<n;j++)
            {
                if(j!=i) s=s*(a[k]-x[j])/(x[i]-x[j]);
            }
            res[k]+=s;
        }
    }
    return res;
}
/*


class Lagrange {
public:
     Lagrange(vector<double> x, vector<double> y,double interp_x) : X(x), Y(y)
    {
        int n = x.size();
        double result = 0,s;
        for (int i = 0; i < n; i++)
        {
            s = y[i];
            for(int j=0;j<n;j++)
            {
                if (j != i) s = s * (interp_x - x[j]) / (x[i] - x[j]);
            }
            result += s;
        }
        cout << fixed << setprecision(3) << result << endl;
    }



private:
    vector<double> X, Y;
};
*/
