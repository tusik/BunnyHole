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

struct CarrotLeaf
{
    QString from_host;
    QString to_host;
    CarrotOperatorCBorType type;
    bunny::Dir dir;
    QByteArray build_request();
    /// \brief 计算校验值的方法
    static QString checksum(QByteArray& obj);
    bool parse(QByteArray& obj);
};
Q_DECLARE_METATYPE(CarrotLeaf)
#endif // CARROTLEAF_H
