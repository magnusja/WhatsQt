#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
#ifdef QT_DEBUG
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "23654");
#endif

    QApplication::setApplicationName("WhatsQt");
    QApplication::setOrganizationName("mjdv");
    QApplication::setOrganizationDomain("https://github.com/mjdev");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#ifdef Q_OS_OSX
    a.setQuitOnLastWindowClosed(false);
#endif

    return a.exec();
}
