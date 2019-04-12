#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class NetWorkConfigDialog;
class RegisterDialog;

typedef QPair<QString,QString> NamePasswordQPair;
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0,const QString &networkFileName = "myNcetworkConfig.conf");
    ~LoginDialog();



signals:
    void adminInfo_signals(const QString& name,const QString &password);
    void sig_IpAndPort(const QString &ip,int port);
    void sig_quit();


public slots:
    void slt_connectError();
    void slt_loginError();

private slots:
    void btnLogin_slot();
    void slt_IpAndPortConfigure(const QString &ip,int port);//接受自定义的网络配置
    void slt_comboxIsSelected(const QString &text);
    void slt_clearHistoryData();



protected:
    void showEvent(QShowEvent *);
    
private:
    Ui::LoginDialog *ui;
    NetWorkConfigDialog *networkConfigDialog;
    RegisterDialog *registerdialog;
    QList<NamePasswordQPair> list_namepassword;

    void writeNamePasswordIntoFile(const QString& name,const QString& password);
    void readLoginInfo();
};

#endif // LOGINDIALOG_H
