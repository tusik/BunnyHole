#ifndef BUNNY_H
#define BUNNY_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMap>
#include <QSharedPointer>
#include "carrot.h"
/**
 * @brief Bunny, The WebSocket Server file transport worker.
 */
class BunnyHole;
class Bunny : public QObject
{
    Q_OBJECT
public:
    explicit Bunny(QObject *parent = nullptr);
    bool start(BunnyHole* home, int port = 22333);
    bool send_message(Carrot c);
    int port = 22333;
public slots:
    void new_child();
    void process_message(QString msg);
    void process_binary_message(QByteArray msg);
signals:
    void new_food_incoming(Carrot c);
private:
    BunnyHole* home = nullptr;
    QWebSocketServer* server = nullptr;
    QMap<QString,QWebSocket*> children;
    QMap<QString,ClientModel> children_models;
    QHash<QString, bool> transfer_status;
};

#endif // BUNNY_H
