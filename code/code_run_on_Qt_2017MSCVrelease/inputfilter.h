#ifndef INPUTFILTER_H
#define INPUTFILTER_H
#include<QVector>
#include<QDateTime>
#include<QFileDialog>
#include<QFile>
#include<QStringList>
#include<QDebug>
#include<QString>
#include<qobject.h>
#include<QObject>
#include<QThread>
#include <QMetaType>

struct cknode{
    int user_id;
    int location_id;
    QDateTime dateTime;
    float lati;
    float longi;
    cknode(){
        qRegisterMetaType<cknode>("cknode");
    }
};

class InputFilter:public QObject
{
Q_OBJECT;
private:
    //原始签到记录
    QVector<cknode> cklist;
    //记录userid=i的user的签到记录序号
    QVector<QVector<cknode>> user;
    //记录location id=i的location的签到记录序号
    QVector<QVector<cknode>> location;



signals:
    void progress(int p);
    //void inputResult(QVector<cknode> cklist);
    void finish_filter();
public:
    InputFilter(QObject*parent=nullptr);
    //void openfile(QFile* file);
    void filter(QDateTime beginTime,QDateTime endTime,float minla,float maxla,float minlong,float maxlong,QFile* file);
    QVector<cknode> inputResult(){return cklist;}
    QVector<QVector<cknode>> userResult(){return user;}
    QVector<QVector<cknode>> locationResult(){return location;}

};

#endif // INPUTFILTER_H
