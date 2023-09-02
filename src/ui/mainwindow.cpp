#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QStandardItem>
#include <QSslCertificate>
#include "listitem.h"
#include "transferdialog.h"
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
    connect(hole, &BunnyHole::new_transfer_request, this, &MainWindow::recive_transfer_request);
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
        c.ip = "127.0.0.1";
        c.hostname = "AAAA";
        c.port = 22333;
        ListItem* item = new ListItem(c);

        item->title_height = 60;
        QListWidgetItem * pItem = new QListWidgetItem();
        pItem->setSizeHint({160,0});
        ui->listWidget->addItem(pItem);
        ui->listWidget->setItemWidget(pItem,item);
        connect(item, &ListItem::size_changed, [pItem](int h){
            pItem->setSizeHint(QSize(pItem->sizeHint().width(), h));
        });
        connect(item, &ListItem::request_transfer, this,&MainWindow::send_transfer_request);
        // FOR TEST ONLY
        //connect(item, &ListItem::request_transfer, this,&MainWindow::recive_transfer_request);
    }
    TransferDialog* dia = new TransferDialog();
    dia->show();
    QStandardItemModel* model = new QStandardItemModel(dia);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Size")<<QStringLiteral("File name"));
    QStandardItem* itemProject = new QStandardItem(QIcon(),QStringLiteral("项目"));
    model->appendRow(itemProject);
    dia->set_model(model);

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
    pItem->setSizeHint({ 300,0 });
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
        ListItem* widget = dynamic_cast<ListItem*>( ui->listWidget->itemWidget(i) );
        widget->offline_animation();
        connect(widget,&ListItem::offline_ok,this,[this,protoc](){
            auto rlist = ui->listWidget->findItems(protoc.host, Qt::MatchExactly);
            for (auto& i : rlist) {
                delete i;

            }
        });

    }
    //qDeleteAll(ui->listWidget->findItems(protoc.host, Qt::MatchFixedString));
}

void MainWindow::send_transfer_request(Carrot c)
{
    ListItem* item = static_cast<ListItem*>(sender());
    auto model = item->get_model();
    auto itr = bunnys.find(model);
    BunnyChild* child;
    if(itr != bunnys.end()){
        child = itr.value();
    }else{
        // new bunny;
        child = new BunnyChild();
        qDebug()<<"ws://"+model.ip+":"+QString::number(model.port);
        child->connect_mom(QUrl("ws://"+model.ip+":"+QString::number(model.port)));
        bunnys.insert(model,child);
    }
    child->send_transfer_request(c);
}

void MainWindow::recive_transfer_request(Carrot c)
{
    TransferDialog* dia = new TransferDialog();
    dia->model_from_dir(c.leaf.dir);
    int rec = dia->exec();
    if(rec == QDialog::Accepted){
        qDebug()<<dia->isFullScreen();
        send_accpet_transfer_request("ss");
    }
}

void MainWindow::send_accpet_transfer_request(QString host)
{
    Carrot c;
    c.leaf.type = CarrotOperatorCBorType::AcceptFileTransfer;
    c.leaf.from_host = "";
    c.leaf.to_host = host;
    hole->bunny.send_message(c);
}


void MainWindow::on_connect_btn_clicked()
{
    auto face_name = ui->comboBox->itemData(ui->comboBox->currentIndex()).value<QList<QVariant>>();
    if(!face_name.isEmpty()){
        hole->start(face_name.first().toString());
    }
}

