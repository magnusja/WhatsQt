#include "notificationservice.h"
#include "nullnotificationservice.h"

#ifdef Q_OS_OSX
#include "osx/osxnotificationservice.h"
#endif

QString Notification::getTitle() const
{
    return title;
}

void Notification::setTitle(const QString &value)
{
    title = value;
}

QString Notification::getInformativeText() const
{
    return infomativeText;
}

void Notification::setInformativeText(const QString &value)
{
    infomativeText = value;
}

QString Notification::getIdentifier() const
{
    return identifier;
}

void Notification::setIdentifier(const QString &value)
{
    identifier = value;
}

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
