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

#ifdef Q_OS_OSX
#include "osx/osxnotificationservice.h"
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

NotificationService::NotificationService(QObject *parent)
    : QObject(parent)
{

}

NotificationService* NotificationService::getNotificationService(QObject *parent)
{
#ifdef Q_OS_OSX
    return new OSXNotificationService(parent);
#else
    return new NullNotificationService(parent);
#endif
}
