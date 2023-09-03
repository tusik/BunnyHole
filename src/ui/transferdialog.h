#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

#include "../kernel/file/bunnydir.h"

namespace Ui {
class TransferDialog;
}

class TransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransferDialog(QWidget *parent = nullptr);
    ~TransferDialog();
    bool set_model(QStandardItemModel* m);
    bool model_from_dir(bunny::Dir& dir);
    bool set_source(QString ip);
    bool is_recive = false;
signals:
    void accpted();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::TransferDialog *ui;
    QStandardItemModel* model;
};

#endif // TRANSFERDIALOG_H
