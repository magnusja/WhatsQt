#include <QWebEngineProfile>
#include <QWebEnginePage>

#include "webview.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    QWebEngineProfile *profile = new QWebEngineProfile(QLatin1String("WhatsQt"), this);
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/600.7.12");
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    qDebug() << "WebEngine Cache path: " << profile->cachePath();
    qDebug() << "WebEngine Persistent Storage path: " << profile->persistentStoragePath();

    QWebEnginePage *page = new QWebEnginePage(profile, this);
    setPage(page);

    load(QUrl("https://web.whatsapp.com"));
}

void WebView::contextMenuEvent(QContextMenuEvent */*event*/)
{
    // We do not want a context menu
}

