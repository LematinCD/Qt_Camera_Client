#include "picenv.h"
#include "ui_picenv.h"
//#include<widget.h>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include<qcustomplot.h>
Picenv::Picenv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Picenv)
{
    ui->setupUi(this);
    ui->label1->setMaximumHeight(30);
    ui->label2->setMaximumHeight(30);
    ui->label3->setMaximumHeight(30);
    ui->label4->setMaximumHeight(30);
    ui->label5->setMaximumHeight(30);
    setupRealtimeDataDemo(ui->customPlot,20,30);
    ui->frame_2->replot();
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible


    setupRealtimeDataDemo(ui->frame_2,30,40);
    ui->frame_3->replot();
    connect(&dataTimer1, SIGNAL(timeout()), this, SLOT(realtimeDataSlothum()));
    dataTimer1.start(0); // Interval 0 means to refresh as fast as possible



    setupRealtimeDataDemoxyz(ui->frame_3,-8,8);
    ui->frame_3->replot();
    connect(&dataTimer2, SIGNAL(timeout()), this, SLOT(realtimeDataSlotlight()));
    dataTimer2.start(0); // Interval 0 means to refresh as fast as possible


    setupRealtimeDataDemo(ui->frame_4,0,3.5);
    ui->frame_4->replot();
    connect(&dataTimer3, SIGNAL(timeout()), this, SLOT(realtimeDataSlotvate()));
    dataTimer3.start(0); // Interval 0 means to refresh as fast as possible

    //test = new ClinetMainWindow(this);
    //connect(test,SIGNAL(sendToPicenv(QByteArray)),this,SLOT(revcmd(QByteArray)));

}

Picenv::~Picenv()
{
    delete ui;
}

void Picenv::setupRealtimeDataDemo(QCustomPlot *customPlot,int i,int j)
{

    demoName = "Real Time Data Demo";


      customPlot->addGraph(); // red line
      customPlot->graph(0)->setPen(QPen(QColor(255, 110, 40)));

      QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
      timeTicker->setTimeFormat("%h:%m:%s");
      customPlot->xAxis->setTicker(timeTicker);
      customPlot->yAxis->setRange(i,j);
      connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
      connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
      customPlot->graph(0)->rescaleAxes(true);
      customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
      customPlot->axisRect()->setupFullAxesBox();
      customPlot->rescaleAxes();

}

void Picenv::setupRealtimeDataDemoxyz(QCustomPlot *customPlot, int i, int j)
{
    customPlot->addGraph(); // red line
    customPlot->graph(0)->setPen(QPen(QColor(255, 110, 40)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(10, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(2)->setPen(QPen(QColor(165, 0, 100)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->yAxis->setRange(i,j);
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    customPlot->graph(0)->rescaleAxes(true);
    customPlot->graph(1)->rescaleAxes(true);
    customPlot->graph(2)->rescaleAxes(true);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();


}

void Picenv::realtimeDataSlot()
{
   // qDebug()<<"********"<<endl;
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 2) // at most add point every 2 ms
    {
      // add data to lines:
        ui->customPlot->graph(0)->addData(key, oder[5]+oder[6]*0.1);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      lastFpsKey = key;
      frameCount = 0;
    }


}

void Picenv::realtimeDataSlothum()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 2) // at most add point every 2 ms
    {
      // add data to lines:
        ui->frame_2->graph(0)->addData(key, oder[7]);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->frame_2->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->frame_2->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      lastFpsKey = key;
      frameCount = 0;
    }
}

void Picenv::realtimeDataSlotvate()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 2) // at most add point every 2 ms
    {
      // add data to lines:
        ui->frame_3->graph(0)->addData(key, (signed)oder[8]);
        ui->frame_3->graph(1)->addData(key, (signed)oder[9]);
        ui->frame_3->graph(2)->addData(key, (signed)oder[10]);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->frame_3->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->frame_3->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      lastFpsKey = key;
      frameCount = 0;
    }

}

void Picenv::realtimeDataSlotlight()
{

    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 2) // at most add point every 2 ms
    {
      // add data to lines:
        ui->frame_4->graph(0)->addData(key, oder[12]*0.1);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->frame_4->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->frame_4->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      lastFpsKey = key;
      frameCount = 0;
    }
}






void Picenv::revcmd(QByteArray bufcmd)
{
    oder=bufcmd;
}
