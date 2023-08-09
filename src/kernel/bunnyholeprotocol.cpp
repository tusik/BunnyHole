/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-01 17:14:21
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-02 15:40:31
 * @filePathColon: /
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "bunnyholeprotocol.h"
#include <QStringList>
#include <QJsonDocument>

BunnyHoleProtocol::BunnyHoleProtocol()
{

}

void BunnyHoleProtocol::build_message()
{
    message_obj.insert("SAY",current_operate);
    message_obj.insert("PORT", port);
    QJsonObject ua_obj;
    ua_obj.insert("OS", os);
    ua_obj.insert("VERSION", version);
    ua_obj.insert("HOSTNAME",hostname);
    message_obj.insert("USER_AGENT", ua_obj);
}

bool BunnyHoleProtocol::parse(const QByteArray &data)
{
    message_obj = QJsonDocument::fromJson(data).object();
    if (message_obj.isEmpty()) {
        return false;
    }
    current_operate = Operate(message_obj.find("SAY").value().toInt());
    port = message_obj.find("PORT").value().toInt();
    QJsonObject ua_obj = message_obj.find("USER_AGENT").value().toObject();
    os = ClientModel::OS(ua_obj.find("OS").value().toInt());
    version = ua_obj.find("VERSION").value().toString();
    hostname = ua_obj.find("HOSTNAME").value().toString();
    return true;
}

QByteArray BunnyHoleProtocol::data()
{
    return QJsonDocument(message_obj).toJson(QJsonDocument::Compact);
}

ClientModel BunnyHoleProtocol::to_client_model()
{
    ClientModel model;
    model.ip = host;
    model.port = port;
    model.id = id;
    model.os = os;
    model.hostname = hostname;
    return model;
}
