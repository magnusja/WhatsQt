#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QtNetwork/QNetworkCookieJar>

class CookieJar : public QNetworkCookieJar
{
public:
    CookieJar(QObject *parent = 0);
};

#endif // COOKIEJAR_H
