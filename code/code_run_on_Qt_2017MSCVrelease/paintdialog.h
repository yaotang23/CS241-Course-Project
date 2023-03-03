#ifndef PAINTDIALOG_H
#define PAINTDIALOG_H

#include <QDialog>
#include"inputfilter.h"
#include"usermap.h"
#include<QWebEngineView>
namespace Ui {
class PaintDialog;
}

class PaintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaintDialog(QWidget *parent = 0);
    void init(QVector<cknode> &a,QVector<QVector<cknode>> &b,QVector<QVector<cknode>> &c)
    {
        this->list=a;
        this->user=b;
        this->location=c;

        qDebug()<<"paint dialog's user.size()="<<user.size();
        qDebug()<<"paint dialog's location.size()="<<location.size();
        userMap->init(a,b,c);
    }
    ~PaintDialog();
signals:
    void paintUserMap(int user_id);
    void paintLocMap(int loc_id);
private slots:
    void on_pushButton_paint_user_clicked();
    void paint_user(QVector<cknode>);
    void paint_loc(QVector<cknode>);

    void on_pushButton_paint_location_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_pre_clicked();

    void on_pushButton_clicked();

private:
    Ui::PaintDialog *ui;
    QThread* thread3;

    UserMap *userMap;
    QWebEngineView *webEngineView;
    QWebEngineView *webEngineView2;
    QVector<cknode> list;
    //记录userid=i的user的签到记录序号
    QVector<QVector<cknode>> user;
    //记录location id=i的location的签到记录序号
    QVector<QVector<cknode>> location;

};

#endif // PAINTDIALOG_H
