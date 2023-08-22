#include "bunny.h"
#include "carrot.h"
Bunny::Bunny(QObject *parent)
    : QObject{parent}
{

}

bool Bunny::start(int port)
{
    if(server != nullptr){
        server->close();
        server->deleteLater();
    }
    this->port = port;
    server = new QWebSocketServer("",QWebSocketServer::NonSecureMode);
    if(server->listen(QHostAddress::Any,this->port)){
        connect(server,&QWebSocketServer::newConnection,this,&Bunny::new_child);
        return true;
    }
    return false;
}

bool Bunny::send_message(Carrot c)
{
    QWebSocket* child_socket = children[c.leaf.to_host];
    return true;
}

void Bunny::new_child()
{
    QWebSocket* child_socket = server->nextPendingConnection();
    auto host = child_socket->peerAddress();
    children.insert(host.toString(), child_socket);
    connect(child_socket,&QWebSocket::textMessageReceived,this,&Bunny::process_message);
}

void Bunny::process_message(QString msg)
{
    QWebSocket* child_socket = static_cast<QWebSocket*>(sender());

    if(transfer_status[child_socket->peerAddress().toString()] == false){

        Carrot carrot;
        if(carrot.parse_leaf(msg.toUtf8())){
            switch(carrot.leaf.type){
            case CarrotOperatorCBorType::SendRequest:
                emit new_food_incoming(carrot);
                break;
            }
        }
        child_socket->sendTextMessage(carrot.transfer_request());

    }


}
