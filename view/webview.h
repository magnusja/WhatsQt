#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>

class WebView : public QWebEngineView
{
public:
    WebView(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // WEBVIEW_H
