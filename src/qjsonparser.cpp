#include "qjsonparser.h"

#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtScript/QtScript>


struct QJsonData {

    QScriptEngine engine;
    QScriptValue parseFn;
    QScriptValue serializeFn;

};

QJsonParser & QJsonParser::instance()
{
    static QJsonParser theInstance;
    return theInstance;
}

QJsonParser::~QJsonParser()
{

}

QJsonParser::QJsonParser()
{
    d = new QJsonData;

    const QString script =
            "function parse_json(string) { return JSON.parse(string); }\n"
            "function serialize_json(object) { return JSON.stringify(object); }";

    QScriptValue result = d->engine.evaluate(script);

    d->parseFn = d->engine.globalObject().property("parse_json");
    d->serializeFn = d->engine.globalObject().property("serialize_json");
}

QVariantMap QJsonParser::parse(const QString &string) const
{
    QScriptValue result = d->parseFn.call(QScriptValue(), QScriptValueList() << QScriptValue(string));
    QVariantMap resultMap = result.toVariant().toMap();
    return resultMap;
}

QString QJsonParser::serialize(const QVariant &value) const
{
    QScriptValue arg = QJsonParser::CreateValue(value, d->engine);
    QScriptValue result = d->serializeFn.call(QScriptValue(), QScriptValueList() << QScriptValue(arg));
    QString resultString = result.toString();
    return resultString;
}

QScriptValue QJsonParser::CreateValue(const QVariant& value, QScriptEngine& engine)
{
    if(value.type() == QVariant::Map)
    {
        QScriptValue obj = engine.newObject();

        QVariantMap map = value.toMap();
        QVariantMap::const_iterator it = map.begin();
        QVariantMap::const_iterator end = map.end();

        while (it != end) {
            //obj.setProperty(it.key(), ::CreateValue(it.value(), engine));
            obj.setProperty(it.key(), CreateValue(it.value(), engine));
            ++it;
        }

        return obj;
    }

    if (value.type() == QVariant::List)
    {
        QVariantList list = value.toList();
        QScriptValue array = engine.newArray(list.length());
        for(int i=0; i < list.length(); ++i)
            array.setProperty(i, CreateValue(list.at(i), engine));
            //array.setProperty(i, ::CreateValue(list.at(i), engine));

        return array;
    }

    switch (value.type()) {

    case QVariant::String:
        return QScriptValue(value.toString());
    case QVariant::Int:
        return QScriptValue(value.toInt());
    case QVariant::UInt:
        return QScriptValue(value.toUInt());
    case QVariant::Bool:
        return QScriptValue(value.toBool());
    case QVariant::ByteArray:
        return QScriptValue(QLatin1String(value.toByteArray()));
    case QVariant::Double:
        return QScriptValue((qsreal)value.toDouble());
    default:
        break;
    }

    if (value.isNull())
        return QScriptValue(QScriptValue::NullValue);

    return engine.newVariant(value);

}

