#include "loaddialog.h"
#include "ui_loaddialog.h"

LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
    thread1=new QThread;
    InputFilter*inputFilter=new InputFilter;
    inputFilter->moveToThread(thread1);
    thread1->start();
     //connect(ui->buttonBox,&QDialogButtonBox::clicked,this,&LoadDialog::close);
     connect(ui->loadBtn,&QPushButton::clicked,[=](){
        QString path=QFileDialog::getOpenFileName(this,"Open the file","D:","*.csv");
        QFile *file=new QFile(path);
        file->open(QFileDevice::ReadOnly);
        QDateTime begin=ui->beginDateTimeEdit->dateTime(),end=ui->endDateTimeEdit->dateTime();
        float minla=ui->doubleSpinBox_minla->value(),maxla=ui->doubleSpinBox_maxla->value();
        float minlong=ui->doubleSpinBox_minlong->value(),maxlong=ui->doubleSpinBox_maxlong->value();
        emit filter(begin,end,minla,maxla,minlong,maxlong,file);
    });
    connect(this,&LoadDialog::filter,inputFilter,&InputFilter::filter);
    connect(inputFilter,&InputFilter::progress,ui->progressBar,&QProgressBar::setValue);
    //connect(inputFilter,&InputFilter::inputResult,this,&LoadDialog::loadResult);
    connect(inputFilter,&InputFilter::finish_filter,[=](){
        list=inputFilter->inputResult();
        user=inputFilter->userResult();
        location=inputFilter->locationResult();
        qDebug()<<"init loadDia para suc";
        emit load_finish();
        qDebug()<<"load finish suc";
        qDebug()<<"load dia's user.size()="<<user.size();

    });
    //emit load_finish();
}


LoadDialog::~LoadDialog()
{
    delete ui;
}



void LoadDialog::on_pushButton_clicked()
{
    close();
}
