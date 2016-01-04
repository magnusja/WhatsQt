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

#include "Preferences.h"

void Preferences::setNotificationType(NotificationType type)
{
    settings.beginGroup("general");
    settings.setValue("notification_type", type);
    settings.endGroup();
}

Preferences::NotificationType Preferences::getNotificationType()
{
    settings.beginGroup("general");
    auto type = (NotificationType) settings.value("notification_type", 0).toInt();
    settings.endGroup();
    return type;
}

uint Preferences::getNotificationTimeMs()
{
    // hard coded for now
    return 7000;
}

void Preferences::setPermission(QWebEnginePage::Feature feature, bool granted)
{
    settings.beginGroup("permissions");
    settings.setValue(QString::number(feature), granted);
    settings.endGroup();
}

bool Preferences::isPermissionGranted(QWebEnginePage::Feature feature)
{
    settings.beginGroup("permissions");
    auto granted = settings.value(QString::number(feature), false).toBool();
    settings.endGroup();
    return granted;
}

bool Preferences::isPermissionDenied(QWebEnginePage::Feature feature)
{
    settings.beginGroup("permissions");
    auto denied = !settings.value(QString::number(feature), true).toBool();
    settings.endGroup();
    return denied;
}
