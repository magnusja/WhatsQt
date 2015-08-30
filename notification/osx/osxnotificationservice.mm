#import <Foundation/NSString.h>
#import <AppKit/NSApplication.h>

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

