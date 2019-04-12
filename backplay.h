#ifndef BACKPLAY_H
#define BACKPLAY_H

#include <QWidget>

namespace Ui {
class backplay;
}

class backplay : public QWidget
{
    Q_OBJECT
    
public:
    explicit backplay(QWidget *parent = 0);
    ~backplay();
    Ui::backplay *ui;
private:

};

#endif // BACKPLAY_H
