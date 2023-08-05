#include "configuration.h"
#include <QJsonDocument>
#include <QFile>
#include <random>

Configuration::Configuration(QObject *parent)
    : QObject{parent}
{

}

Configuration::Configuration(Configuration& conf)
{
    system_id = conf.system_id;
}

bool Configuration::read_from_file(QFile& f)
{
    if (f.open(QFile::ReadOnly)) {
		auto json = QJsonDocument::fromJson(f.readAll()).object();
		system_id = json.find("system_id").value().toString();
		return true;
	}
    return false;
}

bool Configuration::write_to_file(QFile& f)
{
    if (f.open(QFile::WriteOnly)) {
		f.write(data().toUtf8());
		return true;
	}
    return false;
}

bool Configuration::new_config()
{
    system_id = generate_device_id();
    return false;
}

QString Configuration::data()
{
    QJsonObject json;
    json["system_id"] = system_id;
    return QJsonDocument(json).toJson();
}

QString Configuration::generate_device_id()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(65, 90);
    QString id;
    for (auto i = 0; i < id_length; i++) {
        if (i == id_length / 2) {
            id.append("-");
        }
        id.append(distrib(gen));
    }
    return id;
}
