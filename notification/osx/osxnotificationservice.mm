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
    NSString *identifier = notification.getIdentifier().toNSString();

    qDebug() << "deliver notification with identifier: " << identifier;

    NSUserNotification *osxNotification = [NSUserNotification new];
    osxNotification.title = title;
    osxNotification.informativeText = informativeText;
    osxNotification.hasReplyButton = true;
    osxNotification.identifier = identifier;
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

