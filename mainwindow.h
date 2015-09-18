#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <notification/notificationservice.h>

namespace Ui {
class MainWindow;
}

class JSNotifcationWrapper : public QObject {

    Q_OBJECT

public:
    JSNotifcationWrapper(NotificationService *service, QObject *parent = 0);

    Q_INVOKABLE void deliverNotification(const QString &title, const QMap<QString, QVariant> &options);

private:
    NotificationService *notificationService;
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

    void saveSettings();
    void readSettings();

    void initActions();

private slots:
    void webViewTitleChanged(const QString &title);
};

#endif // MAINWINDOW_H
