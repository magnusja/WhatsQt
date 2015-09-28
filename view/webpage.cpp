#include <QDesktopServices>
#include <QSettings>
#include <QFileDialog>

#include "webpage.h"
#include "webview.h"

bool WebPage::OpenUrlWebPage::acceptNavigationRequest(const QUrl &url, NavigationType /*type*/, bool /*isMainFrame*/)
{
    qDebug() << "Navigation request for url: " << url;
    QDesktopServices::openUrl(url);
    return false;
}

WebPage::WebPage(QWebEngineProfile *profile, QWidget *parent)
    : QWebEnginePage(profile, parent),
      openUrlWebPage(new WebPage::OpenUrlWebPage())
{
}

WebPage::~WebPage()
{
    openUrlWebPage->deleteLater();
}

bool WebPage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    qDebug() << "Navigation request for url: " << url;
    if(type == QWebEnginePage::NavigationTypeLinkClicked) {
        QDesktopServices::openUrl(url);
        return false;
    }

    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}

QWebEnginePage* WebPage::createWindow(WebWindowType type)
{
    // This is a hack, not everytime acceptNavigationRequest is called when user clicks on a link
    // but this method is called to create a new window
    // We just create a dummy page to open the URL in the desktop browser
    // see also here: https://github.com/tianyu/see/issues/3

    // TODO: try linkDelegationPolicy
    qDebug() << "New window requested for type: " << type;
    return openUrlWebPage;
}

void WebPage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
    qDebug() << "JS Console: line: " << lineNumber;
    qDebug() << "JS Console: src id: " << sourceID;
    qDebug() << "JS Console: level: " << level;
    qDebug() << "JS Console: " << message;
}

QStringList WebPage::chooseFiles(FileSelectionMode mode, const QStringList &oldFiles, const QStringList &acceptedMimeTypes)
{
    Q_UNUSED(oldFiles)
    Q_UNUSED(acceptedMimeTypes)
    // TODO: support mime types
    QStringList result;

    QSettings settings;
    QString suggestedPath;
    suggestedPath = settings.value("lastMediaPath", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0]).toString();

    if(mode == QWebEnginePage::FileSelectOpen) {
        QString file = QFileDialog::getOpenFileName(view(), tr("Choose Media File"), suggestedPath);
        if(!file.isNull()) {
            result.append(file);
        }
    } else {
        result = QFileDialog::getOpenFileNames(view(), tr("Choose Media Files"), suggestedPath);
    }

    if(!result.isEmpty()) {
        settings.setValue("lastMediaPath", result[0]);
    }

    return result;
}

