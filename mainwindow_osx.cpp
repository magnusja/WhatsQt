#include <objc/objc.h>
#include <objc/message.h>
#include <QDebug>

#include "mainwindow.h"

MainWindow *mainWindow;

bool dockClickHandler(id self, SEL _cmd, ...)
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    qDebug() << "OS X dock icon clicked!";

    mainWindow->show();

    return false;
}

void MainWindow::setupDockClickHandler()
{
    mainWindow = this;

    Class cls = objc_getClass("NSApplication");
    objc_object *appInst = objc_msgSend((objc_object*)cls, sel_registerName("sharedApplication"));

    if(appInst != NULL) {
        objc_object* delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = (Class)objc_msgSend(delegate,  sel_registerName("class"));
        SEL shouldHandle = sel_registerName("applicationShouldHandleReopen:hasVisibleWindows:");
        if (class_getInstanceMethod(delClass, shouldHandle)) {
            if (class_replaceMethod(delClass, shouldHandle, (IMP)dockClickHandler, "B@:"))
                qDebug() << "Registered dock click handler (replaced original method)";
            else
                qWarning() << "Failed to replace method for dock click handler";
        }
        else {
            if (class_addMethod(delClass, shouldHandle, (IMP)dockClickHandler,"B@:"))
                qDebug() << "Registered dock click handler";
            else
                qWarning() << "Failed to register dock click handler";
        }
    }
}