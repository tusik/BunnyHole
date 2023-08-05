/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-01 17:14:21
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-01 21:49:52
 * @FilePath: /BunnyHole/src/kernel/bunnyholeprotocolbuilder.h
 * @Description: 
 * 
 * Copyright (c) 2023 by Image image@by.cx, All Rights Reserved. 
 */
#ifndef BUNNYHOLEPROTOCOLBUILDER_H
#define BUNNYHOLEPROTOCOLBUILDER_H

#include <QObject>
#include <QProcess>
#include "bunnyholeprotocol.h"
class BunnyHoleProtocolBuilder
{
public:
    explicit BunnyHoleProtocolBuilder();
    static BunnyHoleProtocolBuilder builder();
    BunnyHoleProtocolBuilder& search();
    BunnyHoleProtocolBuilder& alive();
    BunnyHoleProtocolBuilder& host(QString host);
    BunnyHoleProtocolBuilder& user_agent();
    BunnyHoleProtocolBuilder& id(QString _id);
    BunnyHoleProtocolBuilder& hostname(QString hn);
    BunnyHoleProtocol build();
private:
    BunnyHoleProtocol protocol;
signals:

};

#endif // BUNNYHOLEPROTOCOLBUILDER_H
