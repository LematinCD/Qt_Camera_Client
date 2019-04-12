#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->btnRegister,SIGNAL(clicked()),this,SLOT(register_slots()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancel_slots()));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::register_slots()
{
    QString name  = ui->lineEditRegisterName->text();
    QString firstPasswd = ui->lineEditFirstPasswd->text();
    QString secondPasswd = ui->lineEditSecondPasswd->text();

    if(name.isEmpty()||firstPasswd.isEmpty()||secondPasswd.isEmpty()){
        QMessageBox::information(this,tr("information"),tr("is empty!"));
        return;
    }
    if(firstPasswd!=secondPasswd){
        QMessageBox::information(this,tr("information"),tr("no same!"));
        return;
    }
    emit register_sig(name,firstPasswd);
}

void RegisterDialog::cancel_slots()
{
    this->close();
}
