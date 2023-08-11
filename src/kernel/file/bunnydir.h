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
#include <QStandardItemModel>
#include "bunnyfile.h"
namespace bunny {
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
    bool failed_load_file_tree = false;
    Dir walk_path(QString root_path,Dir& root_dir);
    QJsonObject to_json();
    QCborMap to_cbor();
    int depth = 0;
    void serialiseCborMap(QCborStreamWriter &stream, const QCborMap &map);
    static Dir parse(const QCborMap &map);
    bool set_to_model(QStandardItemModel* model,QStandardItem* parent = nullptr);
};
}


#endif // BUNNYDIR_H
