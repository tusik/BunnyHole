#ifndef BUNNYHOLEPROTOCOLBUILDER_H
#define BUNNYHOLEPROTOCOLBUILDER_H

#include <QObject>
#include "bunnyholeprotocol.h"
class BunnyHoleProtocolBuilder
{
public:
    explicit BunnyHoleProtocolBuilder();
    static BunnyHoleProtocolBuilder builder();
    BunnyHoleProtocolBuilder& search();
    BunnyHoleProtocolBuilder& host(QString hostname);
    BunnyHoleProtocolBuilder& man(QString man_str);
    BunnyHoleProtocolBuilder& mx(int mx_count);
    BunnyHoleProtocol build();
private:
    BunnyHoleProtocol protocol;
signals:

};

#endif // BUNNYHOLEPROTOCOLBUILDER_H
