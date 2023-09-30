//
// Created by Vache Gasparyan on 22.09.23.
//

#ifndef TODO_LIST_INCLUDES_DATAMODEL_H
#define TODO_LIST_INCLUDES_DATAMODEL_H

#include <QObject>
#include <QAbstractItemModel>

#include <vector>

#include "Task.h"

class DataModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    QList<Task> _data;
    enum class ROWS_COUNT {
        COUNT = 4
    };

public:
    explicit DataModel(QObject *parent);

public:
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeRows(int position, int rows, const QModelIndex &index) override;
    void loadData();
    void saveData();

public slots:
    void addValue(const QString &name, const QString &description, const QDate &date, const bool &state);

};



#endif //TODO_LIST_INCLUDES_DATAMODEL_H
