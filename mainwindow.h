#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "delegate.h"

#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_triggered();
    void simpan();
    void takjadi();
    void batal();

    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase tabel;
    QSqlTableModel *model;
    Delegate *delegasi;
};

#endif // MAINWINDOW_H
