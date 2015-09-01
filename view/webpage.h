#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>
#include <QWebEngineProfile>

class WebPage : public QWebEnginePage
{
    Q_OBJECT

public:
    explicit WebPage(QWebEngineProfile *profile, QWidget *parent = 0);

    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);

protected:
    QWebEnginePage* createWindow(WebWindowType type);

private:
    // Hack to open links in desktop browser see also createWindow implementation
    class OpenUrlWebPage : public QWebEnginePage {
    public:
        OpenUrlWebPage(QObject *parent = 0) : QWebEnginePage(parent) { }
        bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
    };

    OpenUrlWebPage* openUrlWebPage;
};

#endif // WEBPAGE_H
