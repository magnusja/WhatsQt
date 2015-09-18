#import <Foundation/Foundation.h>

// TODO: maybe implement some delegate pattern in C++ -> no knowledge of actual OSXNotificationService
// but abstract class which OSXNotificationService can then implement
class OSXNotificationService;

@interface NotificationCenterDelegate : NSObject<NSUserNotificationCenterDelegate>
- (id)initWithNotificationService:(OSXNotificationService *)notificationService;
@end
