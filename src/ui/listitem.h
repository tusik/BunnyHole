#ifndef LISTITEM_H
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
    int height = 120;
    bool update();

    void online_animation();
    void offline_animation();
signals:
    void size_changed(int value);
    void offline_ok();
private slots:
    void slotShowWidget();
    void on_pushButton_clicked();
private:

    Ui::ListItem *ui;
    bool _showFlg = false;
    ClientModel model;
};

#endif // LISTITEM_H
