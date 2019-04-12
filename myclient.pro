#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T11:13:09
#
#-------------------------------------------------

QT       += core gui network
QT       += widgets printsupport

TARGET = myclient
TEMPLATE = app


SOURCES += main.cpp\
        clinetmainwindow.cpp \
    clientsocket.cpp \
    logindialog.cpp \
    registerdialog.cpp \
    networkconfigdialog.cpp \
    qcustomplot.cpp \
    picenv.cpp \
    playbk.cpp

HEADERS  += clinetmainwindow.h \
    clientsocket.h \
    logindialog.h \
    registerdialog.h \
    networkconfigdialog.h \
    CommandType.h \
    qcustomplot.h \
    picenv.h \
    playbk.h

FORMS    += clinetmainwindow.ui \
    logindialog.ui \
    registerdialog.ui \
    networkconfigdialog.ui \
    picenv.ui \
    playbk.ui
