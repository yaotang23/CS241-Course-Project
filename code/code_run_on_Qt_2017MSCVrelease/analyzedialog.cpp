#include "analyzedialog.h"
#include "ui_analyzedialog.h"
#include<QLineSeries>
#include<QMetaType>
#include<QDateTime>
#include<QChartView>
QT_CHARTS_USE_NAMESPACE
AnalyzeDialog::AnalyzeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyzeDialog)
{
    ui->setupUi(this);

    qRegisterMetaType<QVector<coord1>>("QVector<coord1>");
    qRegisterMetaType<QVector<coord2>>("QVector<coord2>");
    qRegisterMetaType<data_result_3>("data_result_3");
    qRegisterMetaType<DAU4>("DAU4");
    qRegisterMetaType<QVector<double>>("QVector<double>");
    thread2=new QThread;
    analyzeFunction=new AnalyzeFunction;
    //analyzeFunction->init_f(cklist,user,location);
   // qDebug()<<"init ana func suc";

    analyzeFunction->moveToThread(thread2);
    thread2->start();

    connect(this,&AnalyzeDialog::signal1,analyzeFunction,&AnalyzeFunction::slot1);
    connect(this,&AnalyzeDialog::signal2,analyzeFunction,&AnalyzeFunction::slot2);
    connect(this,&AnalyzeDialog::signal3,analyzeFunction,&AnalyzeFunction::slot3);
    connect(this,&AnalyzeDialog::signal4,analyzeFunction,&AnalyzeFunction::slot4);

    connect(analyzeFunction,&AnalyzeFunction::finish1,this,&AnalyzeDialog::paint1);
    connect(analyzeFunction,&AnalyzeFunction::finish2,this,&AnalyzeDialog::paint2);
    connect(analyzeFunction,&AnalyzeFunction::finish3,this,&AnalyzeDialog::paint3);
    connect(analyzeFunction,&AnalyzeFunction::finish4,this,&AnalyzeDialog::paint4);


    //初始化页面3中table widget
     ui->tableWidget_user_com->setRowCount(2);  //设置行数
    ui->tableWidget_user_com->setColumnCount(2);  //设置列数
    ui->tableWidget_user_com->setHorizontalHeaderLabels(QStringList()<<"common points"<<" ");

    ui->tableWidget_user_com->setItem(0,0,new QTableWidgetItem("The number of common visited POIs"));
    ui->tableWidget_user_com->setItem(1,0,new QTableWidgetItem("The place which the two meet each other most possibly"));
    ui->tableWidget_user_com->resizeColumnToContents(0);
    ui->tableWidget_user_com->setShowGrid(true);
    ui->tableWidget_user_com->horizontalHeader()->setStyleSheet ("QHeaderView::section {background-color:skyblue}");
    ui->tableWidget_user_com->verticalHeader()->setVisible(false);

    ui->tableWidget_user_dif->setRowCount(3);
    ui->tableWidget_user_dif->setColumnCount(3);
    ui->tableWidget_user_dif->setHorizontalHeaderLabels(QStringList()<<"different points"<<" "<<" ");
    ui->tableWidget_user_dif->setItem(0,0,new QTableWidgetItem("user_id"));
    ui->tableWidget_user_dif->setItem(1,0,new QTableWidgetItem("the total number of checking-ins"));
    ui->tableWidget_user_dif->setItem(2,0,new QTableWidgetItem("the total number of visited POIs"));
    ui->tableWidget_user_dif->resizeColumnToContents(0);
    ui->tableWidget_user_dif->setShowGrid(true);
    ui->tableWidget_user_dif->horizontalHeader()->setStyleSheet ("QHeaderView::section {background-color:skyblue}");
    ui->tableWidget_user_dif->verticalHeader()->setVisible(false);

    ui->tableWidget_dau->setRowCount(2);
    ui->tableWidget_dau->setColumnCount(2);
    ui->tableWidget_dau->setVerticalHeaderLabels(QStringList()<<"location_id"<<"DAU");
    ui->tableWidget_dau->horizontalHeader()->setVisible(false);
    ui->tableWidget_dau->verticalHeader()->setStyleSheet("QHeaderView::section {background-color:skyblue}");


}

AnalyzeDialog::~AnalyzeDialog()
{
    delete ui;
}

void AnalyzeDialog::on_comboBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void AnalyzeDialog::on_btn1_clicked()
{   int u=ui->user_id_1->value();
    QDateTime t1=ui->startTime1->dateTime(),t2=ui->endTime1->dateTime();
    emit signal1(u,t1,t2);
}

