#include "paintdialog.h"
#include "ui_paintdialog.h"
#include"usermap.h"
#include<QThread>
#include<QWebEngineView>
#include <QHBoxLayout>
#include <QWebChannel>
#include<QMetaType>

PaintDialog::PaintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{   qRegisterMetaType<QVector<cknode>>("QVector<cknode>");
    ui->setupUi(this);
    thread3=new QThread;
    userMap=new UserMap;
    userMap->moveToThread(thread3);
    thread3->start();

    connect(this,&PaintDialog::paintUserMap,userMap,&UserMap::paintUserMap);
    connect(this,&PaintDialog::paintLocMap,userMap,&UserMap::paintLocMap);

    connect(userMap,&UserMap::finish_user,this,&PaintDialog::paint_user);
    connect(userMap,&UserMap::finish_loc,this,&PaintDialog::paint_loc);

    webEngineView=new QWebEngineView(this);
    webEngineView2=new QWebEngineView(this);
    QHBoxLayout *pLay = new QHBoxLayout(ui->widget);
    pLay->addWidget(webEngineView);
    QHBoxLayout *pLay2 = new QHBoxLayout(ui->widget_loc);
    pLay2->addWidget(webEngineView2);

    QFile file(":/map/baiduMap.html");
    file.open(QFileDevice::ReadOnly);
    QByteArray arr = file.readAll();
    file.close();
    qDebug()<<arr;
     webEngineView->page()->setHtml(arr);

     QFile file2(":/map/baiduMap2.html");
     file2.open(QFileDevice::ReadOnly);
     QByteArray arr2 = file2.readAll();
     file2.close();
     qDebug()<<arr2;
     webEngineView2->page()->setHtml(arr2);

}

PaintDialog::~PaintDialog()
{
    delete ui;
}

void PaintDialog::on_pushButton_paint_user_clicked()
{   webEngineView->page()->runJavaScript("clearAll()");
    int userid=ui->spinBox_user_id->value();
    emit paintUserMap(userid);
}



void PaintDialog::on_pushButton_paint_location_clicked()
{
    for(int i=0;i<location.size();i++)
    {   if(location[i].size()!=0)
        {
            QString str=QString("addPlace(%1,%2,%3,%4)").arg(i).arg(location[i][0].longi).arg(location[i][0].lati).arg(location[i].size());
            webEngineView2->page()->runJavaScript(str);
            qDebug()<<str;
        }
    }
    webEngineView2->page()->runJavaScript("addLabel()");

}

void PaintDialog::paint_user(QVector<cknode> u)
{

      for(int i=0;i<u.size();i++)
     {  float longitude1=u.at(i).longi;

        float latitude1=u.at(i).lati;

        int location_id=u.at(i).location_id;
        QString str=QString("paintUserMapAdd(%1,%2,%3)").arg(longitude1).arg(latitude1).arg(location_id);
        webEngineView->page()->runJavaScript(str);
        qDebug()<<"i="<< i <<str;
     }
      webEngineView->page()->runJavaScript("paintUserMap1()");

}
void PaintDialog::paint_loc(QVector<cknode>l)
{
    int locid=ui->spinBox_location_id->value();

    QString str=QString("find(%1,%2,%3)").arg(location[locid][0].longi).arg(location[locid][0].lati).arg(16);
    webEngineView2->page()->runJavaScript(str);
   qDebug()<<"locid="<<locid;
   qDebug()<<str;

}

void PaintDialog::on_pushButton_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void PaintDialog::on_pushButton_pre_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void PaintDialog::on_pushButton_clicked()
{    int locid=ui->spinBox_location_id->value();
     emit paintLocMap(locid);
}
