#include "carrot.h"
#include <QJsonDocument>
#include <QObject>
Carrot::Carrot()
{
    qRegisterMetaType<Carrot>("Carrot");
}

Carrot::Carrot(const Carrot &c)
{
    this->target_file = c.target_file;
    this->leaf = c.leaf;
}

bool Carrot::read_struct(QString file)
{
    target_file = new QFile(file);
    if(target_file->open(QIODevice::ReadOnly)){
        leaf.name = target_file->fileName();
        leaf.length = target_file->size();

        return true;
    }
    return false;
}

bool Carrot::parse_leaf(QString json)
{
    auto obj = QJsonDocument::fromJson(json.toUtf8()).object();
    return leaf.parse(obj);
}

QByteArray Carrot::transfer_request()
{
    return leaf.build_request();
}

QByteArray Carrot::data()
{
    return QByteArray();
}
