#include <QApplication>

#include "qjsonparser.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QVariantMap map = QJsonParser::instance().parse( "{ 'name': 'reza', 'last': 'alizadeh majd' }");
    qDebug() << map;




    return a.exec();
}

