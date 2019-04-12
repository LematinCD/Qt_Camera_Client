#include "networkconfigdialog.h"
#include "ui_networkconfigdialog.h"
#include <QHostAddress>
#include <QFile>
#include <QDialog>
#include <QMessageBox>

NetWorkConfigDialog::NetWorkConfigDialog(QWidget *parent,const QString &networkFileName) :
    QDialog(parent),
    ui(new Ui::NetWorkConfigDialog),
    myNetworkConfig(networkFileName)
{
    ui->setupUi(this);
    readHostData();
    connect(ui->btnHostOK,SIGNAL(clicked()),this,SLOT(okBtn_slots()));
    connect(ui->cmbHostAddress,SIGNAL(activated(QString)),this,SLOT(slt_selectHostHistoryData(QString)));
    connect(ui->btnClearHost,SIGNAL(clicked()),this,SLOT(slt_clearHostHistoryData()));
    setDefaultIPandPort();
    ui->cmbHostAddress->setEditable(true);
    setModal(true);
}

NetWorkConfigDialog::~NetWorkConfigDialog()
{
    delete ui;
}

void NetWorkConfigDialog::okBtn_slots()
{
    QString tmpAddress = ui->cmbHostAddress->currentText();
    QHostAddress add;
    if(!add.setAddress(tmpAddress)){
        QMessageBox::information(this,tr("information"),tr("IP is invaild!"));
        return;
    }

    bool isInt;
    QString port = ui->lineEditPort->text();
    int tmpPort = port.toInt(&isInt,10);
    if (!isInt){
        QMessageBox::information(this,tr("information"),tr("Port is invail! "));
        return;
    }

    emit hostAddressAndIP_signal(tmpAddress,tmpPort);
    writeHostData();
    close();
}

void NetWorkConfigDialog::slt_selectHostHistoryData(const QString indexText)
{
    QFile file(myNetworkConfig);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        if (temp.left(temp.indexOf(' ')) == indexText) {
            ui->lineEditPort->setText(temp.right(temp.length() - temp.indexOf(' ') - 1));
            file.close();
            return;
        }
        temp = out.readLine();
    }
    file.close();
}

void NetWorkConfigDialog::slt_clearHostHistoryData()
{
    QFile file(myNetworkConfig);

    file.resize(0);
    ui->cmbHostAddress->clear();

}

void NetWorkConfigDialog::setDefaultIPandPort()
{
    QFile file(myNetworkConfig);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    defaultIp = temp.left(temp.indexOf(' '));
    defaultPort = temp.right(temp.length() - temp.indexOf(' ') - 1).toInt();
    file.close();
}

void NetWorkConfigDialog::writeHostData()
{
    QFile file(myNetworkConfig);
    if (!file.open(QIODevice::ReadWrite /*| QIODevice::Append*/ | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {

        if (ui->cmbHostAddress->currentText() == temp.left(temp.indexOf(' '))) {
            file.close();
            return;
        }
        temp = out.readLine();
    }
    out << ui->cmbHostAddress->currentText() << ' ' << ui->lineEditPort->text() << '\n';
    file.close();
}

void NetWorkConfigDialog::readHostData()
{

    QFile file(myNetworkConfig);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        ui->cmbHostAddress->addItem(temp.left(temp.indexOf(' ')));
        temp = out.readLine();
    }
    file.close();
}
