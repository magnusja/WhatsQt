#ifndef OSXNOTIFICATIONSERVICE_H
#define OSXNOTIFICATIONSERVICE_H

#include <notification/notificationservice.h>

class OSXNotificationService : public NotificationService
{
friend class NotificationService;
private:
    OSXNotificationService(QObject *parent = 0);

public:
    void setApplicationBadge(QString badge);
    void deliverNotification(const Notification &notification);
    void dismissNotifications();
};

#endif // OSXNOTIFICATIONSERVICE_H
