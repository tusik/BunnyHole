/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-09 22:25:31
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-10 14:09:17
 * @filePathColon: /
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef BUNNYDIR_H
#define BUNNYDIR_H

#include <QVector>
#include <QDir>
#include <QJsonObject>
#include <QCborMap>
#include <QCborStreamWriter>
#include <QStandardItemModel>
#include "bunnyfile.h"
namespace bunny {
static QByteArray cbor_to_byte(const QCborMap &map){
    QByteArray ba;
    QCborStreamWriter stream(&ba);
    map.toCborValue().toCbor(stream);
    return ba;
}
static QCborMap byte_to_cbor(const QByteArray& byte){
    QCborParserError error;
    QCborMap map;
    QCborValue cbor = QCborValue::fromCbor(byte, &error);
    qDebug() << error.errorString()<<cbor.isMap();
    map = cbor.toMap();
    return map;
}
class Dir
{
public:
    enum CBOR_TYPE{
        DIR = 0,
        FILE = 1
    };
    Dir();
    QVector<Dir> sub_dirs;
    QVector<File> files;
    QDir root;
    long long total_size =0;
    static Dir walk_path(QString root_path, int depth = 0);
    QJsonObject to_json();
    QCborMap to_cbor();
    int depth = 0;
    void serialise_map(QCborStreamWriter &stream, const QCborMap &map);
    static Dir parse(const QCborMap &map);
    static Dir parse(const QJsonObject &map);
    bool set_to_model(QStandardItemModel* model,QStandardItem* parent = nullptr);
};
}


#endif // BUNNYDIR_H
