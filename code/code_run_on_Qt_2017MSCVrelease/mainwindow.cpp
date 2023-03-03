#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"loaddialog.h"
#include"paintdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadDialog* loadDialog=new LoadDialog;
    paintDialog=new PaintDialog;
    connect(ui->loadBtn,&QPushButton::clicked,[=](){


        loadDialog->show();
        //qDebug()<<"show loadDialog successfully";
    });
    connect(loadDialog,&LoadDialog::load_finish,[=](){
        cklist=loadDialog->loadResult();
        user=loadDialog->userResult();
       location=loadDialog->locationResult();
       //qDebug()<<cklist.size();
       //qDebug()<<user.size();
       //qDebug()<<location.size();
       qDebug()<<"main window's user.size()="<<user.size();
    });
    connect(ui->analyzeBtn,&QPushButton::clicked,[=](){
        AnalyzeDialog* analyzeDialog=new AnalyzeDialog;
        analyzeDialog->init(cklist,user,location);
        qDebug()<<"initialize anadia suc";
        analyzeDialog->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}









void MainWindow::on_mapBtn_clicked()
{
    //PaintDialog* paintDialog=new PaintDialog(this);
    paintDialog->init(this->cklist,user,location);
    paintDialog->show();


}
