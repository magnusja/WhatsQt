/*
 * This file is part of WhatsQt.
 *
 * WhatsQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WhatsQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WhatsQt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>

#include "mainwindow.h"

#ifdef Q_OS_WIN
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char *argv[])
{
#ifdef QT_DEBUG
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "23654");
#endif

    QApplication::setApplicationName("WhatsQt");
    QApplication::setOrganizationName("mjdv");
    QApplication::setOrganizationDomain("https://github.com/mjdev");
    QApplication::setApplicationVersion(APP_VERSION);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#ifdef Q_OS_OSX
    a.setQuitOnLastWindowClosed(false);
#endif

    return a.exec();
}
