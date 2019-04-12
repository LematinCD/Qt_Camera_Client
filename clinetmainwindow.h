#ifndef CLINETMAINWINDOW_H
#define CLINETMAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QLabel>
#include "picenv.h"
#include "playbk.h"

class ClientSocket;
class LoginDialog;
class Playbk;

namespace Ui {
class ClinetMainWindow;
}

class ClinetMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ClinetMainWindow(QWidget *parent = 0);
    ~ClinetMainWindow();
    

signals:
    void connectError();//连接出错
    void userLoginSuccess_signal();
    void userLoginFailed_siganl();
    void sendToPicenv_signal(QByteArray);

public slots:
    void setIPandPort(const QString& add, int p);//接受网络配置的参数

    void vedioData_slots(const QByteArray &data);//isCam
    void sensorData_slots(const QByteArray &data);//isCam
    void cmdData_slots(int cmd, const QByteArray &data);//isADMIN
    void writeCmdContext(const QByteArray&context);//isCmd

    void userLoginSuccess_slots();
    void userLoginFailed_slots();
    void picenvShow();
    void playbkShow();


private slots:
    void writeAdminNamePassWord(const QString &name,const QString &password);
    void registerNamePasswd(const QString &name,const QString &password);
    void slt_openCamera();
    void slt_closeCamera();

    void slt_openSenSor();
    void slt_closeSensor();

    void slt_openLight();
    void slt_closeLight();

    void requestDEVname();
    void slt_networkException();

    void timerUpdate();

private:
    Ui::ClinetMainWindow *ui;
    QImage *image;
    QLabel *timelabel;
    QTimer *timerdata;
    QTimer *timecmd;


    //QAction *adminLogin;

    QHostAddress address;
    int port;
    int j;

    ClientSocket *cmdSocket;//完成admin命令的socket
    ClientSocket *vedioSocket;//接受视频数据的socket
    ClientSocket *sensorSocket;//接受传感器数据数据的socket
    Picenv *picenv;
    Playbk *playbk;

    void initUI();
    void connects();
    void socketInit();
    void devinfo(const QByteArray &context);

    bool cmdSocketConnectHost();
    bool voideSocketConnectHost();
    bool sensorSocketConnectHost();

    bool isQuitNormal;
    bool isAdmin;
};

#endif // CLINETMAINWINDOW_H
