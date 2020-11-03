#-------------------------------------------------
#
# Project created by QtCreator 2020-10-15T01:26:50
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataInsertInterfaceServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clxpredbwriter.cpp \
    clxbufqueue.cpp \
    clxdatabuf.cpp \
    clxlogfile.cpp \
    clxtcpdevclient.cpp \
    clxmysqldb.cpp

HEADERS  += mainwindow.h \
    clxpredbwriter.h \
    clxbufqueue.h \
    clxdatabuf.h \
    clxlogfile.h \
    clxtcpdevclient.h \
    clxmysqldb.h

FORMS    += mainwindow.ui
