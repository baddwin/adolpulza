#include "delegate.h"
#include "ui_delegate.h"
#include <QDebug>

Delegate::Delegate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delegate)
{
    ui->setupUi(this);
    ui->ruasTanggal->setDateTime(QDateTime::currentDateTime());
}

Delegate::~Delegate()
{
    delete ui;
}

void Delegate::petakan(QSqlTableModel *model)
{
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->ruasNmr, model->fieldIndex("No"));
    mapper->addMapping(ui->ruasTanggal, model->fieldIndex("Tanggal"));
    mapper->addMapping(ui->ruasNomor, model->fieldIndex("Nomor"));
    mapper->addMapping(ui->ruasBiaya, model->fieldIndex("Biaya"));
    mapper->addMapping(ui->ruasCatatan, model->fieldIndex("Catatan"));
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
//    mapper->toFirst();
}

void Delegate::on_buttonBox_accepted()
{
    //mapper->model()->insertRow(ui->ruasNmr->value());
    //mapper->setCurrentIndex(mapper->model()->rowCount());
    //qDebug() << mapper->model()->rowCount();
    mapper->submit();
}

void Delegate::on_buttonBox_rejected()
{
    //
    emit deleteRow();
}

void Delegate::setIndeks(int baris)
{
    mapper->setCurrentIndex(baris);
}
