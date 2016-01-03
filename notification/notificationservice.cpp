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

#include "notificationservice.h"
#include "nullnotificationservice.h"
#include "TrayNotificationService.h"
#include "util/Preferences.h"

#ifdef Q_OS_OSX
#include "osx/osxnotificationservice.h"
#elif defined(Q_OS_LINUX)
#include "linux/FreedesktopNotificationService.h"
#endif

QString Notification::getTitle() const
{
    return title;
}

void Notification::setTitle(const QString &value)
{
    title = value;
}

QString Notification::getInformativeText() const
{
    return infomativeText;
}

void Notification::setInformativeText(const QString &value)
{
    infomativeText = value;
}

QString Notification::getIdentifier() const
{
    return identifier;
}

void Notification::setIdentifier(const QString &value)
{
    identifier = value;
}

uint Notification::getUIntIdentifier() const {
    QString digits;
    foreach(QChar c, identifier)
    {
        if(c.isDigit()) digits.append(c);
    }
    return digits.toUInt();
}

NotificationService::NotificationService(QObject *parent)
    : QObject(parent)
{

}

NotificationService* NotificationService::getNotificationService(QObject *parent)
{
    Preferences preferences;

    switch(preferences.getNotificationType())
    {
        case Preferences::NotificationTypeNative:
            qDebug() << "Using native notifications";
            return getNativeNotificationService(parent);

        case Preferences::NotificationTypeSystemTray:
            qDebug() << "Using tray notifications";
            return new TrayNotificationService(parent);

        case Preferences::NotificationTypeNull:
            qDebug() << "Using null notifications";
            return new NullNotificationService(parent);
    }

    // This should not happen
    return new NullNotificationService(parent);
}

NotificationService *NotificationService::getNativeNotificationService(QObject *parent)
{
#ifdef Q_OS_OSX
    return new OSXNotificationService(parent);
#elif defined(Q_OS_LINUX)
    return new FreedesktopNotificationService(parent);
#elif defined(Q_OS_WIN)
    return new TrayNotificationService(parent);
#else
    return new NullNotificationService(parent);
#endif
}
