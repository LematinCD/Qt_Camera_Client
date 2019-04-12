#include "clientsocket.h"
#include "CommandType.h"
ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent),
    size(0),
    count(0)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataComing()));
}

void ClientSocket::writeCMD(const QByteArray &context)
{
    this->write(context);
}

void ClientSocket::dataComing()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_6);
    in.setByteOrder(QDataStream::LittleEndian);
    if (size == 0)
    {
        if (bytesAvailable() < (qint64)sizeof(int))
        {
            return;
        }
        in >> size;
        qDebug()<<"size:"<<size;
    }
    if (bytesAvailable() < size)
    {
        return;
    }

    qint8 net_cmd = -1;
    in >> net_cmd;
    qDebug()<<"net_cmd:"<<net_cmd;
    switch(net_cmd)
    {

    case LoginSuccess:
    {

        emit LoginSuccess_sig();
    }break;

    case LoginFailed:
    {
        emit LoginFailed_sig();
    }break;
    case RegisterSuccess:
    {
        emit RegisterSuccess_sig();
    }break;

    case RegisterFailed:
    {
        emit RegisterFailed_sig();
    }break;

    case Open_Sensor_Success:
    {
        QByteArray buffer;
        buffer.resize(size - 2*sizeof(int));
        in>>buffer;
        qDebug()<<"Sensor buffer.size:"<<buffer.size();
        emit sensorDataCome(buffer);
    }break;


    case Open_Camera_Success:
    {
        QByteArray buffer;
        buffer.resize(size - 2*sizeof(int));
        in>>buffer;
        qDebug()<<"Cam buffer.size:"<<buffer.size();
        emit videoDataCome(buffer);
    }break;

    case Dev_list:
    {
        QByteArray buffer;
        int cmd;
        in >> cmd;
        buffer.resize(size - 3*sizeof(int));

        //in.device()->seek(12);
        in >> buffer;

        qDebug()<<"CMD :buffer.size:"<<buffer.size();
        QString str(buffer);
        qDebug()<<"str"<<str;
        emit returnCmdContext(cmd,buffer);
    }break;


    default:break;

    }
    size = 0;
    count++;
    qDebug()<<"***************"<<"count:"<<count<<"**************";
}
