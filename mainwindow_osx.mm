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

void updateTitleBar(NSWindow *window)
{
    // Source: https://github.com/stonesam92/ChitChat/blob/master/WhatsMac/AppDelegate.m
    const static CGFloat kTitlebarHeight = 59;
    CGRect windowFrame = window.frame;

    NSView *titlebarView = [window standardWindowButton:NSWindowCloseButton].superview;
    // Set size of titlebar container
    NSView *titlebarContainerView = titlebarView.superview;
    CGRect titlebarContainerFrame = titlebarContainerView.frame;
    titlebarContainerFrame.origin.y = windowFrame.size.height - kTitlebarHeight;
    titlebarContainerFrame.size.height = kTitlebarHeight;
    titlebarContainerView.frame = titlebarContainerFrame;

    // Set position of window buttons
    CGFloat buttonX = 12; // initial LHS margin, matching Safari 8.0 on OS X 10.10.
    NSView *closeButton = [window standardWindowButton:NSWindowCloseButton];
    NSView *minimizeButton = [window standardWindowButton:NSWindowMiniaturizeButton];
    NSView *zoomButton = [window standardWindowButton:NSWindowZoomButton];

    for (NSView *buttonView in @[closeButton, minimizeButton, zoomButton])
    {
        CGRect buttonFrame = buttonView.frame;

        buttonFrame.origin.y = round((kTitlebarHeight - buttonFrame.size.height) / 2.0);

        buttonFrame.origin.x = buttonX;

        // spacing for next button, matching Safari 8.0 on OS X 10.10.
        buttonX += buttonFrame.size.width + 6;

        [buttonView setFrameOrigin:buttonFrame.origin];
    };
}

void updateTitleBarDelegate(id self, SEL _cmd)
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)

    qDebug() << "NSWindow: updating title bar";

    auto nativeView = (NSView *)qtMainWindow->winId();
    updateTitleBar(nativeView.window);
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

void setupNSWindow(NSWindow *window)
{
    window.styleMask =  NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask | NSFullSizeContentViewWindowMask;
    window.appearance = [NSAppearance appearanceNamed:NSAppearanceNameVibrantLight];
    window.titleVisibility = NSWindowTitleHidden;
    window.titlebarAppearsTransparent = YES;
    window.movableByWindowBackground = YES;

    // TODO: can the proper update of the title bar be archived easier?
    Class cls = [[window delegate] class];
    SEL shouldHandle = @selector(windowDidResize:);

    if (class_getInstanceMethod(cls, shouldHandle))
    {
        if (class_replaceMethod(cls, shouldHandle, (IMP) updateTitleBarDelegate, "B@:"))
            qDebug() << "Registered resize handler (replaced original method)";
        else
            qWarning() << "Failed to replace method for resize handler";
    }
    else
    {
        if (class_addMethod(cls, shouldHandle, (IMP) updateTitleBarDelegate, "B@:"))
            qDebug() << "Registered resize handler";
        else
            qWarning() << "Failed to register resize handler";
    }

    shouldHandle = @selector(windowDidBecomeKey:);

    if (class_getInstanceMethod(cls, shouldHandle))
    {
        if (class_replaceMethod(cls, shouldHandle, (IMP) updateTitleBarDelegate, "B@:"))
            qDebug() << "Registered key handler (replaced original method)";
        else
            qWarning() << "Failed to replace method for key handler";
    }
    else
    {
        if (class_addMethod(cls, shouldHandle, (IMP) updateTitleBarDelegate, "B@:"))
            qDebug() << "Registered key handler";
        else
            qWarning() << "Failed to register key handler";
    }

    updateTitleBar(window);
}

void MainWindow::nativeSetup()
{
    qtMainWindow = this;
    setupDockClick();

    // Without these flags, the window buttons always change their place after certain window events
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    auto nativeView = (NSView *)winId();
    setupNSWindow(nativeView.window);
}