void AnalyzeDialog::paint1(QVector<coord1> vectorCoord1,QVector<double> x,QVector<double> y)
{    //绘制直方图
    QChart* mychart= new QChart;
    QBarSeries* bar=new QBarSeries;
    QStringList cate;
    QString str;
    int maxtimes=0;
    QBarSet *set=new QBarSet("TOP 10 popular POIs");
        for(int i=1;i<=10;i++)
        {
            *set<<vectorCoord1.at(i-1).visited_times;
            str=QString::number(vectorCoord1.at(i-1).location_id);
            cate<<str;
            maxtimes=(maxtimes>vectorCoord1.at(i-1).visited_times?maxtimes:vectorCoord1.at(i-1).visited_times);
        }

        QBarCategoryAxis *axisX=new QBarCategoryAxis();
        axisX->append(cate);
        axisX->setTitleText("location_id");

        QValueAxis *axisY=new QValueAxis();
        axisY->setRange(0,maxtimes);
        axisY->setTitleText("visited times");

        bar->attachAxis(axisX);
        bar->append(set);
        bar->setLabelsVisible(true);
        bar->attachAxis(axisY);

        mychart->addAxis(axisX, Qt::AlignBottom);
        mychart->addAxis(axisY, Qt::AlignLeft);
        mychart->addSeries(bar);
        mychart->legend()->setVisible(true);
        mychart->legend()->setAlignment(Qt::AlignBottom);
        mychart->legend()->setAlignment(Qt::AlignLeft);
        mychart->setAnimationOptions(QChart::SeriesAnimations);

        ui->widget1->setChart(mychart);


        //绘制折线图

        QChart *chart=new QChart;
        chart->setTitle("rank-visited times");
        QLineSeries* series=new QLineSeries;
        series->setName("visited times");
        chart->addSeries(series);

        for(int i=0;i<x.size();i++)
        {
            series->append(x[i],y[i]);
                qDebug()<<"i="<<i<<" x="<<x.at(i)<<" y="<<y.at(i);
        }
        //series->setPointLabelsVisible();
        //series->setPointLabelsFormat("(@xPoint,@yPoint)");


        //创建坐标
        QValueAxis *axisX2=new QValueAxis;

        double eleven=11;

        axisX2->setRange(1,eleven);
        axisX2->setTitleText("rank");
        //axisX->setTickCount(10); //主分隔个数：x分成几个单位
        //axisX->setMinorTickCount(0);//每个单位之间绘制多少虚网格

        QValueAxis*axisY2=new QValueAxis;
        axisY2->setRange(0,y[18]);
        axisY2->setTitleText("visited times");
       // axisY->setTickCount(10); //主分隔个数：x分成几个单位
        //axisY->setMinorTickCount(1);//每个单位之间绘制多少虚网格
        chart->setAxisX(axisX2,series);
        chart->setAxisY(axisY2,series);
        ui->widget_chart_page1->setChart(chart);


}

void AnalyzeDialog::on_btn2_clicked()
{
    int locationid=ui->loc_id_2->value();
    QDateTime s=ui->startTime2->dateTime(),e=ui->endTime2->dateTime();
    emit signal2(locationid,s,e);
}
void AnalyzeDialog::paint2(QVector<coord2> vectorCoord2,QVector<double> x,QVector<double> y)
{
//绘制直方图
    QChart* mychart= new QChart;
    QBarSeries* bar=new QBarSeries;
    QStringList cate;
    QString str;
    int maxtimes=0;
    QBarSet *set=new QBarSet("10 Most frequently visiting users");
        for(int i=0;i<10;i++)
        {
            *set<<vectorCoord2.at(i).visited_times;
            str=QString::number(vectorCoord2.at(i).user_id);
            cate<<str;
            maxtimes=( maxtimes>vectorCoord2.at(i).visited_times? maxtimes:vectorCoord2.at(i).visited_times );
            qDebug()<<str<<" "<<vectorCoord2.at(i).visited_times;
        }
        //return ;
        QBarCategoryAxis *axisX=new QBarCategoryAxis();
        axisX->append(cate);
        axisX->setTitleText("user_id");

        QValueAxis *axisY=new QValueAxis();
        axisY->setRange(0,maxtimes);
        axisY->setTitleText("visited times");

        bar->attachAxis(axisX);
        bar->append(set);
        bar->setLabelsVisible(true);
        bar->attachAxis(axisY);

        mychart->addAxis(axisX, Qt::AlignBottom);
        mychart->addAxis(axisY, Qt::AlignLeft);
        mychart->addSeries(bar);
        mychart->legend()->setVisible(true);
        mychart->legend()->setAlignment(Qt::AlignBottom);
        mychart->legend()->setAlignment(Qt::AlignLeft);
        mychart->setAnimationOptions(QChart::SeriesAnimations);

        ui->widget2->setChart(mychart);

        //绘制折线图
        QChart *chart=new QChart;
        chart->setTitle("rank-visited times");
        QLineSeries* series=new QLineSeries;
        series->setName("visited times");
        chart->addSeries(series);

        for(int i=0;i<x.size();i++)
        {
            series->append(x[i],y[i]);
                qDebug()<<"i="<<i<<" x="<<x.at(i)<<" y="<<y.at(i);
        }
        //series->setPointLabelsVisible();
        //series->setPointLabelsFormat("(@xPoint,@yPoint)");


        //创建坐标
        QValueAxis *axisX2=new QValueAxis;
        double eleven=11;

        axisX2->setRange(1,eleven);
        axisX2->setTitleText("rank");
        //axisX->setTickCount(10); //主分隔个数：x分成几个单位
        //axisX->setMinorTickCount(0);//每个单位之间绘制多少虚网格

        QValueAxis*axisY2=new QValueAxis;
        axisY2->setRange(0,y[18]);
        axisY2->setTitleText("visited times");
       // axisY->setTickCount(10); //主分隔个数：x分成几个单位
        //axisY->setMinorTickCount(1);//每个单位之间绘制多少虚网格
        chart->setAxisX(axisX2,series);
        chart->setAxisY(axisY2,series);
        ui->widget_chart_page2->setChart(chart);

}

