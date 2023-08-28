#include "carrot.h"
#include <QJsonDocument>
#include <QObject>
#include <QJsonArray>
Carrot::Carrot()
{
    qRegisterMetaType<Carrot>("Carrot");
}

Carrot::Carrot(const Carrot &c)
{
    this->target_file = c.target_file;
    this->leaf = c.leaf;
}

bool Carrot::read_struct(QString file)
{
    target_file = new QFile(file);
    if(target_file->open(QIODevice::ReadOnly)){
//        leaf.name = target_file->fileName();
//        leaf.length = target_file->size();

        return true;
    }
    return false;
}

bool Carrot::parse(QByteArray obj)
{
    if(leaf.protocol == Cbor){
        QCborParserError error;
        QCborMap map;
        QCborValue cbor = QCborValue::fromCbor(obj, &error);
        map = cbor.toMap();
        auto leaf_map = map.value(CBOR_LEAF).toMap();
        // parse leaf
        leaf.parse(leaf_map);
        // parse body
        auto body_map = map.value(CBOR_BODY).toMap();
        return body_parse(body_map);
    }else if (leaf.protocol == Json) {
        auto map = QJsonDocument::fromJson(obj).object();
        auto leaf_map = map.value(QString::number(CBOR_LEAF)).toObject();
        auto body_map = map.value(QString::number(CBOR_BODY)).toObject();
        return leaf.parse(leaf_map);

    }
    return false;
}

QByteArray Carrot::build()
{
    leaf.build_request();
}

QByteArray Carrot::transfer_request()
{
    return leaf.build_request();
}

QByteArray Carrot::data()
{
    return QByteArray();
}

bool Carrot::body_parse(QCborMap map)
{
    return true;
}
