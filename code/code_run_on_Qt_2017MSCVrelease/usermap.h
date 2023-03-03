#ifndef USERMAP_H
#define USERMAP_H
#include"inputfilter.h"
#include <QObject>

class UserMap: public QObject
{
    Q_OBJECT
public:
    UserMap();
public slots:
    void paintUserMap(int user_id);
    void paintLocMap(int loc_id);
signals:
    void finish_user(QVector<cknode>);
    void finish_loc(QVector<cknode>);
public:

    void init(QVector<cknode> & a,QVector<QVector<cknode>> & b,QVector<QVector<cknode>> &c)
    {
        this->list=a;
        this->user=b;
        this->location=c;
        //analyzeFunction->init_f(cklist,user,location);
        qDebug()<<"map func's user.size()="<<user.size();
        qDebug()<<"map func's location.size()="<<location.size();
    }
private:
    QVector<cknode> list;
    //记录userid=i的user的签到记录序号
    QVector<QVector<cknode>> user;
    //记录location id=i的location的签到记录序号
    QVector<QVector<cknode>> location;
};

#endif // USERMAP_H
