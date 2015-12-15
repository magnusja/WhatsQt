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

#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>
#include <QWebEngineProfile>

class WebPage : public QWebEnginePage
{
    Q_OBJECT

public:
    explicit WebPage(QWebEngineProfile *profile, QWidget *parent = 0);
    ~WebPage();

    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);

protected:
    QWebEnginePage* createWindow(WebWindowType type);
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
    QStringList chooseFiles(FileSelectionMode mode, const QStringList &oldFiles, const QStringList &acceptedMimeTypes);

private:
    // Hack to open links in desktop browser see also createWindow implementation
    class OpenUrlWebPage : public QWebEnginePage {
    public:
        bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
    };

    OpenUrlWebPage* openUrlWebPage;
};

#endif // WEBPAGE_H
