/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-01 16:41:38
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-01 22:04:43
 * @filePathColon: /
 * @Description: 
 * 
 * Copyright (c) 2023 by Image image@by.cx, All Rights Reserved.
 */
#include "bunnyholeprotocolbuilder.h"
#include <version.h>
BunnyHoleProtocolBuilder::BunnyHoleProtocolBuilder()
{

}

BunnyHoleProtocolBuilder BunnyHoleProtocolBuilder::builder()
{
    return BunnyHoleProtocolBuilder();
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::search()
{
    protocol.current_operate = BunnyHoleProtocol::Operate::WHEREYOUARE;
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::alive()
{
    protocol.current_operate = BunnyHoleProtocol::Operate::IMHERE;
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::host(QString host)
{
    protocol.host = host;
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::user_agent()
{
    protocol.version = QString("%1.%2.%3")
            .arg(VERSION_MAJOR)
            .arg(VERSION_MINOR)
            .arg(VERSION_PATCH);
    return *this;
}

BunnyHoleProtocolBuilder& BunnyHoleProtocolBuilder::id(QString _id)
{
    protocol.id = _id;
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::hostname(QString hn)
{
    protocol.hostname = hn;
    return *this;
}

BunnyHoleProtocol BunnyHoleProtocolBuilder::build()
{
    protocol.build_message();
    return protocol;
}



