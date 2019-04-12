#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    
signals:
    void videoDataCome(const QByteArray&data);
    void sensorDataCome(const QByteArray&data);
    void returnCmdContext(int cmd, const QByteArray& context);
    void LoginSuccess_sig();
    void LoginFailed_sig();
    void RegisterSuccess_sig();
    void RegisterFailed_sig();
    
public slots:
    void writeCMD(const QByteArray& context);
private slots:
    void dataComing();

private:
    int size;
    int count;
    
};

#endif // CLIENTSOCKET_H
