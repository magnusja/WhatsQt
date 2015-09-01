#include <QRegExp>
#include <QWebChannel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    notificationService = NotificationService::getNotificationService(this);
    auto channel = new QWebChannel(this);
    channel->registerObject("notificationService", notificationService);
    ui->webView->page()->setWebChannel(channel);

    connect(ui->webView, &WebView::titleChanged, this, &MainWindow::webViewTitleChanged);

    ui->webView->load(QUrl("https://web.whatsapp.com"));
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
        setWindowTitle(QString("(%0) WhatsQt").arg(badge));

    notificationService->setApplicationBadge(badge);
}
