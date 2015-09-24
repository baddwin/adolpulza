#include "delegate.h"
#include "ui_delegate.h"

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
