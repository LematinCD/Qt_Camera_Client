#include "clinetmainwindow.h"
#include "ui_clinetmainwindow.h"
#include "clientsocket.h"
#include "CommandType.h"
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

ClinetMainWindow::ClinetMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClinetMainWindow)
{
    j=10000000;
    picenv = new Picenv;
    playbk = new Playbk;
    ui->setupUi(this);
    cmdSocket=NULL;
    vedioSocket = NULL;
    sensorSocket = NULL;
    initUI();
    connects();
    socketInit();
    image = new QImage();
    //ui->labVideo->setText("123");
    //ui->labVideo->setPixmap(QPixmap("1.jpg"));
    timelabel=new QLabel(ui->labVideo);
    //timelabel->setText("11:04");
    timelabel->setStyleSheet("color:white;font-size:20px");

    timelabel->setMinimumWidth(400);
    timerdata = new QTimer(this);
    connect(timerdata,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timerdata->start(1000);

    connect(this,SIGNAL(sendToPicenv_signal(QByteArray)),picenv,SLOT(revcmd(QByteArray)));
    connect(ui->btnPicenv,SIGNAL(clicked()),this,SLOT(picenvShow()));
    connect(ui->pushButtonback,SIGNAL(clicked()),SLOT(playbkShow()));
    /*timecmd=new QTimer(this);
    connect(timecmd,SIGNAL(timeout()),this,SLOT(updatacmd()));
    timecmd->start(2000);*/
}

ClinetMainWindow::~ClinetMainWindow()
{
    delete ui;
    delete image;
}


void ClinetMainWindow::initUI()
{

    //adminLogin = new QAction(tr("adminLogin"),this);
    ui->btnCloseCamera->setDisabled(true);
    ui->btnCloseSensor->setDisabled(true);
    //ui->btnCloseLight->setDisabled(true);
    //adminLogin->setDisabled(true);
}

void ClinetMainWindow::connects()
{
    connect(ui->btnOpenCamera,SIGNAL(clicked()),this,SLOT(slt_openCamera()));
    connect(ui->btnCloseCamera,SIGNAL(clicked()),this,SLOT(slt_closeCamera()));

    connect(ui->btnOpenSeneor,SIGNAL(clicked()),this,SLOT(slt_openSenSor()));
    connect(ui->btnCloseSensor,SIGNAL(clicked()),this,SLOT(slt_closeSensor()));

    connect(ui->btnOpenLight,SIGNAL(clicked()),this,SLOT(slt_openLight()));
    connect(ui->btnCloseLight,SIGNAL(clicked()),this,SLOT(slt_closeLight()));
}

void ClinetMainWindow::socketInit()
{
    if(NULL == cmdSocket ){
           cmdSocket = new ClientSocket(this);
           connect(cmdSocket,SIGNAL(returnCmdContext(int,QByteArray)),this,SLOT(cmdData_slots(int,QByteArray)));
           connect(cmdSocket,SIGNAL(LoginSuccess_sig()),this,SLOT(userLoginSuccess_slots()));
           connect(cmdSocket,SIGNAL(LoginFailed_sig()),this,SLOT(userLoginFailed_slots()));
           connect(cmdSocket,SIGNAL(disconnected()),this,SLOT(slt_networkException()));

    }
    if(NULL == vedioSocket){
        vedioSocket = new ClientSocket(this);

        connect(vedioSocket,SIGNAL(videoDataCome(QByteArray)),this,SLOT(vedioData_slots(QByteArray)));
        //connect(vedioSocket,SIGNAL(returnCmdContext(int,QByteArray)),this,SLOT(cmdData_slots(int,QByteArray)));
        connect(vedioSocket,SIGNAL(disconnected()),this,SLOT(slt_networkException()));
    }
    if(NULL == sensorSocket){
        sensorSocket = new ClientSocket(this);

        connect(sensorSocket,SIGNAL(sensorDataCome(QByteArray)),this,SLOT(sensorData_slots(QByteArray)));
        //connect(sensorSocket,SIGNAL(returnCmdContext(int,QByteArray)),this,SLOT(cmdData_slots(int,QByteArray)));
        connect(sensorSocket,SIGNAL(sensorDataCome(QByteArray)),this,SIGNAL(sendToPicenv_signal(QByteArray)));
        connect(sensorSocket,SIGNAL(disconnected()),this,SLOT(slt_networkException()));

    }

}

/*****************************************注册---登录---更改密码**************************************************/

void ClinetMainWindow::registerNamePasswd(const QString &name, const QString &password)
{
    /*确认是否连接上*/
    if (!cmdSocketConnectHost()) {

        emit connectError();
    }
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);

    /***************************自定义通信协议*******************************/
    out <<(int)0;
    out<<(unsigned char)Register;
    out << name;
    out <<password;

    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    cmdSocket->writeCMD(buffer);

}

