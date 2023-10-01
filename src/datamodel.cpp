//
// Created by Vache Gasparyan on 22.09.23.
//

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "../includes/datamodel.h"
#include "../includes/task_element_arrangement.h"

namespace task_manager {

    DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent) {
        loadData();
    }

    int DataModel::columnCount(const QModelIndex &) const {
        return static_cast<int>(RowsCount::COUNT);
    }

    int DataModel::rowCount(const QModelIndex &) const {
        return static_cast<int>(_data.size());
    }

    QVariant DataModel::data(const QModelIndex &index, int role) const {
        if (role != Qt::DisplayRole) return QVariant();
        switch (static_cast<TaskElementArrangement>(index.column())) {
            case TaskElementArrangement::NAME:
                return QVariant(_data[index.row()].name);
            case TaskElementArrangement::DESCRIPTION:
                return QVariant(_data[index.row()].description);
            case TaskElementArrangement::DATE:
                return QVariant(_data[index.row()].date);
            case TaskElementArrangement::STATE:
                return QVariant((_data[index.row()].state ? "Completed" : "In Progress"));
            default:
                return QVariant();
        }
    }

    QModelIndex DataModel::index(int row, int column, const QModelIndex &) const {
        switch (static_cast<TaskElementArrangement>(column)) {
            case TaskElementArrangement::NAME:
                return createIndex(row, column, (void *) &_data[row].name);
            case TaskElementArrangement::DESCRIPTION:
                return createIndex(row, column, (void *) &_data[row].description);
            case TaskElementArrangement::DATE:
                return createIndex(row, column, (void *) &_data[row].date);
            case TaskElementArrangement::STATE:
                return createIndex(row, column, (void *) &_data[row].state);
        }
        return createIndex(row, column, nullptr);
    }

    QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (static_cast<TaskElementArrangement>(section)) {
                case TaskElementArrangement::NAME:
                    return "Name";
                case TaskElementArrangement::DESCRIPTION:
                    return "Description";
                case TaskElementArrangement::DATE:
                    return "Date";
                case TaskElementArrangement::STATE:
                    return "State";
                default:
                    return QVariant();
            }
        }
        return QVariant();
    }

    Qt::ItemFlags DataModel::flags(const QModelIndex &index) const {
        Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        return QAbstractTableModel::flags(index) | flags;
    }

    bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        if (role != Qt::EditRole) {
            return true;
        }
        switch (static_cast<TaskElementArrangement>(index.column())) {
            case TaskElementArrangement::NAME:
                if (_data[index.row()].name != value.toString()) {
                    _data[index.row()].name = value.toString();
                    break;
                }
            case TaskElementArrangement::DESCRIPTION:
                if (_data[index.row()].description != value.toString()) {
                    _data[index.row()].description = value.toString();
                    break;
                }
            case TaskElementArrangement::DATE:
                if (_data[index.row()].date != value.toDate()) {
                    _data[index.row()].date = value.toDate();
                    break;
                }
            case TaskElementArrangement::STATE:
                if (_data[index.row()].state != value.toBool()) {
                    _data[index.row()].state = value.toBool();
                    break;
                }
            default:
                return false;
        }
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    void DataModel::addValue(const QString &name, const QString &description, const QDate &date, const bool &state) {
        beginInsertRows(QModelIndex(), static_cast<int>(_data.size()), static_cast<int>(_data.size()));
        _data.push_back({name, description, date, state});
        endInsertRows();
    }


    bool DataModel::removeRows(int position, int rows, const QModelIndex &index) {
        Q_UNUSED(index);
        Q_UNUSED(rows);
        beginRemoveRows(QModelIndex(), position, position);
        for (int row = 0; row <= position; ++row) {
            _data.removeAt(row);
        }
        endRemoveRows();
        return true;
    }

    void DataModel::loadData() {
        QList<task> tasks;
        QFile file(RESOURCES_PATH "/tasks.json");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray jsonData = file.readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonArray taskArray = jsonDoc.array();

            for (const QJsonValue &taskValue: taskArray) {
                QJsonObject taskObject = taskValue.toObject();
                addValue(taskObject["Name"].toString(), taskObject["Description"].toString(),
                         taskObject["Date"].toVariant().toDate(), taskObject["State"].toBool());
            }
            file.close();
        }
    }

    void DataModel::saveData() {
        QFile file(RESOURCES_PATH "/tasks.json");

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QJsonArray taskArray;
            for (const task &task: _data) {
                QJsonObject taskObject;
                taskObject["Name"] = task.name;
                taskObject["Description"] = task.description;
                taskObject["Date"] = task.date.toString(Qt::ISODate);
                taskObject["State"] = task.state;
                taskArray.append(taskObject);
            }
            QJsonDocument jsonDoc(taskArray);
            file.write(jsonDoc.toJson());
            file.close();
        }
    }

}