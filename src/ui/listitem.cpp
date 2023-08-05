#include "listitem.h"
#include "ui_listitem.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QListWidgetItem>
ListItem::ListItem(ClientModel m,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItem),
    model(m)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
    ui->content_widget->setAttribute(Qt::WA_StyledBackground);
//    setWindowFlags( Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint );
    online_animation();
    update();
}

ListItem::~ListItem()
{
    delete ui;
}

bool ListItem::set_model(ClientModel &m)
{
    this->model = m;
    return true;
}
bool ListItem::update()
{
    ui->pushButton->setIcon(QIcon(tr(":/static/image/down-arrow.svg")));
    ui->content_widget->setObjectName("content_widget");
    ui->title_widget->setMaximumHeight(title_height);
    ui->title_widget->setMinimumHeight(title_height);
    QIcon os_icon = QIcon(tr(":/static/image/question.svg"));
    switch (model.os) {
    case ClientModel::UNKOWN:
        break;
    case ClientModel::MAC:
        os_icon = QIcon(tr(":/static/image/mac.svg"));
    case ClientModel::WIN:
        os_icon = QIcon(tr(":/static/image/windows.svg"));
        break;
    case ClientModel::LINUX:
        os_icon = QIcon(tr(":/static/image/linux.svg"));
    default:
        break;
    }
    ui->device_icon_btn->setIcon(os_icon);
    ui->host_name_label->setText(model.hostname);
    ui->ip_label->setText(model.ip);
    return true;
}
void ListItem::slotShowWidget()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutExpo);
    if(!_showFlg){
        ui->pushButton->setIcon(QIcon(tr(":/static/image/up-arrow.svg")));
        animation->setStartValue(title_height);
        animation->setEndValue(height);
        connect(animation, &QPropertyAnimation::valueChanged,this, [&](const QVariant& value){
            this->setFixedHeight(value.toInt());
            emit size_changed(value.toInt());
        });
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        _showFlg = true;
    }else {
        ui->pushButton->setIcon(QIcon(tr(":/static/image/down-arrow.svg")));
        animation->setStartValue(height);
        animation->setEndValue(title_height);
        connect(animation, &QPropertyAnimation::valueChanged,this, [&](const QVariant& value){
            this->setFixedHeight(value.toInt());
            emit size_changed(value.toInt());
        });
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        _showFlg = false;
    }
}

void ListItem::on_pushButton_clicked()
{
    slotShowWidget();
}

void ListItem::online_animation()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutExpo);
    animation->setStartValue(0);
    animation->setEndValue(title_height);
    connect(animation, &QPropertyAnimation::valueChanged,this, [&](const QVariant& value){
        this->setFixedHeight(value.toInt());
        emit size_changed(value.toInt());
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ListItem::offline_animation()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutExpo);
    animation->setStartValue(title_height);
    animation->setEndValue(0);
    connect(animation, &QPropertyAnimation::valueChanged,this, [&](const QVariant& value){
        this->setFixedHeight(value.toInt());
        emit size_changed(value.toInt());
    });
    connect(animation, &QPropertyAnimation::destroyed,this, [&](){
        emit offline_ok();
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

