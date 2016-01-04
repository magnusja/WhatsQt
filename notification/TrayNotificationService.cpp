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

#include "TrayNotificationService.h"

TrayNotificationService::TrayNotificationService(QObject *parent)
    : NotificationService(parent)
{
    trayIcon.setIcon(QIcon(":/artwork/icon/icon256.png"));
    trayIcon.hide();
}

void TrayNotificationService::dismissNotifications()
{
}

void TrayNotificationService::deliverNotification(const Notification &notification)
{
    trayIcon.show();
    trayIcon.showMessage(notification.getTitle(),
        notification.getInformativeText(),
        QSystemTrayIcon::Information,
        preferences.getNotificationTimeMs());
    trayIcon.hide();
}

void TrayNotificationService::setApplicationBadge(QString badge)
{
    Q_UNUSED(badge);
}
