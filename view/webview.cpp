#include <QSettings>
#include <QDesktopServices>
#include <QWebEngineScript>
#include <QWebEngineProfile>
#include <QFile>
#include <QMessageBox>
#include <QCheckBox>

#include "webview.h"
#include "webpage.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    QWebEngineProfile *profile = new QWebEngineProfile(QLatin1String("WhatsQt"), this);
    connect(profile, &QWebEngineProfile::downloadRequested, this, &WebView::downloadRequested);

#ifdef Q_OS_OSX
    profile->setHttpUserAgent("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/600.7.12");
#elif defined(Q_OS_LINUX)
    profile->setHttpUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36");
#elif defined(Q_OS_WIN)
    profile->setHttpUserAgent("Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/537.36");
#endif
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    qDebug() << "WebEngine Cache path: " << profile->cachePath();
    qDebug() << "WebEngine Persistent Storage path: " << profile->persistentStoragePath();

    insertJavaScript(profile->scripts());

    auto page = new WebPage(profile, this);
    setPage(page);

    connect(page, &QWebEnginePage::featurePermissionRequested, this, &WebView::onFeaturePermissionRequest);

}

void WebView::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)
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


void WebView::downloadRequested(QWebEngineDownloadItem *download)
{
    qDebug() << "Download requested: " << download->url() << download->path();
    connect(download, &QWebEngineDownloadItem::stateChanged, this, &WebView::onDownloadStateChanged);
    connect(download, &QWebEngineDownloadItem::finished, this, &WebView::onDownloadFinished);
    connect(download, &QWebEngineDownloadItem::downloadProgress, this, &WebView::onDownloadProgress);
    download->accept();
}

void WebView::onFeaturePermissionRequest(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
    auto permissionString = [](QWebEnginePage::Feature feature) {
        switch(feature)
        {
            case QWebEnginePage::Geolocation:
                return tr("current location");
            case QWebEnginePage::MediaAudioVideoCapture:
                return tr("camera and microphone");
            case QWebEnginePage::MediaAudioCapture:
                return tr("microphone");
            case QWebEnginePage::MediaVideoCapture:
                return tr("camera");
            default:
                return tr("unknown");
        }
    };

    qDebug() << Q_FUNC_INFO;
    qDebug() << securityOrigin << " " << feature;

    QSettings settings;
    if(settings.value(QString("permission_granted_%1").arg(feature), false).toBool())
    {
        page()->setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
        return;
    }

    QMessageBox *box = new QMessageBox(QMessageBox::Question,
                                       tr("Permission Request"),
                                       tr("WhatsApp Web wants to access your %1, do you want to allow that?").arg(permissionString(feature)),
                                       QMessageBox::Yes | QMessageBox::No,
                                       this);

    QCheckBox *checkBox = new QCheckBox(tr("Remember this decision"), box);
    box->setCheckBox(checkBox);

    box->exec();

    bool accepted = box->clickedButton() == box->button(QMessageBox::Yes);
    if(accepted)
    {
        qDebug() << "Accepted feature request";
        page()->setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
    }
    else
    {
        qDebug() << "Denied feature request";
        page()->setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
    }

    if(checkBox->isChecked())
    {
        settings.setValue(QString("permission_granted_%1").arg(feature), accepted);
    }
}

void WebView::onDownloadFinished()
{
    qDebug() << "Download finished";
}

void WebView::onDownloadStateChanged(QWebEngineDownloadItem::DownloadState state)
{
    qDebug() << "Download state changed to: " << state;
}

void WebView::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << "Downloaded " << bytesReceived << " bytes from " << bytesTotal;
}