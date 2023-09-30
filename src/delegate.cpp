//
// Created by Vache Gasparyan on 24.09.23.
//

#include "../includes/delegate.h"
#include <QDateEdit>

delegate::delegate(QObject *parent)
        : QStyledItemDelegate(parent)
{
}

QWidget *delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 2) {
            QDateEdit* dateEdit = new QDateEdit(parent);
            return dateEdit;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if (index.column() == 2) {
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
    if (index.column() == 2) {
        QDateEdit* dateEdit = static_cast<QDateEdit*>(editor);
        model->setData(index, dateEdit->date());
        return;
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}