#ifndef BUNNYFILE_H
#define BUNNYFILE_H
#include <QObject>
#include <QFileInfo>
namespace bunny {
class File
{
public:
    enum CBOR_TYPE{
        FileName = 0,
        Size = 1
    };
    File();
    File(QFileInfo& info);
    long long size;
    QString file_name;
    static QString size_str(long number);

};
}


#endif // BUNNYFILE_H
