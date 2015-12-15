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

#include <objc/message.h>
#include <QDebug>

#import <AppKit/AppKit.h>

#include "mainwindow.h"

// TODO: static instance is not nice :/
MainWindow *qtMainWindow;

// TODO: avoid nasty runtime injection of methods into delegate classes (if possible)

void dockClickHandler(id self, SEL _cmd)
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    qDebug() << "OS X dock icon clicked!";

    qtMainWindow->show();
}

void setupDockClick()
{
    Class cls = [[[NSApplication sharedApplication] delegate] class];
    SEL shouldHandle = @selector(applicationShouldHandleReopen:hasVisibleWindows:);

    if (class_getInstanceMethod(cls, shouldHandle))
    {
        if (class_replaceMethod(cls, shouldHandle, (IMP)dockClickHandler, "B@:"))
            qDebug() << "Registered dock click handler (replaced original method)";
        else
            qWarning() << "Failed to replace method for dock click handler";
    }
    else
    {
        if (class_addMethod(cls, shouldHandle, (IMP)dockClickHandler,"B@:"))
            qDebug() << "Registered dock click handler";
        else
            qWarning() << "Failed to register dock click handler";
    }

}

void MainWindow::nativeSetup()
{
    qtMainWindow = this;
    setupDockClick();
}