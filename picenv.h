#ifndef PICENV_H
#define PICENV_H

#include <QWidget>
#include<qcustomplot.h>
#include<QTimer>


namespace Ui {
class Picenv;
}

class Picenv : public QWidget
{
    Q_OBJECT
protected slots:
    void revcmd(QByteArray bufcmd);
    void realtimeDataSlot();
    void realtimeDataSlothum();
    void realtimeDataSlotvate();
    void realtimeDataSlotlight();
public:
    explicit Picenv(QWidget *parent = 0);
    ~Picenv();
    void setupRealtimeDataDemo(QCustomPlot *customPlot,int i,int j);
    void setupRealtimeDataDemoxyz(QCustomPlot *customPlot,int i,int j);
    //ClinetMainWindow *test;
    Ui::Picenv *ui;
private:
       QString demoName;
       QTimer dataTimer;
       QTimer dataTimer1;
       QTimer dataTimer2;
       QTimer dataTimer3;
       QByteArray oder;

};

#endif // PICENV_H
