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

#ifndef OSXNOTIFICATIONSERVICE_H
#define OSXNOTIFICATIONSERVICE_H
#include <objc/objc.h>

#include <notification/notificationservice.h>

#ifdef __OBJC__
#define OBJC_CLASS(name) @class name
#else
#define OBJC_CLASS(name) typedef struct objc_object name
#endif

OBJC_CLASS(NSUserNotificationCenter);
OBJC_CLASS(NSUserNotification);

class OSXNotificationService : public NotificationService
{
friend class NotificationService;

Q_OBJECT

public:

    ~OSXNotificationService();

    void setApplicationBadge(QString badge);
    void deliverNotification(const Notification &notification);
    void dismissNotifications();

    void notificationClickedDelegate(NSUserNotification *notification);
    void notificationRepliedDelegate(NSUserNotification *notification);

private:
    OSXNotificationService(QObject *parent = 0);

    NSUserNotificationCenter *notificationCenter;
};

#endif // OSXNOTIFICATIONSERVICE_H
