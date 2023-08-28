#include "bunnydir.h"
#include <QFileInfo>
#include <QDirIterator>
#include <QJsonArray>
#include <QCborMap>
#include <QCborArray>
bunny::Dir::Dir()
{

}

bunny::Dir bunny::Dir::walk_path(QString root_path, Dir *root_dir)
{
    Dir dir;
    if(root_dir == nullptr){
        dir.root = QDir(root_path);
        root_dir = &dir;
    }
    QDirIterator it(QFileInfo(root_path).absoluteFilePath());
    dir.root = QDir(root_path);
    root_dir->depth ++;
    // 128 is the max depth
    if(root_dir->depth > 128){
        root_dir->depth --;
        root_dir->failed_load_file_tree = true;
        qWarning("Max depth reached");
        return dir;
    }
    while(it.hasNext()){
        it.next();
        QFileInfo info = it.fileInfo();
        QStringList sub_dirs;
        if(info.isDir()){
            if(info.baseName() == "." || info.baseName() == ".." || info.baseName() == "" ){

            }else{
                dir.sub_dirs.append(walk_path(root_path+"/"+info.baseName(),root_dir));
                if (root_dir->failed_load_file_tree)
                {
                    return dir;
                }
                
            }
        }else if(info.isFile()){
            dir.files.append(File(info));
            root_dir->total_size += info.size();

        }

    }
    root_dir->depth --;
    return dir;
}

QJsonObject bunny::Dir::to_json()
{
    QJsonObject obj;
    QJsonArray file_arr;
    for(auto& i:files){
        QJsonObject file_obj;
        file_obj["N"] = i.file_name;
        file_obj["S"] = i.size;
        file_arr.append(file_obj);
    }
    obj.insert("F",file_arr);
    QJsonArray dir_arr;
    for(auto& i:sub_dirs){
        dir_arr.append(i.to_json());
    }
    obj.insert("D",dir_arr);
    return obj;

}

QCborMap bunny::Dir::to_cbor()
{
    QCborMap map;
    QCborArray file_arr;
    for(auto& i:files){
        QCborMap file_obj;
        file_obj.insert(File::CBOR_TYPE::FileName,i.file_name);
        file_obj.insert(File::CBOR_TYPE::Size,i.size);
        file_arr.append(file_obj);
    }
    map.insert(Dir::CBOR_TYPE::FILE,file_arr);
    QCborArray dir_arr;
    for(auto& i:sub_dirs){
        dir_arr.append(i.to_cbor());
    }
    map.insert(Dir::CBOR_TYPE::DIR,dir_arr);
    return map;
}

void bunny::Dir::serialise_map(QCborStreamWriter &stream, const QCborMap &map)
{
    map.toCborValue().toCbor(stream);
}

bunny::Dir bunny::Dir::parse(const QCborMap &map)
{
    Dir dir;
    QCborArray file_arr = map.value(Dir::CBOR_TYPE::FILE).toArray();
    for(auto i:file_arr){
        QCborMap file_obj = i.toMap();
        File file;
        file.file_name = file_obj.value(File::CBOR_TYPE::FileName).toString();
        file.size = file_obj.value(File::CBOR_TYPE::Size).toInteger();
        dir.files.append(file);
    }
    QCborArray dir_arr = map.value(Dir::CBOR_TYPE::DIR).toArray();
    for(auto i:dir_arr){
        QCborMap dir_obj = i.toMap();
        dir.sub_dirs.append(Dir::parse(dir_obj));
    }
    return dir;
}

bunny::Dir bunny::Dir::parse(const QJsonObject &map)
{
    Dir dir;
    QJsonArray file_arr = map[QString::number(Dir::CBOR_TYPE::FILE)].toArray();

    for(auto i:qAsConst(file_arr)){
        QJsonObject file_obj = i.toObject();
        File file;
        file.file_name = file_obj[QString::number(File::CBOR_TYPE::FileName)].toString();
        file.size = file_obj[QString::number(File::CBOR_TYPE::Size)].toInt();
        dir.files.append(file);
    }
    QJsonArray dir_arr = map[QString::number(Dir::CBOR_TYPE::DIR)].toArray();
    for(auto i :qAsConst(dir_arr)){
        QJsonObject dir_obj = i.toObject();
        dir.sub_dirs.append(Dir::parse(dir_obj));
    }
    return dir;
}

bool bunny::Dir::set_to_model(QStandardItemModel *model, QStandardItem *parent)
{
    QStandardItem* item = new QStandardItem(QIcon(),root.dirName());
    for(auto& i:sub_dirs){
        i.set_to_model(model,item);
    }
    for(auto& i:files){
        item->appendRow({new QStandardItem(QIcon(),i.file_name),new QStandardItem(QIcon(),i.size_str())});
    }
    if(parent==nullptr){
        model->appendRow(item);
    }else{
        parent->appendRow(item);
    }
    return true;
}
