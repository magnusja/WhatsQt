#include "nullnotificationservice.h"

NullNotificationService::NullNotificationService(QObject *parent)
    : NotificationService(parent)
{

}

void NullNotificationService::setApplicationBadge(QString badge)
{
    Q_UNUSED(badge);
}

void NullNotificationService::deliverNotification(const Notification &notification)
{
    Q_UNUSED(notification);
}

