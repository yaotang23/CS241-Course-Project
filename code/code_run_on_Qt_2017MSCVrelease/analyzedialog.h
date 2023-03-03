#ifndef ANALYZEDIALOG_H
#define ANALYZEDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include<QFileDialog>
#include<QFile>
#include<QVector>
#include<QStringList>
#include<QDebug>
#include<inputfilter.h>
#include<QDateTime>
#include<QString>
#include<QThread>
#include"inputfilter.h"
#include"analyzefunction.h"
#include"interpolation.h"
#include<QAbstractButton>
#include<QtCharts>
#include<QChart>
namespace Ui {
class AnalyzeDialog;
}

class AnalyzeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyzeDialog(QWidget *parent = nullptr);
    void init(QVector<cknode> a,QVector<QVector<cknode>> b,QVector<QVector<cknode>> c)
    {
        this->cklist=a;
        this->user=b;
        this->location=c;
        analyzeFunction->init_f(cklist,user,location);
        qDebug()<<"ana dialog's user.size()="<<user.size();
        qDebug()<<"ana dialog's location.size()="<<location.size();

    }
    QChart * createBarChart() const; // 绘制自定义的柱状图
    ~AnalyzeDialog();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_btn1_clicked();
    void paint1(QVector<coord1> vectorCoord1,QVector<double> x,QVector<double> y);
    void paint2(QVector<coord2> vectorCoord2,QVector<double> x,QVector<double> y);
    void paint3(data_result_3);
    void paint4(DAU4 res);

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

private:
    Ui::AnalyzeDialog *ui;
    AnalyzeFunction* analyzeFunction;
    QVector<cknode> cklist;
    //记录userid=i的user的签到记录序号
    QVector<QVector<cknode>> user;
    //记录location id=i的location的签到记录序号
    QVector<QVector<cknode>> location;
    QThread *thread2;
signals:
    void signal1(int userid,QDateTime s,QDateTime e);
    void signal2(int location_id,QDateTime startTime,QDateTime endTime);
    void signal3(int u1,int u2,QDateTime t1,QDateTime t2);
    void signal4(int l1,int l2,QDate date);


};

#endif // ANALYZEDIALOG_H
