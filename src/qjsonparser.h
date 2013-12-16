#ifndef QJSONPARSER_H
#define QJSONPARSER_H

#include <QVariantMap>

struct QJsonData;
class QScriptValue;
class QScriptEngine;

class QJsonParser
{
public:
    static QJsonParser& instance();
    ~QJsonParser();

    QVariantMap parse(const QString& string) const;
    QString serialize(const QVariant& value) const;

protected:
    QJsonParser();

private:
    QJsonData* d;
    static QScriptValue CreateValue(const QVariant& value, QScriptEngine& engine);


};

#endif // QJSONPARSER_H
