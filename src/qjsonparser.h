#ifndef QJSONPARSER_H
#define QJSONPARSER_H

#include <QVariantMap>

struct QJsonData;

class QJsonParser
{
public:
    static QJsonParser& instance();
    ~QJsonParser();

    QVariantMap parse();
    QString serialize();

protected:
    QJsonParser();

private:
    QJsonData* d;

};

#endif // QJSONPARSER_H
