#include "notificationservice.h"

#ifdef Q_OS_OSX
#include "osx/osxnotificationservice.h"
#endif

NotificationService::NotificationService(QObject *parent)
    : QObject(parent)
{

}

NotificationService* NotificationService::getNotificationService()
{
#ifdef Q_OS_OSX
    return new OSXNotificationService();
#else
    return 0;
#endif
}

