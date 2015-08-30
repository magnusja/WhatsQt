#include <QWebEngineProfile>
#include <QWebEnginePage>

#include "webview.h"
#include "net/cookiejar.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->setCookieJar(new CookieJar(this));

    QWebEngineProfile *profile = new QWebEngineProfile(this);
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Version/8.0.7 Safari/600.7.12");

    setPage(new QWebEnginePage(profile, this));
    page()->setNetworkAccessManager(manager);
    load(QUrl("https://web.whatsapp.com"));
}

