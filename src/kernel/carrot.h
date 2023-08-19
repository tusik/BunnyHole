#ifndef CARROT_H
#define CARROT_H

#include <QFile>
#include "carrotleaf.h"
class Carrot
{
public:
    Carrot();
    Carrot(const Carrot& c);
    bool read_struct(QString file);
    bool parse_leaf(QByteArray obj);
    QByteArray transfer_request();
    QByteArray data();

    CarrotLeaf leaf;
private:
    QFile* target_file;

};

#endif // CARROT_H
