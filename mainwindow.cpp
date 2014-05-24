#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabel = QSqlDatabase::addDatabase("QSQLITE");
    QString tabelFile = "/home/bedouin/Apps/projects/qt-latihan/AdolPulza/adolpulza.sqlite";
    tabel.setDatabaseName(tabelFile);

    QFileInfo infoTabel(tabelFile);
    if(infoTabel.isFile())
    {
        if(tabel.open())
        {
            //qDebug() << "Database siap gan...";

        }else{
            //qDebug() << "Ada kesalahan";
        }
    }

    QSqlTableModel *model = new QSqlTableModel(ui->tableView);

    model->setTable("laporan");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,tr("No"));
    model->setHeaderData(1,Qt::Horizontal,tr("Tanggal"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nomer"));
    model->setHeaderData(3,Qt::Horizontal,tr("Biaya"));
    model->setHeaderData(4,Qt::Horizontal,tr("Keterangan"));
    model->select();
    ui->tableView->setModel(model);

    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,200);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
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
    QMessageBox *about = new QMessageBox(this);
    about->setWindowTitle("Tentang Program");
    about->setText("Adol Pulza\n2014 Slamet Badwi");
    about->setIcon(QMessageBox::Information);
    about->exec();
}
