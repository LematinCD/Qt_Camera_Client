#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include "networkconfigdialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginDialog::LoginDialog(QWidget *parent,const QString &networkFileName) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->cmbAdmin->setEditable(true);
    networkConfigDialog = new NetWorkConfigDialog(this,networkFileName);
    connect(networkConfigDialog,SIGNAL(hostAddressAndIP_signal(QString,int)),this,SLOT(slt_IpAndPortConfigure(QString,int)));//设置IP和端口号
    connect(ui->btnNetConfig,SIGNAL(clicked()),networkConfigDialog,SLOT(show()));

    registerdialog = new RegisterDialog(this);
    connect(ui->btnRegister,SIGNAL(clicked()),registerdialog,SLOT(show()));

    connect(ui->btnLogin,SIGNAL(clicked()),this,SLOT(btnLogin_slot()));//登录
    ui->btnLogin->setDefault(true);
    connect(ui->btnQuit,SIGNAL(clicked()),this,SIGNAL(sig_quit()));//退出
    connect(ui->btnClearHistory,SIGNAL(clicked()),this,SLOT(slt_clearHistoryData()));//清除用户信息
    connect(ui->cmbAdmin,SIGNAL(activated(QString)),this,SLOT(slt_comboxIsSelected(QString)));//选择用户名
    readLoginInfo();//读取本地用户信息
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

/*登录*/
void LoginDialog::btnLogin_slot()
{
    QString name = ui->cmbAdmin->currentText();
    QString password = ui->lineEditPasswd->text();
    if (name.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this,tr("information"),tr("is Empty!"));
        return;
    }

    emit adminInfo_signals(name,password);
    if (ui->checkBoxPasswd->checkState() != Qt::Unchecked)
        writeNamePasswordIntoFile(name,password);//登录信息存入本地,记住密码和用户名
}






/*修改登录主机和端口号*/
void LoginDialog::slt_IpAndPortConfigure(const QString &ip, int port)
{
    emit sig_IpAndPort(ip,port);
}



/*保存用户名和密码到本地*/
void LoginDialog::writeNamePasswordIntoFile(const QString &name, const QString &password)
{
    QFile file("historyLogin.txt");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    in << name << ' ' << password << '\n';

    file.close();
}
/*从本地读取用户名和密码*/
void LoginDialog::readLoginInfo()
{
    QFile file("historyLogin.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        NamePasswordQPair t;
        t.first = temp.left(temp.indexOf(' '));
        t.second = temp.right(temp.length() - temp.indexOf(' ') - 1);
        list_namepassword.append(t);
        temp = out.readLine();
        ui->cmbAdmin->addItem(t.first);
    }
    file.close();
}
/*选择用户名和密码*/
void LoginDialog::slt_clearHistoryData()
{
    QFile file("historyLogin.txt");
    file.resize(0);
    list_namepassword.clear();
    ui->cmbAdmin->clear();
    ui->lineEditPasswd->clear();
}
/*清除本地的用户名和密码*/
void LoginDialog::slt_comboxIsSelected(const QString &text)
{
    foreach (const NamePasswordQPair& t, list_namepassword) {
        if (text == t.first) {
            ui->lineEditPasswd->setText(t.second);
            return;
        }

    }
}

/*连接出错*/
void LoginDialog::slt_connectError()
{
    QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("无法连接到主机，请查看网络配置!"));
}

void LoginDialog::slt_loginError()
{
    QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("登录失败!请检查用户名和密码!"));
}

void LoginDialog::showEvent(QShowEvent *)
{
    emit sig_IpAndPort(networkConfigDialog->getIP(),networkConfigDialog->getPort());
}

