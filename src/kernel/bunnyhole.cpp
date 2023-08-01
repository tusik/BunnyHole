#include "bunnyhole.h"
#include <QNetworkInterface>
#include "bunnyholeprotocolbuilder.h"
BunnyHole::BunnyHole(QObject *parent) : QObject(parent)
{

    udp_socket = new QUdpSocket(this);
    auto res = udp_socket->bind(QHostAddress::AnyIPv4,group_address.port(),QUdpSocket::ShareAddress);
    if(!res){
        return;
    }
    res = udp_socket->joinMulticastGroup(QHostAddress(group_address.host()));
    if(!res){
        return;
    }
    connect(udp_socket,&QUdpSocket::readyRead,this,&BunnyHole::read_message);
}

bool BunnyHole::client_online()
{

    auto protocol = BunnyHoleProtocolBuilder::builder()
            .host(group_address.toString())
            .man("ssdp:discocver")
            .mx(1)
            .build();
    QByteArray data = protocol.message_body.toUtf8();
    auto res = udp_socket->write(data,data.length());
    if(res != data.length()){
        return false;
    }
    return true;
}

void BunnyHole::read_message()
{
    while (udp_socket->hasPendingDatagrams()) {
        QByteArray reply;
        reply.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(reply.data(), reply.size());
        qDebug() << reply.data();
    }

}
