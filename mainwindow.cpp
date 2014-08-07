#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymodel.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QtDebug>

QSqlTableModel *model;
MyModel *timer_model;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
        db.setHostName("localhost");
        db.setDatabaseName("test");
        db.setUserName("root");
        //db.setPassword("");
        bool ok = db.open();

    qDebug() << "hey" << ok;

    model = new QSqlTableModel(0, db);
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("name"));
    model->setHeaderData(1, Qt::Horizontal, tr("skill"));

    timer_model = new MyModel(parent);

    //ui->tableView->setModel(model);
    ui->processes->setModel(timer_model);

    ui->processes->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSomething_triggered(){
    model->select();
}

void MainWindow::on_actionGetProcesses_triggered(){

}
