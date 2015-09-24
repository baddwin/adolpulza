#ifndef DELEGATE_H
#define DELEGATE_H

#include <QDialog>

namespace Ui {
class Delegate;
}

class Delegate : public QDialog
{
    Q_OBJECT

public:
    explicit Delegate(QWidget *parent = 0);
    ~Delegate();

private:
    Ui::Delegate *ui;
};

#endif // DELEGATE_H
