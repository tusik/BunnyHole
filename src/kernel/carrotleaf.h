#ifndef CARROTLEAF_H
#define CARROTLEAF_H
#include <QObject>
#include <QString>
#include <QJsonObject>
struct CarrotLeaf
{
    long long length;
    QString name;
    QByteArray build_request();
    /// \brief 计算校验值的方法
    static QString checksum(QJsonObject obj);
    bool parse(QJsonObject obj);
};
Q_DECLARE_METATYPE(CarrotLeaf)
#endif // CARROTLEAF_H
