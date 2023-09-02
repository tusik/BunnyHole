#ifndef CARROTLEAF_H
#define CARROTLEAF_H
#include <QObject>
#include <QString>
#include "file/bunnydir.h"
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
    QString from_host;
    QString to_host;
    CarrotOperatorCBorType type;
    bunny::Dir dir;
    QByteArray build_request();
    QJsonObject build_json();
    /// \brief 计算校验值的方法
    static QString checksum(QByteArray& obj);
    bool parse(QCborMap& map);
    bool parse(QJsonObject& map);
    CarrotProtocol protocol = Json;
};
Q_DECLARE_METATYPE(CarrotLeaf)
#endif // CARROTLEAF_H
