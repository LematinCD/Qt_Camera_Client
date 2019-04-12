#ifndef PLAYBK_H
#define PLAYBK_H

#include <QWidget>
#include <qtimer.h>
#include <QFileInfo>

namespace Ui {
class Playbk;
}

class Playbk : public QWidget
{
    Q_OBJECT
    
public:
    explicit Playbk(QWidget *parent = 0);
    ~Playbk();
    
public slots:
    void playback();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Playbk *ui;

    QImage showimage;
    QString pixname;
    QTimer *timer;
    QStringList filters;
    QFileInfoList infoList;
    QFileInfo fileInfo;
    int i;
};

#endif // PLAYBK_H
