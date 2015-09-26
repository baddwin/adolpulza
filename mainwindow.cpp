#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabel = QSqlDatabase::addDatabase("QSQLITE");

    //QSettings tatanan(QSettings::IniFormat, QSettings::UserScope, "Baddwin", "AdolPulza");
    delegasi = new Delegate(parent);
    connect(delegasi,SIGNAL(deleteRow()),this,SLOT(batal()));

#ifdef Q_OS_WIN
    QString tabelFile = "adolpulza.sqlite";
#else
    QString tabelFile = "adolpulza.sqlite";
#endif

    QFileInfo infoTabel(tabelFile);
    if(infoTabel.exists()) {
        if(infoTabel.isFile()) {
            tabel.setDatabaseName(tabelFile);
            if(!tabel.open())
            {
                ui->statusBar->showMessage(tabel.lastError().text());
                //return 0;
            } else {
                ui->statusBar->showMessage("Database berhasil dibuka",3000);
            }
            //qDebug() << "Database siap gan...";

        }
    } else {
        //qDebug() << "Ada kesalahan";
        ui->statusBar->showMessage("File tidak ditemukan");
        return;
    }

    model = new QSqlTableModel(parent,tabel);
    model->setTable("laporan");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    //model->database().transaction();
    ui->tableView->setModel(model);

    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,200);
    //ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView->show();

    delegasi->petakan(model);

    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(simpan()));
    connect(ui->actionReset,SIGNAL(triggered()),this,SLOT(takjadi()));
}

MainWindow::~MainWindow()
{
    delete delegasi;
    tabel.close();
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"Tentang Program","Adol Pulza\n2015 Slamet Badwi");
}

void MainWindow::simpan()
{
    if(model->submitAll())
    {
        ui->statusBar->showMessage("Berhasil disimpan",10000);
    }
    else
    {
        ui->statusBar->showMessage("Tidak bisa menyimpan: "+tabel.lastError().text(),5000);
    }
}

void MainWindow::takjadi()
{
    model->revertAll();
    ui->statusBar->showMessage("Tabel dikembalikan pada kondisi awal",5000);
}

void MainWindow::on_actionAdd_triggered()
{
    //qDebug() << model->rowCount();
    model->insertRow(model->rowCount());
    model->setData(model->index(model->rowCount()+1,0),model->rowCount()+1);
    ui->tableView->selectRow(model->rowCount());
    delegasi->setIndeks(model->rowCount());
    delegasi->exec();
}

void MainWindow::on_actionDelete_triggered()
{
    qDebug() << "deleted" << ui->tableView->currentIndex().row();
    model->removeRow(ui->tableView->currentIndex().row());
}

void MainWindow::on_actionEdit_triggered()
{
    //delegasi->exec();
    ui->tableView->update();
}

void MainWindow::batal()
{
//    qDebug() << model->rowCount();
    model->removeRow(model->rowCount()-1);
}
