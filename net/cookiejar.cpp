#include <QDataStream>
#include <QList>
#include <QNetworkCookie>
#include <QDebug>
#include <QSettings>

#include "cookiejar.h"

QDataStream &operator<<(QDataStream &stream, const QList<QNetworkCookie> &cookies)
{
    stream << quint32(cookies.size());

    foreach(QNetworkCookie cookie, cookies) {
        stream << cookie.toRawForm();
    }

    return stream;
}

QDataStream &operator>>(QDataStream &stream, QList<QNetworkCookie> &cookies)
{
    cookies.clear();

    quint32 size;
    stream >> size;

    for(quint32 i = 0; i < size; i++)
    {
        QByteArray array;
        stream >> array;

        QList<QNetworkCookie> parsedCookies = QNetworkCookie::parseCookies(array);

        if(parsedCookies.size() == 0 && array.size() > 0) {
            qWarning() << "Error parsing cookies: " << array;
        }

        foreach (QNetworkCookie cookie, parsedCookies) {
            cookies.append(cookie);
        }

        if(stream.atEnd())
            break;
    }

    return stream;
}

CookieJar::CookieJar(QObject *parent)
    : QNetworkCookieJar(parent)
{
    qRegisterMetaTypeStreamOperators< QList<QNetworkCookie> >();

    QSettings settings;
    setAllCookies(qvariant_cast< QList<QNetworkCookie> >(settings.value(QLatin1String("cookies"))));
}

CookieJar::~CookieJar()
{
    qDebug() << "Saving cookies ...";
    QSettings settings;
    settings.setValue(QLatin1String("cookies"), QVariant::fromValue(allCookies()));
}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url)
{
    qDebug() << "Setting cookies for url: " << url;

    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

