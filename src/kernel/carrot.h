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
    bool parse_leaf(QString json);
    QByteArray transfer_request();
    QByteArray data();
private:
    QFile* target_file;
    CarrotLeaf leaf;

};

#endif // CARROT_H
