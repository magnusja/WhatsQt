#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QObject>

class NotificationService : public QObject
{
protected:
    NotificationService(QObject *parent = 0);
public:
    virtual void setApplicationBadge(QString badge) = 0;

    static NotificationService* getNotificationService();
};

#endif // NOTIFICATIONSERVICE_H
