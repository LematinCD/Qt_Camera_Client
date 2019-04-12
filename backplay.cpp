#include "backplay.h"
#include "ui_backplay.h"
#include <QDebug>

backplay::backplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::backplay)
{
    qDebug()<<"------------2----------";
    ui->setupUi(this);
}

backplay::~backplay()
{
    delete ui;
}
