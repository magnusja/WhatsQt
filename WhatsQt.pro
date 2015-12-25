#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T00:27:12
#
#-------------------------------------------------

QT       += core gui webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

CONFIG += c++11

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
    view/webview.cpp \
    notification/notificationservice.cpp \
    notification/nullnotificationservice.cpp \
    view/webpage.cpp \
    dialog/AboutDialog.cpp

HEADERS  += mainwindow.h \
    view/webview.h \
    notification/notificationservice.h \
    notification/nullnotificationservice.h \
    view/webpage.h \
    dialog/AboutDialog.h

FORMS    += mainwindow.ui \
    dialog/aboutdialog.ui

mac {
    HEADERS += notification/osx/osxnotificationservice.h \
        notification/osx/notificationcenterdelegate.h

    OBJECTIVE_SOURCES += notification/osx/osxnotificationservice.mm \
        notification/osx/notificationcenterdelegate.mm \
        mainwindow_osx.cpp

    LIBS += -framework Foundation -framework AppKit
}

RESOURCES += \
    resources.qrc
