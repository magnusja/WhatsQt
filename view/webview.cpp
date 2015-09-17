
#include <QWebEngineScript>
#include <QWebEngineProfile>
#include <QFile>

#include "webview.h"
#include "webpage.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    QWebEngineProfile *profile = new QWebEngineProfile(QLatin1String("WhatsQt"), this);
#ifdef Q_OS_OSX
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/600.7.12");
#elif defined(Q_OS_LINUX)
    profile->setHttpUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36");
#endif
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    qDebug() << "WebEngine Cache path: " << profile->cachePath();
    qDebug() << "WebEngine Persistent Storage path: " << profile->persistentStoragePath();

    insertJavaScript(profile->scripts());

    auto page = new WebPage(profile, this);
    setPage(page);
}

void WebView::contextMenuEvent(QContextMenuEvent */*event*/)
{
    // We do not want a context menu
}

void WebView::insertJavaScript(QWebEngineScriptCollection *scripts)
{
    QFile webChannelFile(":/qtwebchannel/qwebchannel.js");
    webChannelFile.open(QIODevice::ReadOnly);
    QWebEngineScript webChannelScript;
    webChannelScript.setSourceCode(webChannelFile.readAll());
    webChannelScript.setInjectionPoint(QWebEngineScript::DocumentCreation);
    webChannelScript.setWorldId(QWebEngineScript::MainWorld);
    scripts->insert(webChannelScript);

    QWebEngineScript script;
    QFile file(":/js/bridge.js");
    file.open(QIODevice::ReadOnly);
    script.setSourceCode(file.readAll());
    script.setInjectionPoint(QWebEngineScript::DocumentReady);
    script.setWorldId(QWebEngineScript::MainWorld);
    scripts->insert(script);
}
