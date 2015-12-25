/*
 * This file is part of WhatsQt.
 *
 * WhatsQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WhatsQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WhatsQt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
#include <QWebEngineScriptCollection>
#include <QWebEngineDownloadItem>

#include "util/Preferences.h"

class WebView : public QWebEngineView
{
public:
    WebView(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event);

private:
    Preferences preferences;

    void insertJavaScript(QWebEngineScriptCollection *scripts);

private slots:
    void downloadRequested(QWebEngineDownloadItem *download);
    void onFeaturePermissionRequest(const QUrl &securityOrigin, QWebEnginePage::Feature feature);

    void onDownloadStateChanged(QWebEngineDownloadItem::DownloadState state);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished();
};

#endif // WEBVIEW_H
