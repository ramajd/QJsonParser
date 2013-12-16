#include "qjsonparser.h"

QJsonParser & QJsonParser::instance()
{
    static QJsonParser theInstance;
    return theInstance;
}
