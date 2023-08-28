#ifndef BUNNYCHILD_H
#define BUNNYCHILD_H

#include <QObject>
#include <QWebSocket>
#include <QHostAddress>
#include "file/bunnydir.h"
#include "carrot.h"
/**
 * @brief The BunnyChild WebSocket Client connect class
 */
class BunnyChild : public QObject
{
    Q_OBJECT
public:
    explicit BunnyChild(QObject *parent = nullptr);
    bool connect_mom(QUrl url);
    bool ws_status = false;
public slots:
    bool send_file(QString path);
    void send_transfer_request(Carrot c);
    void recive_message(QString msg);
signals:

private:
    QWebSocket* socket = nullptr;
    QByteArray transfered_buffer;
};

#endif // BUNNYCHILD_H
