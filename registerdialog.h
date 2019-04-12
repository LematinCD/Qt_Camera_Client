#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();
signals:
    void register_sig(const QString &name,const QString &passwd);
private slots:
    void register_slots();
    void cancel_slots();
private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
