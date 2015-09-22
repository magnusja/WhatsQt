#import <Foundation/NSString.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSDockTile.h>

#include "osxnotificationservice.h"
#import <notification/osx/notificationcenterdelegate.h>

Notification osxNotificationToQtNotification(NSUserNotification *osxNotification) {
    Notification qtNotification;
    qtNotification.setTitle(QString::fromNSString(osxNotification.title));
    qtNotification.setIdentifier(QString::fromNSString(osxNotification.identifier));
    qtNotification.setInformativeText(QString::fromNSString(osxNotification.subtitle));

    return qtNotification;
}

OSXNotificationService::OSXNotificationService(QObject *parent)
    : NotificationService(parent)
{
    notificationCenter = [NSUserNotificationCenter defaultUserNotificationCenter];
    notificationCenter.delegate = [[NotificationCenterDelegate alloc] initWithNotificationService: this];
}

OSXNotificationService::~OSXNotificationService()
{
    [notificationCenter.delegate release];
    [notificationCenter release];
}

void OSXNotificationService::setApplicationBadge(QString badge)
{
    [[NSApp dockTile] setBadgeLabel:badge.toNSString()];
}

void OSXNotificationService::deliverNotification(const Notification &notification)
{
    NSString *title = notification.getTitle().toNSString();
    NSString *informativeText = notification.getInformativeText().toNSString();
    //NSString *identifier = notification.getIdentifier().toNSString();

    NSUserNotification *osxNotification = [NSUserNotification new];
    osxNotification.title = title;
    osxNotification.informativeText = informativeText;
    osxNotification.hasReplyButton = true;
    //osxNotification.identifier = identifier;
    [notificationCenter scheduleNotification:osxNotification];
}

void OSXNotificationService::dismissNotifications()
{
    [notificationCenter removeAllDeliveredNotifications];
}

void OSXNotificationService::notificationClickedDelegate(NSUserNotification *notification)
{
    emit notificationClicked(osxNotificationToQtNotification(notification));
}

void OSXNotificationService::notificationRepliedDelegate(NSUserNotification *notification)
{
    emit notificationReplied(osxNotificationToQtNotification(notification), QString::fromNSString(notification.response.string));
}

