#include <QDesktopServices>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QCheckBox>

#include "webpage.h"

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
    connect(this, &QWebEnginePage::featurePermissionRequested, this, &WebPage::onFeaturePermissionRequest);
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

void WebPage::onFeaturePermissionRequest(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
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
        setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
        return;
    }

    QMessageBox *box = new QMessageBox(QMessageBox::Question,
                                       tr("Permission Request"),
                                       tr("WhatsApp Web wants to access your %1, do you want to allow that?").arg(permissionString(feature)),
                                       QMessageBox::Yes | QMessageBox::No,
                                       view());

    QCheckBox *checkBox = new QCheckBox(tr("Remember this decision"), box);
    box->setCheckBox(checkBox);

    box->exec();

    bool accepted = box->clickedButton() == box->button(QMessageBox::Yes);
    if(accepted)
    {
        qDebug() << "Accepted feature request";
        setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
    }
    else
    {
        qDebug() << "Denied feature request";
        setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
    }

    if(checkBox->isChecked())
    {
        settings.setValue(QString("permission_granted_%1").arg(feature), accepted);
    }
}

