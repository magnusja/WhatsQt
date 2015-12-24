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

#ifndef WHATSQT_FREEDESKTOPNOTIFICATIONSERVICE_H
#define WHATSQT_FREEDESKTOPNOTIFICATIONSERVICE_H

#include <QTemporaryFile>

#include <notification/notificationservice.h>
#include <FreedesktopNotifications.h>

class FreedesktopNotificationService : public NotificationService
{
friend class NotificationService;

Q_OBJECT

public:
    void setApplicationBadge(QString badge);
    void deliverNotification(const Notification &notification);
    void dismissNotifications();

private:
    FreedesktopNotificationService(QObject *parent = 0);

    org::freedesktop::Notifications *freedesktopInterface;
    // holds application image file to show in a notification
    // copied from resources.qrc
    QTemporaryFile *imageFile;

private slots:
    void onNotificationActionInvoked(const uint id, const QString &actionKey);
};


#endif //WHATSQT_FREEDESKTOPNOTIFICATIONSERVICE_H
