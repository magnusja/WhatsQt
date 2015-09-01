#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
#include <QWebEngineScriptCollection>

class WebView : public QWebEngineView
{
public:
    WebView(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event);

private:
    void insertJavaScript(QWebEngineScriptCollection *scripts);
};

#endif // WEBVIEW_H
