#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T00:27:12
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WhatsQt
TEMPLATE = app
VERSION = 0.01

CONFIG(debug, debug|release) {
    DESTDIR = bin/debug
} else {
    DESTDIR = bin/release
}

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES += main.cpp\
        mainwindow.cpp \
    net/cookiejar.cpp \
    view/webview.cpp

HEADERS  += mainwindow.h \
    net/cookiejar.h \
    view/webview.h

FORMS    += mainwindow.ui
