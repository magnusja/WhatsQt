#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QObject>

class Notification {

public:

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getInformativeText() const;
    void setInformativeText(const QString &value);

    QString getIdentifier() const;
    void setIdentifier(const QString &value);

private:
    QString title;
    QString infomativeText;
    QString identifier;
};

class NotificationService : public QObject
{
    Q_OBJECT

public:
    virtual void setApplicationBadge(QString badge) = 0;
    virtual void deliverNotification(const Notification &notification) = 0;
    virtual void dismissNotifications() = 0;

    static NotificationService* getNotificationService(QObject *parent = 0);

protected:
    NotificationService(QObject *parent = 0);

signals:
    void notificationClicked(Notification notification);
    void notificationReplied(Notification notification, QString reply);
};

#endif // NOTIFICATIONSERVICE_H
