#include "carrotleaf.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
QByteArray CarrotLeaf::build_request()
{
    QJsonObject obj;
    obj["name"] = name;
    obj["length"] = length;
    obj["checksum"] = checksum(obj);
    return QJsonDocument(obj).toJson();
}

QString CarrotLeaf::checksum(QJsonObject obj)
{
    QCryptographicHash hash(QCryptographicHash::Algorithm::Sha1);
    hash.addData(obj["name"].toString().toUtf8());
    hash.addData(QString::number(obj["length"].toInt()).toUtf8());

    return hash.result().toHex();
}

bool CarrotLeaf::parse(QJsonObject obj)
{
    name = obj["name"].toString();
    length = obj["length"].toInt();
    return checksum(obj) == obj["checksum"].toString();
}
