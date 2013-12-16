#include "qjsonparser.h"

#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

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
