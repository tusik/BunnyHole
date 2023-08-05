/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-01 17:14:21
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-01 22:01:33
 * @FilePath: /BunnyHole/src/kernel/bunnyholeprotocol.h
 * @Description: 
 * 
 * Copyright (c) 2023 by Image image@by.cx, All Rights Reserved.
 */
#ifndef BUNNYHOLEPROTOCOL_H
#define BUNNYHOLEPROTOCOL_H

#include <QString>
#include <QJsonObject>
#include "../ui/model/clientmodel.h"
class BunnyHoleProtocol
{
public:
    enum Operate{
        UNKNONW,
        WHEREYOUARE,
        IMHERE,
        BYEBYE
    };
    static const QString OperateStr[];
    explicit BunnyHoleProtocol();
    void build_message();
    bool parse(const QByteArray& data);
    QByteArray data();
    ClientModel to_client_model();
public:
    QJsonObject message_obj;
    int port;
    QString id;
    QString version;
    QString host;
    QString hostname;
    Operate current_operate;
    #ifdef __APPLE__
    ClientModel::OS os = ClientModel::OS::MAC;
    #elif defined _WIN32
    ClientModel::OS os = ClientModel::OS::WIN;
    #elif defined __linux__
    ClientModel::OS os = ClientModel::OS::LINUX;
    #endif
};

#endif // BUNNYHOLEPROTOCOL_H
