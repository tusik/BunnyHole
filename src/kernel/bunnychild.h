#ifndef BUNNYCHILD_H
#define BUNNYCHILD_H

#include <QObject>
#include <QWebSocket>
#include <QHostAddress>
#include "file/bunnydir.h"
class BunnyChild : public QObject
{
    Q_OBJECT
public:
    explicit BunnyChild(QObject *parent = nullptr);
    bool connect_mom(QHostAddress addr,int port);
public slots:
    bool send_file(QString path);
    void send_transfer_request(bunny::Dir dir);
signals:

private:
    QWebSocket* socket = nullptr;
};

#endif // BUNNYCHILD_H
