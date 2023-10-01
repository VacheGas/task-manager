//
// Created by Vache Gasparyan on 24.09.23.
//
#include <QDateEdit>

#include "../includes/delegate.h"
#include "../includes/task_element_arrangement.h"

delegate::delegate(QObject *parent)
        : QStyledItemDelegate(parent) {
}

QWidget *delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (static_cast<TaskElementArrangement>(index.column()) == TaskElementArrangement::DATE) {
            QDateEdit* dateEdit = new QDateEdit(parent);
            return dateEdit;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if (static_cast<TaskElementArrangement>(index.column()) == TaskElementArrangement::DATE) {
            QDateEdit* dateEdit = static_cast<QDateEdit*>(editor);
            if (dateEdit) {
                QDate value = index.model()->data(index, Qt::EditRole).toDate();
                dateEdit->setDate(value);
            }
            return;
    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void delegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
    if (static_cast<TaskElementArrangement>(index.column()) == TaskElementArrangement::DATE) {
        QDateEdit* dateEdit = static_cast<QDateEdit*>(editor);
        model->setData(index, dateEdit->date());
        return;
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}