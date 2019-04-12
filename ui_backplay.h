/********************************************************************************
** Form generated from reading UI file 'backplay.ui'
**
** Created: Mon Feb 27 16:06:21 2017
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKPLAY_H
#define UI_BACKPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_backplay
{
public:

    void setupUi(QWidget *backplay)
    {
        if (backplay->objectName().isEmpty())
            backplay->setObjectName(QString::fromUtf8("backplay"));
        backplay->resize(400, 300);

        retranslateUi(backplay);

        QMetaObject::connectSlotsByName(backplay);
    } // setupUi

    void retranslateUi(QWidget *backplay)
    {
        backplay->setWindowTitle(QApplication::translate("backplay", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class backplay: public Ui_backplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKPLAY_H
