#include "mapdialog.h"
#include "ui_mapdialog.h"
#include<QPushButton>
#include<QString>
MapDialog::MapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapDialog)
{
    ui->setupUi(this);
    m_view = new QWebEngineView(this);
    m_view->setGeometry(0,0,550,550);

    QWebEnginePage *page = m_view->page();
    QString lng=QString::number(0);
    QString lat=QString::number(0);
    QString command = QString("%1,%2").arg(lng).arg(lat);
    page->runJavaScript(command);
    QString mappathA = exepath + "/map/baiduMap.html";//离线地图
    qDebug()<<mappathA;
    page->load(QUrl((mappathA)));

    /*
    QWebEngineView *view=new QWebEngineView();
    view->setUrl(QUrl("https://zhuanlan.zhihu.com/p/351084915"));
    view->show();
    */
}
/*
 *void MainWindow::on_finished_clicked()
{
    QString Lng = ui->lineEditlng->text();//获取经度
    QString Lat = ui->lineEditlat->text();//获取纬度
    QWebEnginePage *page = m_view->page();


    QString command = QString("movepoint(%1,%2)").arg(Lng).arg(Lat);
    page->runJavaScript(command);
}




void MainWindow::on_btnmapA_clicked()
{
    QWebEnginePage *page = m_view->page();
    QString mappathA = exepath + "/map/test.html";//离线地图
     qDebug()<<mappathA;
    page->load(QUrl((mappathA)));
}

*/
MapDialog::~MapDialog()
{
    delete ui;
}
