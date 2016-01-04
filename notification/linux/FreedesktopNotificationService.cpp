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
#include <QtDBus/QDBusPendingReply>
#include <QtDBus/QDBusConnection>
#include <QFile>

#include "FreedesktopNotificationService.h"

FreedesktopNotificationService::FreedesktopNotificationService(QObject *parent)
        : NotificationService(parent),
          imageFile(new QTemporaryFile(this))
{
    // TODO: this should be a temporary hack
    imageFile->open(); // create so fileName() returns path
    QFile image(":/artwork/icon/icon256.png");
    image.open(QIODevice::ReadOnly);
    imageFile->write(image.readAll());

    freedesktopInterface = new org::freedesktop::Notifications(QStringLiteral("org.freedesktop.Notifications"),
                                                               QStringLiteral("/org/freedesktop/Notifications"),
                                                               QDBusConnection::sessionBus(), this);

    connect(freedesktopInterface, &org::freedesktop::Notifications::ActionInvoked, this, &FreedesktopNotificationService::onNotificationActionInvoked);

    connect(freedesktopInterface, &org::freedesktop::Notifications::NotificationClosed, this, [this](const uint id, const uint reason) {
       qDebug() << "Notification Closed: " << id << " " << reason;
    });

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
    // TODO: passing zero sets new an id for this notification -> how can we identify it 'backwards'
    // to enable action invokes
    freedesktopInterface->Notify(qAppName(), 0, imageFile->fileName(), notification.getTitle(),
        notification.getInformativeText(), QStringList(), QVariantMap(), preferences.getNotificationTimeMs());
}

void FreedesktopNotificationService::dismissNotifications()
{

}

void FreedesktopNotificationService::onNotificationActionInvoked(const uint id, const QString &actionKey)
{
    qDebug() << "Freedesktop Notification Action Invoked " << id << " " << actionKey;
}
