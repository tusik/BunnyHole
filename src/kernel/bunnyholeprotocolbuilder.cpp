/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-01 16:41:38
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-01 19:44:04
 * @filePathColon: /
 * @Description: 
 * 
 * Copyright (c) 2023 by Image image@by.cx, All Rights Reserved.
 */
#include "bunnyholeprotocolbuilder.h"

BunnyHoleProtocolBuilder::BunnyHoleProtocolBuilder()
{

}

BunnyHoleProtocolBuilder BunnyHoleProtocolBuilder::builder()
{
    return BunnyHoleProtocolBuilder();
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::search()
{
    protocol.message_body.append("M-SEARCH * HTTP/1.1\n\n");
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::host(QString hostname)
{
    protocol.append("HOST: ");
    protocol.append(hostname);
    protocol.append("\n\n");
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::man(QString man_str)
{
    protocol.append("MAN: ");
    protocol.append(man_str);
    protocol.append("\n\n");
    return *this;
}

BunnyHoleProtocolBuilder &BunnyHoleProtocolBuilder::mx(int mx_count)
{
    protocol.append("MX: ");
    protocol.append(QString::number(mx_count));
    protocol.append("\n\n");
    return *this;
}

BunnyHoleProtocol BunnyHoleProtocolBuilder::build()
{
    return protocol;
}
