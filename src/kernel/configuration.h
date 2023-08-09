#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QJsonObject>
#include <QFile>
class Configuration : public QObject
{
    Q_OBJECT
public:
    explicit Configuration(QObject *parent = nullptr);
    Configuration(Configuration& conf);
    bool read_from_file(QFile& f);
    bool write_to_file(QFile& f);
    bool new_config();
    QString system_id;
    QString data();
    QString generate_device_id();

private:

    int id_length = 8;
signals:

};

#endif // CONFIGURATION_H
