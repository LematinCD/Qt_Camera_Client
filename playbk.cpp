#include "playbk.h"
#include "ui_playbk.h"
#include "qdir.h"
#include <QDebug>

Playbk::Playbk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Playbk)
{
    ui->setupUi(this);

    i=0;
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(playback()));
    connect(ui->slider,SIGNAL(sliderMoved(int)),this,SLOT(playback()));
}

void Playbk::playback()
{
    QDir dir("./camerapho/");
    filters<<"*.jpg";
    dir.setNameFilters(filters);
    infoList = dir.entryInfoList();

    fileInfo=infoList.at(i);
    pixname = fileInfo.fileName();
    showimage.load("./camerapho/"+pixname);
    ui->label->setPixmap(QPixmap::fromImage(showimage).scaled(ui->label->width(),ui->label->height()));

    ui->slider->setMinimum(0);
    ui->slider->setMaximum(infoList.count()-1);
    ui->slider->setValue(i);

    i += 1;
    if(i>=infoList.count())
        i=0;
}

Playbk::~Playbk()
{
    delete ui;
}

void Playbk::on_pushButton_clicked()
{
    timer->start(20);
}
