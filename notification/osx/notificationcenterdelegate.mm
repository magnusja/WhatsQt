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

#import <notification/osx/notificationcenterdelegate.h>
#include <notification/osx/osxnotificationservice.h>

@interface NotificationCenterDelegate() {
    OSXNotificationService *m_notificationService;
}
@end

@implementation NotificationCenterDelegate

- (id)initWithNotificationService:(OSXNotificationService *)notificationService
{
    self = [super init];
    if (self) {
       m_notificationService = notificationService;
    }
    return self;
}

- (void)userNotificationCenter:(NSUserNotificationCenter *)center
       didActivateNotification:(NSUserNotification *)notification
{
    Q_UNUSED(center);

    // TODO: maybe do the siwtch in OSXNotificationService
    switch(notification.activationType)
    {
    case NSUserNotificationActivationTypeContentsClicked:
        m_notificationService->notificationClickedDelegate(notification);
        break;
    case NSUserNotificationActivationTypeReplied:
        m_notificationService->notificationRepliedDelegate(notification);
        break;
    default:
        break;
    }
}

@end

