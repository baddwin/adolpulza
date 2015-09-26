#ifndef DELEGATE_H
#define DELEGATE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class Delegate;
}

class Delegate : public QDialog
{
    Q_OBJECT

public:
    explicit Delegate(QWidget *parent = 0);
    ~Delegate();
    void petakan(QSqlTableModel *model);
    void setIndeks(int baris);

signals:
    void deleteRow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Delegate *ui;
    QDataWidgetMapper *mapper;
};

#endif // DELEGATE_H
