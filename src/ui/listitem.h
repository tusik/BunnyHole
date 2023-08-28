#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include "model/clientmodel.h"

#include "../kernel/file/bunnydir.h"
#include "../kernel/carrot.h"
#include <QFileDialog>
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
    int height = 120;
    bool update();

    void online_animation();
    void offline_animation();
    ClientModel get_model();
signals:
    void size_changed(int value);
    void offline_ok();
    void request_transfer(Carrot c);
private slots:
    void slotShowWidget();
    void on_pushButton_clicked();
    void on_transfer_btn_clicked();

private:
    Ui::ListItem *ui;
    bool _showFlg = false;
    ClientModel model;
};

#endif // LISTITEM_H
