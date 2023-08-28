#ifndef BUNNYHOLE_H
#define BUNNYHOLE_H

#include <QObject>
#include <QUdpSocket>
#include <QUrl>
#include <QTimer>
#include <QList>

#include <QNetworkInterface>
#include "bunnyholeprotocol.h"
#include "configuration.h"
#include "bunny.h"
/**
 * @brief The BunnyHole class
 * UDP multicast tool to send & recive message from multicast address
 */
class BunnyHole : public QObject
{
    Q_OBJECT
public:
    explicit BunnyHole(Configuration c, QObject *parent = nullptr);
    QUdpSocket* udp_socket = nullptr;
    QUrl group_address = QUrl::fromUserInput("239.255.255.251:11223");
    QNetworkInterface local_interface;
    QHostAddress local_host;
    QList<QNetworkInterface> get_local_hostinfo();
    QTimer notify_timer;
    const Configuration config;

    Bunny bunny;
public slots:
    bool start(QString interface_name);

    // udp
    bool client_online();
    bool client_alive();
    void read_message();
    void message_process(BunnyHoleProtocol& bhp);
signals:
    void new_client_online(BunnyHoleProtocol protocol);
    void clinet_offline(BunnyHoleProtocol protocol);
    void new_transfer_request(Carrot c);
private:
};

#endif // BUNNYHOLE_H
