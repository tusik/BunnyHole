#include "bunnyhole.h"
#include "bunnyholeprotocolbuilder.h"
#include <QHostInfo>
BunnyHole::BunnyHole(Configuration c, QObject *parent) :QObject(parent), config(c)
{

    qRegisterMetaType<BunnyHoleProtocol>("BunnyHoleProtocol");
    udp_socket = new QUdpSocket(this);
}

bool BunnyHole::client_online()
{
    auto v4_list = get_local_hostinfo();
    if(v4_list.isEmpty()){
        return false;
    }
    auto protocol = BunnyHoleProtocolBuilder::builder()
            .host(local_host.toString())
            .search()
            .user_agent()
            .hostname(QHostInfo::localHostName())
            .id(config.system_id)
            .port(bunny.port)
            .build();
    QByteArray data = protocol.data();
    if(udp_socket->isOpen()){

    }
    auto res = udp_socket->writeDatagram(data,QHostAddress(group_address.host()),group_address.port());
    if(res != data.length()){
        return false;
    }
    return true;
}

bool BunnyHole::client_alive()
{
    auto protocol = BunnyHoleProtocolBuilder::builder()
            .host(local_host.toString())
            .alive()
            .hostname(QHostInfo::localHostName())
            .user_agent()
            .port(bunny.port)
            .id(config.system_id)
            .build();
    QByteArray data = protocol.data();
    if(udp_socket->isOpen()){

    }
    auto res = udp_socket->writeDatagram(data,QHostAddress(group_address.host()),group_address.port());
    if(res != data.length()){
        return false;
    }
    return true;
}

QList<QNetworkInterface> BunnyHole::get_local_hostinfo()
{
    QList<QNetworkInterface> v4_address_set;
    auto face_list = QNetworkInterface::allInterfaces();
    for(auto& i:face_list){
        for(auto& t:i.addressEntries()){
            if(t.ip().protocol() == QAbstractSocket::NetworkLayerProtocol::IPv4Protocol){
                v4_address_set.append(i);
            }
        }
    }
    return v4_address_set;
}

bool BunnyHole::start(QString interface_name)
{
    /// activate BunnyHole UDP announce server
    auto res = udp_socket->bind(QHostAddress::AnyIPv4,group_address.port(),QUdpSocket::ShareAddress);
    udp_socket->setSocketOption(QAbstractSocket::MulticastTtlOption,128);
    if(!res){
        return false;
    }
    local_interface = QNetworkInterface().interfaceFromName(interface_name);

    for(auto& t:local_interface.addressEntries()){
        if(t.ip().protocol() == QAbstractSocket::NetworkLayerProtocol::IPv4Protocol){
            local_host = t.ip();
        }
    }

    udp_socket->setMulticastInterface(local_interface);
    res = udp_socket->joinMulticastGroup(QHostAddress(group_address.host()));
    if(!res){
        return false;
    }
    connect(udp_socket,&QUdpSocket::readyRead,this,&BunnyHole::read_message);
    client_online();
    connect(&notify_timer,&QTimer::timeout,this,&BunnyHole::client_alive);
    notify_timer.setInterval(3000);
//    notify_timer.start();
    /// activate Bunny TCP transfer
    bunny.start(this);
    connect(&bunny,&Bunny::new_food_incoming,this,&BunnyHole::new_transfer_request);
    return true;
}

void BunnyHole::read_message()
{
    while (udp_socket->hasPendingDatagrams()) {
        QByteArray reply;
        reply.resize(udp_socket->pendingDatagramSize());
        QHostAddress add;
        udp_socket->readDatagram(reply.data(), reply.size(),&add);
        BunnyHoleProtocol protocol;
        protocol.host = add.toString();
        if(protocol.parse(reply)){
            qDebug().noquote() << protocol.data();
            if(protocol.host == local_host.toString()){
                // ignore
            }else{
                // process message
                message_process(protocol);
            }
        }
    }

}

void BunnyHole::message_process(BunnyHoleProtocol& bhp)
{
    if (bhp.current_operate == BunnyHoleProtocol::Operate::WHEREYOUARE) {
		auto protocol = BunnyHoleProtocolBuilder::builder()
				.host(local_host.toString())
				.alive()
				.user_agent()
                .hostname(QHostInfo::localHostName())
                .port(bunny.port)
				.build();
		QByteArray data = protocol.data();
        
		auto res = udp_socket->writeDatagram(data,QHostAddress(group_address.host()),group_address.port());
        if (res != data.length()) {
			return;
		}
        online_clients.insert(bhp.host,bhp.to_client_model());
        emit new_client_online(bhp);
    }else if (bhp.current_operate == BunnyHoleProtocol::Operate::BYEBYE) {
        emit clinet_offline(bhp);
    }else if (bhp.current_operate == BunnyHoleProtocol::Operate::IMHERE) {
        online_clients.insert(bhp.host,bhp.to_client_model());
        emit new_client_online(bhp);
    }else if (bhp.current_operate == BunnyHoleProtocol::Operate::UNKNONW) {

    }
}
