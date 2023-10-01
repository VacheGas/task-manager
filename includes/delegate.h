//
// Created by Vache Gasparyan on 24.09.23.
//

#ifndef TODO_LIST_INCLUDES_DELEGATE_H
#define TODO_LIST_INCLUDES_DELEGATE_H

#include <QStyledItemDelegate>

namespace task_manager {
    /**
     * @brief The delegate class provides custom rendering and editing of items in views.
     *
     * This class inherits QStyledItemDelegate and provides custom editors for items in the view.
     */
    class delegate : public QStyledItemDelegate {
        Q_OBJECT
    public:
        /**
         * @brief Constructor for the delegate class.
         * @param parent The parent QObject.
         */
        explicit delegate(QObject *parent = nullptr);

        /**
         * @brief Creates an editor for the item specified by the given index.
         * @param parent The parent widget of the editor.
         * @param option Style options for the item view.
         * @param index The model index of the item.
         * @return A pointer to the created editor widget.
         */
        QWidget *
        createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

        /**
         * @brief Sets the data to be displayed and edited by the editor from the model.
         * @param editor The editor widget.
         * @param index The model index of the item.
         */
        void setEditorData(QWidget *editor, const QModelIndex &index) const override;

        /**
         * @brief Sets the data from the editor back into the model.
         * @param editor The editor widget.
         * @param model The model containing the item.
         * @param index The model index of the item.
         */
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    };

}
#endif //TODO_LIST_INCLUDES_DELEGATE_H
