#ifndef BUNNYHOLEPROTOCOL_H
#define BUNNYHOLEPROTOCOL_H

#include <QString>

class BunnyHoleProtocol
{
public:
    explicit BunnyHoleProtocol();
    void append(QString str);
    QString message_body;

};

#endif // BUNNYHOLEPROTOCOL_H
