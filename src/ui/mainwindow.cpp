#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QStandardItem>
#include "listitem.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);
    file.close();
    ui->comboBox->view()->window()->setWindowFlags( Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint );
    ui->comboBox->setView(new QListView);

    hole = new BunnyHole(config, this);
    auto list = hole->get_local_hostinfo();
    for(auto& i:qAsConst(list)){
        for(auto& add: i.addressEntries()){
            if(add.ip().protocol() == QAbstractSocket::NetworkLayerProtocol::IPv4Protocol){
                ui->comboBox->addItem(add.ip().toString(),QList<QVariant>()<<i.name());
            }
        }
    }
    connect(hole, &BunnyHole::new_client_online,this,&MainWindow::new_clien_oneline);
    connect(hole, &BunnyHole::clinet_offline, this, &MainWindow::client_offline);
    // read config file
    if (read_local_data()) {

    }else {
        // no config file fond
        write_local_data();
    }

    ui->listWidget->setSpacing(0);
    ui->listWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    for(auto i=0;i<5;i++){
        ClientModel c;
        c.ip = QString::number(i);
        c.hostname = "sdasd";
        ListItem* item = new ListItem(c);

        item->title_height = 60;
        QListWidgetItem * pItem = new QListWidgetItem();
        pItem->setSizeHint({300,60});
        ui->listWidget->addItem(pItem);
        ui->listWidget->setItemWidget(pItem,item);
        connect(item, &ListItem::size_changed, [pItem](int h){
            pItem->setSizeHint(QSize(pItem->sizeHint().width(), h));
        });
    }

}

MainWindow::~MainWindow()
{
    hole->deleteLater();
    delete ui;
}

bool MainWindow::read_local_data()
{
    QString base_path = QApplication::applicationDirPath();
    QString data_path = base_path+"/data";
    QFile file(data_path +"/config.json");
    auto res = file.exists() && config.read_from_file(file);
    file.close();
    return res;
}

bool MainWindow::write_local_data()
{
    QString base_path = QApplication::applicationDirPath();
    QString data_path = base_path + "/data";
    QDir(base_path).mkdir("data");
    QFile file(data_path + "/config.json");
    
    config.new_config();
    auto res = config.write_to_file(file);
    file.close();
    return res;
}

void MainWindow::new_clien_oneline(BunnyHoleProtocol protoc)
{
    

    QListWidgetItem* pItem = new QListWidgetItem();
    ListItem* item = new ListItem(protoc.to_client_model());
    item->title_height = 60;
    pItem->setText(protoc.host);
    pItem->setSizeHint({ 300,60 });
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, item);

    connect(item, &ListItem::size_changed, [pItem](int h) {
        pItem->setSizeHint(QSize(pItem->sizeHint().width(), h));
    });
}

void MainWindow::client_offline(BunnyHoleProtocol protoc)
{
    auto list = ui->listWidget->findItems(protoc.host, Qt::MatchExactly);
    for (auto& i : list) {
        delete i;
    }
    //qDeleteAll(ui->listWidget->findItems(protoc.host, Qt::MatchFixedString));
}


void MainWindow::on_connect_btn_clicked()
{
    auto face_name = ui->comboBox->itemData(ui->comboBox->currentIndex()).value<QList<QVariant>>();
    if(!face_name.isEmpty()){
        hole->start(face_name.first().toString());
    }
}

