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


#ifndef WHATSQT_PREFERENCES_H
#define WHATSQT_PREFERENCES_H

#include <QWebEnginePage>
#include <QMap>
#include <QSettings>

class Preferences {

public:

    enum NotificationType {
        NotificationTypeNative = 0,
        NotificationTypeSystemTray,
        NotificationTypeNull
    };

    void setNotificationType(NotificationType type);
    NotificationType getNotificationType();
    uint getNotificationTimeMs();

    void setPermission(QWebEnginePage::Feature feature, bool granted);
    bool isPermissionGranted(QWebEnginePage::Feature feature);
    bool isPermissionDenied(QWebEnginePage::Feature feature);

private:
    QSettings settings;
};


#endif //WHATSQT_PREFERENCES_H
