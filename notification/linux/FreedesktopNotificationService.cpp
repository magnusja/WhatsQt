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

#include <QApplication>

#include "FreedesktopNotificationService.h"

FreedesktopNotificationService::FreedesktopNotificationService(QObject *parent)
        : NotificationService(parent)
{
    freedesktopInterface = new org::freedesktop::Notifications(QStringLiteral("org.freedesktop.Notifications"),
                                                               QStringLiteral("/org/freedesktop/Notifications"),
                                                               QDBusConnection::sessionBus(), this);

    QDBusPendingReply<QStringList> reply = freedesktopInterface->GetCapabilities();
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, [reply, watcher, this]() {
        qDebug() << "GetCapabilities reply: " << reply.value();
        watcher->deleteLater();
    });
}

void FreedesktopNotificationService::setApplicationBadge(QString badge)
{
    Q_UNUSED(badge);
}

void FreedesktopNotificationService::deliverNotification(const Notification &notification)
{
    freedesktopInterface->Notify(qAppName(), notification.getUIntIdentifier(), QString(), notification.getTitle(),
        notification.getInformativeText(), QStringList(), QVariantMap(), 3000);
}

void FreedesktopNotificationService::dismissNotifications()
{

}