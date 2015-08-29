#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T00:27:12
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    net/cookiejar.cpp

HEADERS  += mainwindow.h \
    net/cookiejar.h

FORMS    += mainwindow.ui
