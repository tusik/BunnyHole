#ifndef BUNNYHOLE_H
#define BUNNYHOLE_H

#include <QObject>
#include <QUdpSocket>
#include <QUrl>
class BunnyHole : public QObject
{
    Q_OBJECT
public:
    explicit BunnyHole(QObject *parent = nullptr);
    QUdpSocket* udp_socket = nullptr;
//    QHostAddress group_address = QHostAddress("239.255.255.251");
    QUrl group_address = QUrl::fromUserInput("239.255.255.251:11223");
    bool client_online();
public slots:
    void read_message();
signals:


};

#endif // BUNNYHOLE_H
