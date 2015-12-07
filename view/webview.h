#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
#include <QWebEngineScriptCollection>
#include <QWebEngineDownloadItem>


class WebView : public QWebEngineView
{
public:
    WebView(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event);

private:
    void insertJavaScript(QWebEngineScriptCollection *scripts);

private slots:
    void downloadRequested(QWebEngineDownloadItem *download);
    void onFeaturePermissionRequest(const QUrl &securityOrigin, QWebEnginePage::Feature feature);

    void onDownloadStateChanged(QWebEngineDownloadItem::DownloadState state);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished();
};

#endif // WEBVIEW_H
