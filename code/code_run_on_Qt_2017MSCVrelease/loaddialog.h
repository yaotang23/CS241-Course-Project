#ifndef LOADDIALOG_H
#define LOADDIALOG_H

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
#include<QAbstractButton>
namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = nullptr);
    QVector<cknode> loadResult(){return list;}
    ~LoadDialog();
    QThread* thread1;
    QVector<QVector<cknode>> userResult(){return user;}
    QVector<QVector<cknode>> locationResult(){return location;}
signals:

        void filter(QDateTime begin,QDateTime end,float minla,float maxla,float minlong,float maxlong,QFile* file);
        void load_finish();
private slots:

        void on_pushButton_clicked();

private:
    Ui::LoadDialog *ui;
    QVector<cknode> list;
    //记录userid=i的user的签到记录序号
    QVector<QVector<cknode>> user;
    //记录location id=i的location的签到记录序号
    QVector<QVector<cknode>> location;


};

#endif // LOADDIALOG_H
