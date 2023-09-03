#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
#include <QJsonObject>
#include "../include/version.h"
class ClientModel
{
public:
    ClientModel();
    enum OS{
        UNKOWN,
        MAC,
        WIN,
        LINUX
    };
    OS os;
    QString version = QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);
    QString id;
    QString ip;
    QString hostname;
    int port;
    bool operator == (const ClientModel& model) const{
        return model.port == this->port && model.ip == this->ip && model.hostname == this->hostname;
    }
    QJsonObject to_json(){
        QJsonObject obj;
        obj.insert("id",id);
        obj.insert("ip",ip);
        obj.insert("hostname",hostname);
        obj.insert("port",port);
        obj.insert("version",version);
        return obj;
    }
    static ClientModel from_json(QJsonObject obj){
        ClientModel model;
        model.id = obj.value("id").toString();
        model.ip = obj.value("ip").toString();
        model.hostname = obj.value("hostname").toString();
        model.port = obj.value("port").toInt();
        model.version = obj.value("version").toString();
        return model;
    }
};
inline uint qHash(const ClientModel &key, uint seed = 0)
{
    uint ret = qHash(key.ip, seed)^qHash(key.port, seed);
    return ret;
}



#endif // CLIENTMODEL_H