/*发送登录信息*/
void ClinetMainWindow::writeAdminNamePassWord(const QString &name, const QString &password)
{
    /*确认是否连接上*/
    if (!cmdSocketConnectHost()) {

        emit connectError();
    }
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);
    out <<(int)0;
    out<<(unsigned char)Login;
    out << name;
    out <<password;

    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    cmdSocket->writeCMD(buffer);
}
void ClinetMainWindow::userLoginSuccess_slots()
{

    //requestDEVname();
    emit userLoginSuccess_signal();
    //showMaximized();
    show();

}
void ClinetMainWindow::userLoginFailed_slots()
{
    emit userLoginFailed_siganl();
}

void ClinetMainWindow::picenvShow()
{
    picenv->show();
}

void ClinetMainWindow::playbkShow()
{
    qDebug()<<"-------------";
    playbk->show();

}

bool ClinetMainWindow::cmdSocketConnectHost()
{
    if (cmdSocket->state() == QAbstractSocket::ConnectedState)
    {

        return true;
    }
    cmdSocket->connectToHost(address,port);
    if(!cmdSocket ->waitForConnected(6000))
    {

        return false;
    }
    return true;
}


void ClinetMainWindow::slt_closeLight()
{
    /*确认是否连接上*/
    if (!cmdSocketConnectHost()) {

        emit connectError();
    }
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);
    out <<(int)0;
    out<<(unsigned char)Close_Fan;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    cmdSocket->writeCMD(buffer);

    ui->btnOpenLight->setDisabled(false);
    ui->btnCloseLight->setDisabled(true);
}


void ClinetMainWindow::slt_openLight()
{

    if(true){
        ui->btnOpenLight->setText("close");
    }
    ui->btnOpenLight->setText("Open");
    /*确认是否连接上*/
    if (!cmdSocketConnectHost()) {

        emit connectError();
    }
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);
    out <<(int)0;
    out<<(unsigned char)Open_Fan;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    cmdSocket->writeCMD(buffer);
    ui->btnOpenLight->setDisabled(true);
    ui->btnCloseLight->setDisabled(false);
}


/**************************************获取设备信息************************************************/

void ClinetMainWindow::devinfo(const QByteArray &context)
{
    QString temp(context);
    QStringList devs = temp.split('\n');
    devs.removeOne("");
    ui->cmbDev->addItems(devs);
}
void ClinetMainWindow::requestDEVname()
{
    voideSocketConnectHost();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);

    out <<(int)0;
    //out << isCMD;
    out<<(unsigned char)Dev_list;
    out << 4;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    cmdSocket->writeCMD(buffer);
}




/******************************************打开摄像头*************************************************/

void ClinetMainWindow::slt_openCamera()
{
    if (!voideSocketConnectHost()) {
        QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("无法连接到主机!"));
    }

    QString devName = ui->cmbDev->currentText();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);

    out <<(int)0;
    out<<(unsigned char)Open_Camera;
    out << devName;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    vedioSocket->writeCMD(buffer);

    ui->btnOpenCamera->setDisabled(true);
    ui->btnCloseCamera->setDisabled(false);
}

