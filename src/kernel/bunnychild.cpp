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
        ws_status = true;
        if(!transfered_buffer.isEmpty()){
            socket->sendTextMessage(transfered_buffer);
            transfered_buffer.clear();
        }
    });
    connect(socket,&QWebSocket::disconnected,this,[&](){
        ws_status = false;
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

void BunnyChild::send_transfer_request(Carrot c)
{
    c.leaf.type = CarrotOperatorCBorType::SendRequest;
    transfered_buffer = c.build();
    if(ws_status){
        socket->sendTextMessage(transfered_buffer);
        transfered_buffer.clear();
    }
}

void BunnyChild::recive_message(QString msg)
{

}
