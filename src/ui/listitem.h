﻿#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include "model/clientmodel.h"
namespace Ui {
class ListItem;
}

class ListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListItem(ClientModel m,QWidget *parent = nullptr);
    ~ListItem();
    bool set_model(ClientModel& m);
    int title_height = 60;
    int height = 200;
    bool update();
signals:
    void size_changed(int value);
private slots:
    void slotShowWidget();
    void on_pushButton_clicked();

private:
    Ui::ListItem *ui;
    bool _showFlg = false;
    ClientModel model;
};

#endif // LISTITEM_H
