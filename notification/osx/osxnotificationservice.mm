#import <Foundation/NSString.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSDockTile.h>

#include "osxnotificationservice.h"

OSXNotificationService::OSXNotificationService(QObject *parent)
    : NotificationService(parent)
{

}

void OSXNotificationService::setApplicationBadge(QString badge)
{
    NSString* nsBadge = [[NSString alloc] initWithUTF8String:badge.toUtf8().data()];
    [[NSApp dockTile] setBadgeLabel:nsBadge];
}

void OSXNotificationService::deliverNotification(const Notification &notification)
{
    NSString* title = [[NSString alloc] initWithUTF8String:notification.getTitle().toUtf8().data()];
    NSString* informativeText = [[NSString alloc] initWithUTF8String:notification.getInformativeText().toUtf8().data()];

    NSUserNotification *osxNotification = [NSUserNotification new];
    osxNotification.title = title;
    osxNotification.subtitle = informativeText;
    [[NSUserNotificationCenter defaultUserNotificationCenter] scheduleNotification:osxNotification];
}

