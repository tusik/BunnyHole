#include "transferdialog.h"
#include "ui_transferdialog.h"

TransferDialog::TransferDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferDialog)
{
    setWindowFlags(Qt::FramelessWindowHint );
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    if(!is_recive){
        ui->change_path_btn->hide();
        ui->save_path_label->hide();
    }
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("File name")<<QStringLiteral("Size"));
}

TransferDialog::~TransferDialog()
{
    delete ui;
}

bool TransferDialog::set_model(QStandardItemModel *m)
{
    ui->treeView->setModel(m);
    return true;
}

bool TransferDialog::model_from_dir(bunny::Dir &dir)
{
    dir.set_to_model(model);
    this->set_model(model);
    ui->size_label->setText(QString::number(dir.total_size/1024.0/1024.0)+" MB");
    return true;
}

void TransferDialog::on_buttonBox_accepted()
{

}