void AnalyzeDialog::on_btn3_clicked()
{   int u1=ui->userid1_3->value(),u2=ui->userid2_3->value();
    QDateTime t1=ui->startTime3->dateTime(),t2=ui->endTime3->dateTime();
    emit signal3(u1,u2,t1,t2);
}
void AnalyzeDialog::paint3(data_result_3 data)
{   qDebug()<<"data.comPOIid.size="<<data.comPOIid.size();
    ui->tableWidget_user_com->setItem(0,1,new QTableWidgetItem(QString::number(data.comPOIid.size())));
    ui->tableWidget_user_com->setItem(1,1,new QTableWidgetItem(QString::number(data.maxComId)));

    ui->tableWidget_user_dif->setItem(0,1,new QTableWidgetItem(QString::number(ui->userid1_3->value())));
    ui->tableWidget_user_dif->setItem(0,2,new QTableWidgetItem(QString::number(ui->userid2_3->value())));
    ui->tableWidget_user_dif->setItem(1,1,new QTableWidgetItem(QString::number(data.totalTimes1)));
    ui->tableWidget_user_dif->setItem(1,2,new QTableWidgetItem(QString::number(data.totalTimes2)));
    ui->tableWidget_user_dif->setItem(2,1,new QTableWidgetItem(QString::number(data.totalPlaces1)));
    ui->tableWidget_user_dif->setItem(2,2,new QTableWidgetItem(QString::number(data.totalPlaces2)));

}

void AnalyzeDialog::on_btn4_clicked()
{
    int loc1=ui->loc_id1_4->value(),loc2=ui->loc_id2_4->value();
    QDate date=ui->dateEdit->date();
    emit signal4(loc1,loc2,date);
}

void AnalyzeDialog::paint4(DAU4 res)
{   ui->tableWidget_dau->setItem(0,0,new QTableWidgetItem(QString::number(ui->loc_id1_4->value())));
    ui->tableWidget_dau->setItem(1,0,new QTableWidgetItem(QString::number(ui->loc_id2_4->value())));
    ui->tableWidget_dau->setItem(0,1,new QTableWidgetItem(QString::number(res.dau1)));
    ui->tableWidget_dau->setItem(1,1,new QTableWidgetItem(QString::number(res.dau2)));


    QChart* mychart= new QChart;
    QBarSeries* bar=new QBarSeries;
    QStringList cate;
    QString str;
    int maxtimes=0;
    QBarSet *set=new QBarSet("two locations' DAU");

    *set<<res.dau1<<res.dau2;
    cate<<QString::number(ui->loc_id1_4->value())<<QString::number(ui->loc_id2_4->value());

    maxtimes=( res.dau1>res.dau2? res.dau1:res.dau2 );

        QBarCategoryAxis *axisX=new QBarCategoryAxis();
        axisX->append(cate);
        axisX->setTitleText("location_id");

        QValueAxis *axisY=new QValueAxis();
        axisY->setRange(0,maxtimes);
        axisY->setTitleText("DAU");

        bar->attachAxis(axisX);
        bar->append(set);
        bar->setLabelsVisible(true);
        bar->attachAxis(axisY);

        mychart->addAxis(axisX, Qt::AlignBottom);
        mychart->addAxis(axisY, Qt::AlignLeft);
        mychart->addSeries(bar);
        mychart->legend()->setVisible(true);
        mychart->legend()->setAlignment(Qt::AlignBottom);
        mychart->legend()->setAlignment(Qt::AlignLeft);
        mychart->setAnimationOptions(QChart::SeriesAnimations);

        ui->widget4->setChart(mychart);
}
