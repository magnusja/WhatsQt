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

#include <QRegExp>
#include <QWebChannel>
#include <QSettings>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog/AboutDialog.h"
#include "dialog/PreferencesDialog.h"

JSNotifcationWrapper::JSNotifcationWrapper(NotificationService *service, QObject *parent)
    : QObject(parent),
      notificationService(service)
{
    connect(notificationService, &NotificationService::notificationClicked, this, &JSNotifcationWrapper::onNotificationClicked);
    connect(notificationService, &NotificationService::notificationReplied, this, &JSNotifcationWrapper::onNotificationReplied);
}

void JSNotifcationWrapper::setNotificationService(NotificationService *notificationService) {
    this->notificationService = notificationService;
}

void JSNotifcationWrapper::deliverNotification(const QString &title, const QMap<QString, QVariant> &options)
{
    qDebug() << "Received notification: " << title << " " << options;

    if(qApp->activeWindow())
    {
        qDebug() << "Ignoring notification due to active window";
        return;
    }

    Notification notification;
    notification.setTitle(title);
    notification.setInformativeText(options["body"].toString());
    notification.setIdentifier(options["tag"].toString());

    notificationService->deliverNotification(notification);
}

void JSNotifcationWrapper::onNotificationClicked(const Notification &notification)
{
    QMap<QString, QVariant> options;
    options["body"] = notification.getInformativeText();
    options["tag"] = notification.getIdentifier();
    emit notificationClicked(notification.getTitle(), options);
}

void JSNotifcationWrapper::onNotificationReplied(const Notification &notification, const QString &reply)
{
    QMap<QString, QVariant> options;
    options["body"] = notification.getInformativeText();
    options["tag"] = notification.getIdentifier();
    emit notificationReplied(notification.getTitle(), options, reply);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    notificationService(nullptr),
    notificationWrapper(nullptr)
{
    ui->setupUi(this);

#ifndef Q_OS_OSX
    setWindowIcon(QIcon(":/artwork/icon/icon256.png"));
#endif

    initNotificationService();

    notificationWrapper = new JSNotifcationWrapper(notificationService, this);
    auto channel = new QWebChannel(this);
    channel->registerObject("notificationService", notificationWrapper);
    ui->webView->page()->setWebChannel(channel);

    connect(ui->webView, &WebView::titleChanged, this, &MainWindow::webViewTitleChanged);

    initActions();
    initMenus();

    readSettings();

    ui->webView->load(QUrl("https://web.whatsapp.com"));

    nativeSetup();
}

void MainWindow::initNotificationService() {
    if(notificationService) notificationService->deleteLater();

    notificationService = NotificationService::getNotificationService(this);
    connect(notificationService, &NotificationService::notificationClicked, this, &MainWindow::notificationClicked);
    connect(notificationService, &NotificationService::notificationReplied, this, &MainWindow::notificationReplied);

    if(notificationWrapper) notificationWrapper->setNotificationService(notificationService);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::webViewTitleChanged(const QString &title)
{
    qDebug() << "Title changed to: " << title;

    QString badge = "";
    QRegExp regex("\\(([0-9]+)\\) WhatsApp Web");

    if(regex.indexIn(title) > -1) {
        badge = regex.cap(1);
    }

    if(badge.isEmpty())
        setWindowTitle("WhatsQt");
    else
        setWindowTitle((badge.toInt() == 1 ? tr("%1 unread message") : tr("%1 unread messages")).arg(badge) + " - WhatsQt");

    notificationService->setApplicationBadge(badge);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();

#ifdef Q_OS_OSX
    hide();
    event->ignore();
#else
    QMainWindow::closeEvent(event);
#endif
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();
}

void MainWindow::initActions()
{
    QAction *action = ui->webView->pageAction(QWebEnginePage::Copy);
    action->setShortcut(QKeySequence::Copy);
    ui->webView->addAction(action);

    action = ui->webView->pageAction(QWebEnginePage::Cut);
    action->setShortcut(QKeySequence::Cut);
    ui->webView->addAction(action);

    action = ui->webView->pageAction(QWebEnginePage::Paste);
    action->setShortcut(QKeySequence::Paste);
    ui->webView->addAction(action);

    action = ui->webView->pageAction(QWebEnginePage::SelectAll);
    action->setShortcut(QKeySequence::SelectAll);
    ui->webView->addAction(action);

    action = ui->webView->pageAction(QWebEnginePage::Reload);
#ifdef Q_OS_OSX
    action->setShortcut(QKeySequence("Ctrl+R"));
#else
    action->setShortcut(QKeySequence("F5"));
#endif
    ui->webView->addAction(action);
}

void MainWindow::initMenus()
{
    QAction *aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        AboutDialog dialog(this);
        dialog.exec();
    });

    QAction *aboutQtAction = new QAction(tr("About Qt"), this);
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);

    QAction *preferencesAction = new QAction(tr("Preferences"), this);
    preferencesAction->setShortcut(QKeySequence("Ctrl+,"));

    connect(preferencesAction, &QAction::triggered, this, [this]() {
        PreferencesDialog dialog(this);
        if(dialog.exec() == QDialog::Accepted)
            initNotificationService();
    });

    QMenu *aboutMenu = menuBar()->addMenu(tr("Help"));
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addSeparator();
    aboutMenu->addAction(preferencesAction);
}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::WindowActivate)
    {
        qDebug() << "Window becoming active";
        notificationService->dismissNotifications();
    }

    return QMainWindow::event(event);
}

void MainWindow::notificationClicked(const Notification &notification)
{
    Q_UNUSED(notification)
    qDebug() << "Notification clicked";

}

void MainWindow::notificationReplied(const Notification &notification, const QString &reply)
{
    Q_UNUSED(notification)
    Q_UNUSED(reply)
    qDebug() << "Notification replied";
}
