//
// Created by Vache Gasparyan on 22.09.23.
//

#ifndef TODO_LIST_INCLUDES_DATAMODEL_H
#define TODO_LIST_INCLUDES_DATAMODEL_H

#include <QObject>
#include <QAbstractItemModel>

#include "task.h"

namespace task_manager {
    /**
     * @brief The DataModel class represents a custom data model for task management.
     *
     * This class inherits QAbstractTableModel and provides methods to manage tasks.
     */
    class DataModel : public QAbstractTableModel {
    Q_OBJECT

    private:
        QList<task> _data; /**< List to store task objects. */
        enum class RowsCount {
            COUNT = 4
        };

    public:
        /**
         * @brief Constructor for the DataModel class.
         * @param parent The parent QObject.
         */
        explicit DataModel(QObject *parent);

    public:
        // Overridden methods from QAbstractTableModel
        int columnCount(const QModelIndex &parent) const override;

        int rowCount(const QModelIndex &parent) const override;

        QVariant data(const QModelIndex &index, int role) const override;

        QModelIndex index(int row, int column, const QModelIndex &parent) const override;

        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;

        bool setData(const QModelIndex &index, const QVariant &value, int role) override;

        bool removeRows(int position, int rows, const QModelIndex &index) override;

        /**
         * @brief Loads data from a JSON file into the model.
         */
        void loadData();

        /**
         * @brief Saves the current data in the model to a JSON file.
         */
        void saveData();

        bool isEmpty();

    public slots:
        /**
         * @brief Adds a new task to the model.
         * @param name The name of the task.
         * @param description The description of the task.
         * @param date The date of the task.
         * @param state The state of the task.
         */
        void addValue(const QString &name, const QString &description, const QDate &date, const bool &state);

    };
}
#endif //TODO_LIST_INCLUDES_DATAMODEL_H
