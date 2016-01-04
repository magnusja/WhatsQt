/*
 * This file is part of WhatsQt.
 *
 * WhatsQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WhatsQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WhatsQt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <QObject>
#include "util/Preferences.h"

class Notification {

public:

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getInformativeText() const;
    void setInformativeText(const QString &value);

    QString getIdentifier() const;
    void setIdentifier(const QString &value);

    uint getUIntIdentifier() const;

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

    Preferences preferences;

private:
    static NotificationService *getNativeNotificationService(QObject *parent = 0);

signals:
    void notificationClicked(Notification notification);
    void notificationReplied(Notification notification, QString reply);
};

#endif // NOTIFICATIONSERVICE_H
