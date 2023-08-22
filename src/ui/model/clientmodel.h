#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QObject>
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
    QString version;
    QString id;
    QString ip;
    QString hostname;
    int port;
    bool operator == (const ClientModel& model) const{
        return model.port == this->port && model.ip == this->ip && model.hostname == this->hostname;
    }
};
inline uint qHash(const ClientModel &key, uint seed = 0)
{
    uint ret = qHash(key.ip, seed)^qHash(key.port, seed);
    return ret;
}



#endif // CLIENTMODEL_H
