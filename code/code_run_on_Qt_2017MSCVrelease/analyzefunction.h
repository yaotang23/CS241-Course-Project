#ifndef ANALYZEFUNCTION_H
#define ANALYZEFUNCTION_H

#include <QObject>
#include"inputfilter.h"
#include"interpolation.h"
struct coord1
{
    int  location_id;
    int visited_times;


};

struct coord2
{
    int user_id;
    int visited_times;


};
struct data_result_3
{
    //int comPOInum;

    QVector<int> comPOIid;
    QVector<int> comPOItimes1;
    QVector<int> comPOItimes2;
    int maxComId;

    int totalTimes1;
    int totalTimes2;
    int totalPlaces1;
    int totalPlaces2;


};
struct DAU4
{
    int dau1;
    int dau2;
};


class AnalyzeFunction : public QObject
{
    Q_OBJECT
private:
    QVector<cknode>cklist;
    QVector<QVector<cknode>> user;
    QVector<QVector<cknode>> location;
    Interpolation *interpolation;

public:
    explicit AnalyzeFunction(QObject *parent = nullptr);
    void init_f(QVector<cknode>a,QVector<QVector<cknode>>b,QVector<QVector<cknode>>c)
    {
        cklist=a;
        user=b;
        location=c;
        qDebug()<<"ana func's user.size()="<<user.size();
        qDebug()<<"ana func's location.size()="<<location.size();
    }


signals:
    void finish1(QVector<coord1> res,QVector<double> x,QVector<double> y);
    void finish2(QVector<coord2>res,QVector<double> x,QVector<double> y);
    void finish3(data_result_3 res);
    void finish4(DAU4 res);
public slots:
    void slot1(int userid,QDateTime s,QDateTime e);
    void slot2(int locationid,QDateTime startTime,QDateTime endTime);
    void slot3(int userid1,int u2,QDateTime t1,QDateTime t2);
    void slot4(int l1,int l2,QDate date);
};

#endif // ANALYZEFUNCTION_H
