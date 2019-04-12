/********************************************************************************
** Form generated from reading UI file 'playbackdialog.ui'
**
** Created: Mon Feb 27 14:52:06 2017
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYBACKDIALOG_H
#define UI_PLAYBACKDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>

QT_BEGIN_NAMESPACE

class Ui_PlaybackDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *slider;

    void setupUi(QDialog *PlaybackDialog)
    {
        if (PlaybackDialog->objectName().isEmpty())
            PlaybackDialog->setObjectName(QString::fromUtf8("PlaybackDialog"));
        PlaybackDialog->resize(400, 300);
        gridLayout = new QGridLayout(PlaybackDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(PlaybackDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        slider = new QSlider(PlaybackDialog);
        slider->setObjectName(QString::fromUtf8("slider"));
        slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider, 1, 0, 1, 1);


        retranslateUi(PlaybackDialog);

        QMetaObject::connectSlotsByName(PlaybackDialog);
    } // setupUi

    void retranslateUi(QDialog *PlaybackDialog)
    {
        PlaybackDialog->setWindowTitle(QApplication::translate("PlaybackDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlaybackDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaybackDialog: public Ui_PlaybackDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYBACKDIALOG_H
