#include "notificationservice.h"
#include "nullnotificationservice.h"

#ifdef Q_OS_OSX
#include "osx/osxnotificationservice.h"
#endif

NotificationService::NotificationService(QObject *parent)
    : QObject(parent)
{

}

NotificationService* NotificationService::getNotificationService(QObject *parent)
{
#ifdef Q_OS_OSX
    return new OSXNotificationService(parent);
#else
    return new NullNotificationService(parent);
#endif
}

