#include "carrotleaf.h"

#include <QCryptographicHash>
QByteArray CarrotLeaf::build_request()
{
    QCborMap obj;
    auto data = dir.to_cbor();
    obj.insert(CarrotLeafCBorType::Data,data);
    obj.insert(CarrotLeafCBorType::OperatorType,CarrotOperatorCBorType::SendRequest);
    obj.insert(CarrotLeafCBorType::CheckSum,bunny::cbor_to_byte(data));
    return bunny::cbor_to_byte(obj);
}

QString CarrotLeaf::checksum(QByteArray &obj)
{
    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha1);
    hash.addData(obj);
    return hash.result().toHex();
}

bool CarrotLeaf::parse(QByteArray& obj)
{
    QCborMap map = bunny::byte_to_cbor(obj);
    auto data = bunny::cbor_to_byte(map[CarrotLeafCBorType::Data].toMap());
    type = CarrotOperatorCBorType(map[CarrotLeafCBorType::OperatorType].toInteger());
    return checksum(data)
           == map[CarrotLeafCBorType::CheckSum].toString();
}
