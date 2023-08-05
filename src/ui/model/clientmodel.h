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
};


#endif // CLIENTMODEL_H
