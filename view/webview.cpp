#include <QWebEngineProfile>
#include <QWebEnginePage>

#include "webview.h"
#include "net/cookiejar.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    QWebEngineProfile *profile = new QWebEngineProfile(QLatin1String("WhatsQt"), this);
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Version/8.0.7 Safari/600.7.12");
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    qDebug() << "WebEngine Cache path: " << profile->cachePath();
    qDebug() << "WebEngine Persistent Storage path: " << profile->persistentStoragePath();

    setPage(new QWebEnginePage(profile, this));
    load(QUrl("https://web.whatsapp.com"));
}

