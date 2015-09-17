#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QObject>

class Notification : public QObject {
    Q_OBJECT
public:
    QString getTitle() const;
    void setTitle(const QString &value);

    QString getInformativeText() const;
    void setInformativeText(const QString &value);

private:
    QString title;
    QString infomativeText;

};

class NotificationService : public QObject
{
protected:
    NotificationService(QObject *parent = 0);
public:
    virtual void setApplicationBadge(QString badge) = 0;
    virtual void deliverNotification(const Notification &notification) = 0;

    static NotificationService* getNotificationService(QObject *parent = 0);
};

#endif // NOTIFICATIONSERVICE_H
