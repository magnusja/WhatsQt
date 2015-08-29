#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineProfile>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWebEngineProfile *profile = new QWebEngineProfile(ui->webView);
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Version/8.0.7 Safari/600.7.12");
    ui->webView->setPage(new QWebEnginePage(profile, ui->webView));
    ui->webView->load(QUrl("https://web.whatsapp.com"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
