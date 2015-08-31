#include<QDesktopServices>

#include "webpage.h"

WebPage::WebPage(QWebEngineProfile *profile, QWidget *parent)
    : QWebEnginePage(profile, parent)
{

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

