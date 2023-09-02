#include "carrotleaf.h"

#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
QByteArray CarrotLeaf::build_request()
{
    if(protocol == Cbor){
        QCborMap obj;
        auto data = dir.to_cbor();
        obj.insert(CarrotLeafCBorType::Data,data);
        obj.insert(CarrotLeafCBorType::OperatorType,CarrotOperatorCBorType::SendRequest);
        obj.insert(CarrotLeafCBorType::CheckSum,bunny::cbor_to_byte(data));
        return bunny::cbor_to_byte(obj);
    }else if(protocol == Json){

        return QJsonDocument(build_json()).toJson(QJsonDocument::Compact);
    }
    return QByteArray();
}

QJsonObject CarrotLeaf::build_json()
{
    QJsonObject obj;
    auto data = dir.to_json();
    obj.insert(QString::number(CarrotLeafCBorType::Data),data);
    obj.insert(QString::number(CarrotLeafCBorType::OperatorType),CarrotOperatorCBorType::SendRequest);
    QByteArray data_ba =QJsonDocument(data).toJson(QJsonDocument::Compact);
    obj.insert(QString::number(CarrotLeafCBorType::CheckSum),checksum(data_ba));
    return obj;
}

QString CarrotLeaf::checksum(QByteArray &obj)
{
    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha1);
    hash.addData(obj);
    return hash.result().toHex();
}

bool CarrotLeaf::parse(QCborMap &map)
{
    //QCborMap map = bunny::byte_to_cbor(obj);

    auto data = bunny::cbor_to_byte(map[CarrotLeafCBorType::Data].toMap());
    type = CarrotOperatorCBorType(map[CarrotLeafCBorType::OperatorType].toInteger());
    return checksum(data)
           == map[CarrotLeafCBorType::CheckSum].toString();

}

bool CarrotLeaf::parse(QJsonObject &map)
{
    auto data = map[QString::number(CarrotLeafCBorType::Data)].toObject();
    type = CarrotOperatorCBorType(map[QString::number(CarrotLeafCBorType::OperatorType)].toInt());
    QByteArray data_ba =QJsonDocument(data).toJson(QJsonDocument::Compact);
    dir = bunny::Dir::parse(data);
    return checksum(data_ba)
           == map[QString::number(CarrotLeafCBorType::CheckSum)].toString();
}
