#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../kernel/bunnyhole.h"
#include "../kernel/configuration.h"
#include "model/clientmodel.h"
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
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
