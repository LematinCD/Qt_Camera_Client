#ifndef NETWORKCONFIGDIALOG_H
#define NETWORKCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class NetWorkConfigDialog;
}

class NetWorkConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NetWorkConfigDialog(QWidget *parent = 0,const QString &networkFileName = "myNcetworkConfig.conf");
    ~NetWorkConfigDialog();
    QString getIP() const {return defaultIp;};
    int getPort() const {return defaultPort;};


signals:
    void hostAddressAndIP_signal(const QString &address,int port);

private slots:
    void okBtn_slots();
    void slt_selectHostHistoryData(const QString indexText);
    void slt_clearHostHistoryData();


    
private:
    Ui::NetWorkConfigDialog *ui;
    QString myNetworkConfig;
    QString defaultIp;
    int defaultPort;


    void setDefaultIPandPort();
    void writeHostData();
    void readHostData();
};

#endif // NETWORKCONFIGDIALOG_H