void ClinetMainWindow::slt_closeCamera()
{
    isQuitNormal = true;
    if (!voideSocketConnectHost()) {
        QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("无法连接到主机!"));
    }

    QString devName = ui->cmbDev->currentText();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);

    out <<(int)0;
    out<<(unsigned char)Close_Camera;
    out << devName;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    vedioSocket->writeCMD(buffer);


    vedioSocket->close();
    ui->btnOpenCamera->setDisabled(false);
    ui->btnCloseCamera->setDisabled(true);
}

void ClinetMainWindow::vedioData_slots(const QByteArray &data)
{
    image->loadFromData(data);

    QDateTime time=QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString pixname="./camerapho/"+str+".jpg";
    image->save(pixname);
    j++;


    ui->labVideo->setPixmap(QPixmap::fromImage(*image,Qt::AutoColor));
    slt_openCamera();
}

bool ClinetMainWindow::voideSocketConnectHost()
{
    if (vedioSocket->state() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    vedioSocket->connectToHost(address,port);
    if(!vedioSocket ->waitForConnected(6000))
    {
        return false;
    }
    return true;

}



/***********************************传感器******************************************/


void ClinetMainWindow::slt_openSenSor()
{
    if (!sensorSocketConnectHost()) {
        QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("无法连接到主机!"));
    }

    QString devName = ui->cmbDev->currentText();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out.setByteOrder(QDataStream::LittleEndian);

    out <<(int)0;
    out<<(unsigned char)Open_Sensor;
    out << devName;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    sensorSocket->writeCMD(buffer);

    ui->btnOpenSeneor->setDisabled(true);
    ui->btnCloseSensor->setDisabled(false);
}

void ClinetMainWindow::slt_closeSensor()
{
    isQuitNormal = true;
    sensorSocket->close();
    ui->btnOpenSeneor->setDisabled(false);
    ui->btnCloseSensor->setDisabled(true);
}



void ClinetMainWindow::sensorData_slots(const QByteArray &data)
{
    qDebug()<<"sensor data coming";
    QString sensorStr;
    const char *tmp;
    tmp = data.data();
    qDebug()<<"tmp"<<tmp[24];
    qDebug()<<"tmp2"<<tmp[25];
    sensorStr=QString(tmp[24]);
    sensorStr.append(QString(tmp[25]));

    ui->lineEditTemperature->setText(sensorStr);
    ui->textEdit->append(sensorStr);
    ui->plainTextEdit->appendPlainText(sensorStr);
    slt_openSenSor();
}


bool ClinetMainWindow::sensorSocketConnectHost()
{
    if (sensorSocket->state() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    sensorSocket->connectToHost(address,port);
    if(!sensorSocket ->waitForConnected(3000))
    {
        return false;
    }
    return true;

}

/*****************************************************************************/



void ClinetMainWindow::slt_networkException()
{
    if (!isQuitNormal) {
        QMessageBox::warning(this,tr("Waring"),tr("network Exception!"));
        QApplication::quit();
    }
    isQuitNormal = false;
}

void ClinetMainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    timelabel->setText(str);
}



/*接收由登录界面发来的主机地址和端口号logindialong.cpp -->main.cpp--->this*/
void ClinetMainWindow::setIPandPort(const QString &add, int p)
{
    this->address = add;
    this->port = p;
}


void ClinetMainWindow::writeCmdContext(const QByteArray &context)
{
    cmdSocket->writeCMD(context);
}



void ClinetMainWindow::cmdData_slots(int cmd, const QByteArray &data)
{
    switch (cmd) {
    case 0:{
        //emit logdir_signals(data);

    } break;
    case 1:{
        //emit logfile_signals(data);

    } break;
    case 3:{
        // emit workingDevinfo_signals(data);

    } break;
    case 2:{
        //emit clientinfo_signals(data);

    } break;
    case 4:{
        devinfo(data);
    } break;
    default:
        break;
    }
}

