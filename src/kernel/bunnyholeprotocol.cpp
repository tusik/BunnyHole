#include "bunnyholeprotocol.h"

BunnyHoleProtocol::BunnyHoleProtocol()
{

}

void BunnyHoleProtocol::append(QString str)
{
    message_body.append(str);
}
