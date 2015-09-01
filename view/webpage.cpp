#include<QDesktopServices>

#include "webpage.h"

bool WebPage::OpenUrlWebPage::acceptNavigationRequest(const QUrl &url, NavigationType /*type*/, bool /*isMainFrame*/)
{
    qDebug() << "Navigation request for url: " << url;
    QDesktopServices::openUrl(url);
    return false;
}

WebPage::WebPage(QWebEngineProfile *profile, QWidget *parent)
    : QWebEnginePage(profile, parent),
      openUrlWebPage(new WebPage::OpenUrlWebPage())
{

}

WebPage::~WebPage()
{
    openUrlWebPage->deleteLater();
}

bool WebPage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    qDebug() << "Navigation request for url: " << url;
    if(type == QWebEnginePage::NavigationTypeLinkClicked) {
        QDesktopServices::openUrl(url);
        return false;
    }

    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}

QWebEnginePage* WebPage::createWindow(WebWindowType type) {
    // This is a hack, not everytime acceptNavigationRequest is called when user clicks on a link
    // but this method is called to create a new window
    // We just create a dummy page to open the URL in the desktop browser
    // see also here: https://github.com/tianyu/see/issues/3
    qDebug() << "New window requested for type: " << type;
    return openUrlWebPage;
}

