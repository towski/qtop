#include "mymodel.h"
#include <QVariant>
#include <QAbstractTableModel>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QProcess>

QTimer *timer;
QProcess *myProcess;
QByteArray strdata;
QStringList lines;
QList<QStringList> row_lines;
QStringList headers;

MyModel::MyModel(QObject *parent):QAbstractTableModel(parent){
//    selectedCell = 0;
    headers << "PID" << "USER" << "PR" << "NI" << "VIRT" << "RES" << "SHR" << "S" << "%CPU" << "%MEM" << "TIME+" << "COMMAND";
row_lines.reserve(21);
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()) , this, SLOT(timerHit()));
    timer->start();
}


void MyModel::timerHit()
{
    qDebug() << "ag";
    myProcess = new QProcess();

    QStringList list;
    list << "-c" << "top -bn1 | tail -n+8";

    myProcess->start(QString("/bin/sh"), list, QProcess::ReadWrite);

    myProcess->waitForReadyRead();

    strdata = myProcess->readAllStandardOutput();

    lines = QString(strdata).split("\n");

    //we identify the top left cell
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(lines.length(),0);

    //emit a signal to make the view reread identified data
    emit dataChanged(topLeft, bottomRight);
}

int MyModel::rowCount(const QModelIndex &parent = QModelIndex()) const {
    return 20;
}

int MyModel::columnCount(const QModelIndex &parent = QModelIndex()) const {
    return headers.length();
}

QVariant MyModel::data(const QModelIndex &index, int role) const{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole){
        if(lines.isEmpty()){
            return "last";
        }
       if(col == 0 && row == 0){
           row_lines.clear();
       }
       if (col == 0){
           row_lines << lines[row].trimmed().split(QRegExp("\\s+"));
       }
       if(myProcess){
           return row_lines[row][col];
       }
       //return QTime::currentTime().toString();
       return "last";

    }
    if (role == Qt::SizeHintRole){
        return 500;
    }
    return QVariant();
}


QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return headers[section];
   }
   return QVariant();
}
