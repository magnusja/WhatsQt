#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QNetworkCookieJar>

class CookieJar : public QNetworkCookieJar
{
public:
    CookieJar(QObject *parent = 0);
    ~CookieJar();

    bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url);
};

#endif // COOKIEJAR_H
