#ifndef CARROTLEAF_H
#define CARROTLEAF_H
#include <QObject>
#include <QString>
#include "file/bunnydir.h"
#include "../ui/model/clientmodel.h"
enum CarrotLeafCBorType{
    Data,
    CheckSum,
    OperatorType
};
enum CarrotOperatorCBorType{
    SendRequest,
    AcceptFileTransfer,
};
enum CarrotProtocol{
    Json,
    Cbor
};

struct CarrotLeaf
{
    QString from;
    QString to;
    CarrotOperatorCBorType type;
    bunny::Dir dir;
    QByteArray build_request();
    QJsonObject build_json();
    /// \brief verify data with sha1
    static QString checksum(QByteArray& obj);
    bool parse(QCborMap& map);
    bool parse(QJsonObject& map);
    CarrotProtocol protocol = Json;
};
Q_DECLARE_METATYPE(CarrotLeaf)
#endif // CARROTLEAF_H
