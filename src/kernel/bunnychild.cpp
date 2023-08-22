#include "bunnychild.h"
#include <QCborStreamWriter>
#include "carrot.h"
BunnyChild::BunnyChild(QObject *parent)
    : QObject{parent}
{

}

bool BunnyChild::connect_mom(QUrl url)
{
    socket = new QWebSocket();
    connect(socket,&QWebSocket::connected,this,[&](){
        qDebug()<<"connected";
    });
    connect(socket,&QWebSocket::disconnected,this,[](){

    });
    connect(socket,&QWebSocket::textMessageReceived,this,&BunnyChild::recive_message);
    socket->open(url);

    return true;
}

bool BunnyChild::send_file(QString path)
{
    Carrot carrot;
    carrot.read_struct(path);
    if(socket->sendTextMessage(carrot.transfer_request())>0){
        return true;
    }
    return false;
}

void BunnyChild::send_transfer_request(bunny::Dir dir)
{
    QByteArray ba;
    QCborStreamWriter writer(&ba);
    dir.serialiseCborMap(writer,dir.to_cbor());
    socket->sendTextMessage(ba);
}

void BunnyChild::recive_message(QString msg)
{

}
