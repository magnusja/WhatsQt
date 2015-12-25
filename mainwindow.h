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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>


#include "notification/notificationservice.h"

namespace Ui {
class MainWindow;
}

class JSNotifcationWrapper : public QObject {

    Q_OBJECT

public:
    JSNotifcationWrapper(NotificationService *service, QObject *parent = 0);

    void setNotificationService(NotificationService *notificationService);
    Q_INVOKABLE void deliverNotification(const QString &title, const QMap<QString, QVariant> &options);

private:
    NotificationService *notificationService;

private slots:
    void onNotificationClicked(const Notification &notification);
    void onNotificationReplied(const Notification &notification, const QString &reply);

signals:
    void notificationClicked(const QString &title, const QMap<QString, QVariant> &options);
    void notificationReplied(const QString &title, const QMap<QString, QVariant> &options, const QString &reply);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

protected:
    bool event(QEvent *event);

private:
    Ui::MainWindow *ui;
    NotificationService *notificationService;
    JSNotifcationWrapper *notificationWrapper;

    void saveSettings();
    void readSettings();

    void initActions();
    void initMenus();

    void initNotificationService();

#ifdef Q_OS_OSX
    void nativeSetup();
#else
    void nativeSetup() {}
#endif

private slots:
    void webViewTitleChanged(const QString &title);
    void notificationClicked(const Notification &notification);
    void notificationReplied(const Notification &notification, const QString &reply);
};

#endif // MAINWINDOW_H
