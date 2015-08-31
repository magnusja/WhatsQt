
#include <QWebEngineScriptCollection>
#include <QWebEngineScript>
#include <QWebEngineProfile>
#include <QFile>

#include "webview.h"
#include "webpage.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    QWebEngineProfile *profile = new QWebEngineProfile(QLatin1String("WhatsQt"), this);
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/600.7.12");
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    qDebug() << "WebEngine Cache path: " << profile->cachePath();
    qDebug() << "WebEngine Persistent Storage path: " << profile->persistentStoragePath();

    QWebEngineScript script;
    QFile file(":/js/bridge.js");
    file.open(QIODevice::ReadOnly);
    script.setSourceCode(file.readAll());
    script.setInjectionPoint(QWebEngineScript::DocumentReady);
    profile->scripts()->insert(script);

    WebPage *page = new WebPage(profile, this);
    setPage(page);

    load(QUrl("https://web.whatsapp.com"));
}

void WebView::contextMenuEvent(QContextMenuEvent */*event*/)
{
    // We do not want a context menu
}

