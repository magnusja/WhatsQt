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

