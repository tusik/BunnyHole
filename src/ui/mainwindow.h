#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../kernel/bunnyhole.h"
#include "../kernel/bunnychild.h"
#include "../kernel/configuration.h"
#include "model/clientmodel.h"
#include "../kernel/file/bunnydir.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    BunnyHole* hole = nullptr;
    Configuration config;
private slots:
    void on_connect_btn_clicked();

    bool read_local_data();
    bool write_local_data();
    void new_clien_oneline(BunnyHoleProtocol protoc);
    void client_offline(BunnyHoleProtocol protoc);
    void send_transfer_request(bunny::Dir dir);
    void recive_transfer_request(bunny::Dir dir);
    void send_accpet_transfer_request(QString host);
private:
    Ui::MainWindow *ui;
    QHash<ClientModel,BunnyChild*> bunnys;

};
#endif // MAINWINDOW_H
