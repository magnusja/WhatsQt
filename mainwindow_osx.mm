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