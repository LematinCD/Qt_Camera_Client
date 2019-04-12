#include <QtGui/QApplication>
#include "clinetmainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClinetMainWindow w;
    LoginDialog logindialog;
    RegisterDialog registerdialog;

    QObject::connect(&registerdialog,SIGNAL(register_sig(QString,QString)),&w,SLOT(registerNamePasswd(QString,QString)));
    QObject::connect(&logindialog,SIGNAL(adminInfo_signals(QString,QString)),&w,SLOT(writeAdminNamePassWord(QString,QString)));

    QObject::connect(&logindialog,SIGNAL(sig_IpAndPort(QString,int)),&w,SLOT(setIPandPort(QString,int)));

    QObject::connect(&w,SIGNAL(userLoginSuccess_signal()),&logindialog,SLOT(close()));
    QObject::connect(&w,SIGNAL(userLoginFailed_siganl()),&logindialog,SLOT(slt_loginError()));


    QObject::connect(&logindialog,SIGNAL(sig_quit()),&a,SLOT(quit()));
    logindialog.show();



    
    return a.exec();
}
