﻿/*
 * @Author: Image image@by.cx
 * @Date: 2023-08-09 21:25:59
 * @LastEditors: Image image@by.cx
 * @LastEditTime: 2023-08-10 16:32:04
 * @filePathColon: /
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "bunnyfile.h"

bunny::File::File()
{

}

bunny::File::File(QFileInfo &info)
{
    this->file_name = info.fileName();
    this->size = info.size();
}

QString bunny::File::size_str()
{
    if(size < 1024){
        return QString::number(size)+" Byte";
    }else if(size < 1024*1024){
        return QString::number(size/1024)+" KB";
    }else if(size < 1024*1024*1024){
        return QString::number(size/1024/1024)+" MB";
    }else{
        return QString::number(size/1024/1024/1024)+" GB";
    }
    
}
