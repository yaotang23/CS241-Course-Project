#include "analyzefunction.h"

const int zero=0;
AnalyzeFunction::AnalyzeFunction(QObject *parent) : QObject(parent)
{
    interpolation=new Interpolation;
}
void AnalyzeFunction::slot1(int userid,QDateTime s,QDateTime e)
{
    int u=userid,l;
    QVector<int> count(location.size(),zero);//记录用户访问不同location id的次数
    QVector<coord1> result;
    QVector<double> x;
    QVector<double> y;
    QVector<double> a;
    uint start=s.toTime_t(),end=e.toTime_t();

    qDebug()<<"ana func's user.size()="<<user.size();
    //qDebug()<<"user at u size"<<user.at(u).size();
    for(int i=0;i<user.at(u).size();i++)
    {  uint x=user.at(u).at(i).dateTime.toTime_t();
       if(x>=start&&x<=end)
       {
           l=user.at(u).at(i).location_id;
           count[l]++;
       }
    }

    for(int j=0;j<10;j++)

    {   int maxValue=0,maxIndex=0;

        for(int i=0;i<location.size();i++)
        {
            if(maxValue<=count[i])
            {
                maxValue=count[i];
                maxIndex=i;

            }
        }
       count[maxIndex]=-1;
       coord1 coord;
       coord.location_id=maxIndex;
       coord.visited_times=maxValue;
       double xx=j+1;
       x.push_back(xx);
       y.push_back(maxValue);
       result.push_back(coord);
    }
    for(int i=0;i<200;i++)
    {
        double aa=i;
        a.push_back(aa*0.055);
    }

    QVector<double> y_a=interpolation->solve(x,y,a);
    for(int i=0; i<a.size();i++)
    {
        qDebug()<<"i="<<i<<" a="<<a.at(i)<<" y_a="<<y_a.at(i);
    }

    emit finish1(result,a,y_a);

}

void AnalyzeFunction::slot2(int locationid,QDateTime s,QDateTime e)
{
    int l=locationid,u;
    QVector<int> count(user.size(),zero);//记录不同user用户访问locationid的次数
    QVector<double> x;
    QVector<double> y;
    QVector<double> a;
    QVector<double> y_a;

    QVector<coord2> result;
    uint start=s.toTime_t(),end=e.toTime_t();

    for(int i=0;i<location.at(l).size();i++)
    {  uint x=location.at(l).at(i).dateTime.toTime_t();
       if(x>=start&&x<=end)
       {
           u=location.at(l).at(i).user_id;
           count[u]++;
       }
    }

    for(int j=0;j<10;j++)

    {   int maxValue=0,maxIndex=0;

        for(int i=0;i<user.size();i++)
        {
            if(maxValue<=count[i])
            {
                maxValue=count[i];
                maxIndex=i;
            }
        }
       count[maxIndex]=-1;
       coord2 coord;
       coord.user_id=maxIndex;
       coord.visited_times=maxValue;
       //result.push_back(coord);
       double xx=j+1;
       x.push_back(xx);
       y.push_back(maxValue);
       result.push_back(coord);
    }
    for(int i=0;i<200;i++)
    {
        double aa=i;
        a.push_back(aa*0.055);
    }

     y_a=interpolation->solve(x,y,a);
    /*for(int i=0; i<a.size();i++)
    {
        qDebug()<<"i="<<i<<" a="<<a.at(i)<<" y_a="<<y_a.at(i);
    }
    */
    emit finish2(result,a,y_a);
}

void AnalyzeFunction::slot3(int u1,int u2,QDateTime t1,QDateTime t2)
{   /*

    QVector<int> comPOIid;
    QVector<int> comPOItimes1;
    QVector<int> comPOItimes2;

    int totalTimes1;
    int totalTimes2;
    int totalPlaces1;
    int totalPlaces2;*/
    data_result_3 res;
    res.totalTimes1=0;
    res.totalTimes2=0;
    res.totalPlaces1=0;
    res.totalPlaces2=0;
    QVector<int> check1(location.size(),zero);//用于记录对应location是否被访问过 0为没访问 非0为访问过
    QVector<int> check2(location.size(),zero);
    uint start=t1.toTime_t(),end=t2.toTime_t();
    for(int i=0;i<user.at(u1).size();i++)
    {
        uint t=user.at(u1).at(i).dateTime.toTime_t();
        int loc=user.at(u1).at(i).location_id;
        if(t>=start&&t<=end)
        {
            //这条访问记录有效
            res.totalTimes1++;
            if(check1.at(loc)==0) res.totalPlaces1++;
            check1[loc]++;
        }
    }
    for(int i=0;i<user.at(u2).size();i++)
    {
        uint t=user.at(u2).at(i).dateTime.toTime_t();
        int loc=user.at(u2).at(i).location_id;
        if(t>=start&&t<=end)
        {
            res.totalTimes2++;
            if(check2.at(loc)==0) res.totalPlaces2++;
            if(check2.at(loc)==0&&check1.at(loc)>0) res.comPOIid.push_back(loc);
            check2[loc]++;
        }
    }
    int maxvalue=-1,maxid=-1;
    for(int i=0;i<res.comPOIid.size();i++)
    {   int id=res.comPOIid.at(i),time;
        res.comPOItimes1.push_back(check1.at(id));
        res.comPOItimes2.push_back(check2.at(id));
        time=( check1.at(id)>check2.at(id)? check1.at(id):check2.at(id) );
        if(maxvalue<time)
        {maxvalue=time;
         maxid=i;
        }

    }
    res.maxComId=maxid;

   emit finish3(res);
}
void AnalyzeFunction::slot4(int l1,int l2,QDate date)
{   DAU4 res;
    res.dau1=0;
    res.dau2=0;
    for(int i=0;i<location.at(l1).size();i++)
    {
        QDate d=location.at(l1).at(i).dateTime.date();
        if(d==date)
            res.dau1++;
    }
    for(int i=0;i<location.at(l2).size();i++)
    {
        QDate d=location.at(l2).at(i).dateTime.date();
        if(d==date)
            res.dau2++;
    }
    emit finish4(res);
}
