#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(QObject*);


    QVariant data(const QModelIndex&, int ) const;
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


public slots:
    void timerHit();

};

#endif // MYMODEL_H
