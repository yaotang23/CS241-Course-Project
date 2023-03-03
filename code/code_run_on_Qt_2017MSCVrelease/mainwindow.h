#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include"analyzedialog.h"
#include"paintdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<cknode> cklist;
    QVector<QVector<cknode>> user;
    QVector<QVector<cknode>> location;
    PaintDialog* paintDialog;
signals:
    void filter(QDateTime begin,QDateTime end,float minla,float maxla,float minlong,float maxlong,QFile* file);
private slots:
    void recvInput(QVector<cknode> list){cklist=list;}
    //void on_analyzeBtn_clicked();
    void on_mapBtn_clicked();
};
#endif // MAINWINDOW_H
