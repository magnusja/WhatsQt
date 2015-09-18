#ifndef OSXNOTIFICATIONSERVICE_H
#define OSXNOTIFICATIONSERVICE_H
#include <objc/objc.h>

#include <notification/notificationservice.h>

#ifdef __OBJC__
#define OBJC_CLASS(name) @class name
#else
#define OBJC_CLASS(name) typedef struct objc_object name
#endif

OBJC_CLASS(NSUserNotificationCenter);
OBJC_CLASS(NSUserNotification);

class OSXNotificationService : public NotificationService
{
friend class NotificationService;

Q_OBJECT

public:

    ~OSXNotificationService();

    void setApplicationBadge(QString badge);
    void deliverNotification(const Notification &notification);
    void dismissNotifications();

    void notificationClickedDelegate(NSUserNotification *notification);
    void notificationRepliedDelegate(NSUserNotification *notification);

private:
    OSXNotificationService(QObject *parent = 0);

    NSUserNotificationCenter *notificationCenter;
};

#endif // OSXNOTIFICATIONSERVICE_H
