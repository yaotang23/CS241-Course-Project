#include "inputfilter.h"

InputFilter::InputFilter(QObject*parent):QObject(parent)
{

}


void InputFilter::filter(QDateTime beginTime,QDateTime endTime,float minla,float maxla,float minlong,float maxlong,QFile* file)
{   cklist.clear();
    user.clear();
    location.clear();
    QStringList list;
    QString datetime;
    uint begin = beginTime.toTime_t();

    uint end = endTime.toTime_t();

   int count=0,k=1;

    while(!file->atEnd())
                   {
                           QString fileLine=file->readLine();//逐行读取数据
                            list=fileLine.split(",");//一行中的单元格以，区分
                            cknode node;
                            node.user_id=((list.at(0)).toInt());
                            node.location_id=((list.at(1)).toInt());
                            datetime=list.at(2);
                            datetime.replace("T"," ");
                            datetime.replace("Z","\0");
                            node.dateTime=QDateTime::fromString(datetime,"yyyy-MM-dd hh:mm:ss");
                            uint time=node.dateTime.toTime_t();
                            node.lati=((list.at(3)).toFloat());
                            node.longi=((list.at(4)).toFloat());
                            if(time>=begin && time<=end && node.lati>=minla && node.lati<=maxla && node.longi>=minlong && node.longi<=maxlong)
                            {
                                cklist.push_back(node);

                                //按user id保存check in记录
                                for(int i=user.size();i<=node.user_id;i++)
                                {
                                    QVector<cknode> u;
                                    user.push_back(u);
                                }
                                //qDebug()<<""<<node.user_id;
                                //qDebug()<<user.size();
                                user[node.user_id].push_back(node);

                                //按照location id 保存check in记录
                                for(int i=location.size();i<=node.location_id;i++)
                                {
                                    QVector<cknode> l;
                                    location.push_back(l);
                                }
                                location[node.location_id].push_back(node);

                            }
                            if(count+1==1502536/100*k)
                            {
                                emit progress(k);
                                k++;
                            }
                            count++;
    }
file->close();
//qDebug()<<"filter's user.size()="<<user.size();
//qDebug()<<"filter suc";
emit finish_filter();

}
