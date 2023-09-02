#ifndef CARROT_H
#define CARROT_H

#include <QFile>
#include "carrotleaf.h"
#define CBOR_LEAF 0
#define CBOR_BODY 1
class Carrot
{
public:
    Carrot();
    Carrot(const Carrot& c);
    bool read_struct(QString file);
    bool parse(QByteArray obj);
    QByteArray build();
    QByteArray transfer_request();
    QByteArray data();

    CarrotLeaf leaf;
private:
    QFile* target_file;
    bool body_parse(QCborMap map);
};

#endif // CARROT_H
