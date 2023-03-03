#include "mapform.h"
#include "ui_mapform.h"

MapForm::MapForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapForm)
{
    ui->setupUi(this);
    QString mappathA = ":/map/baiduMap.html";
}

MapForm::~MapForm()
{
    delete ui;
}
