#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <notification/notificationservice.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    NotificationService *notificationService;

private slots:
    void webViewTitleChanged(const QString &title);
};

#endif // MAINWINDOW_H
