//
// Created by Vache Gasparyan on 24.09.23.
//
#include <QDateEdit>
#include <QComboBox>

#include <delegate.h>
#include <task_element_arrangement.h>

namespace task_manager {

    delegate::delegate(QObject *parent)
            : QStyledItemDelegate(parent) {
    }

    QWidget *
    delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        switch (static_cast<TaskElementArrangement>(index.column())) {
            case TaskElementArrangement::DATE: {
                QDateEdit *dateEdit = new QDateEdit(parent);
                return dateEdit;
            }
            case TaskElementArrangement::STATE: {
                QComboBox *stateEdit = new QComboBox(parent);
                stateEdit->addItem(QString("In Progress"));
                stateEdit->addItem(QString("Completed"));
                stateEdit->setEditable(true);
                return  stateEdit;
            }
            default:
                return QStyledItemDelegate::createEditor(parent, option, index);
        }
    }

    void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
        switch (static_cast<TaskElementArrangement>(index.column())) {
            case TaskElementArrangement::DATE: {
                QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
                QDate value = index.model()->data(index).toDate();
                dateEdit->setDate(value);
                return;
            }
            case TaskElementArrangement::STATE: {
                QComboBox *comboState = static_cast<QComboBox*>(editor);
                bool stateData = index.model()->data(index) == "Completed";
                comboState->setCurrentIndex(stateData);
                return;
            }
            default:
                QStyledItemDelegate::setEditorData(editor, index);
        }
    }

    void delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
        switch (static_cast<TaskElementArrangement>(index.column())) {
            case TaskElementArrangement::DATE: {
                QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
                model->setData(index, dateEdit->date());
                return;
            }
            case TaskElementArrangement::STATE: {
                QComboBox *comboState = static_cast<QComboBox*>(editor);
                bool stateData = comboState->currentText() == QString("Completed");

                model->setData(index, QVariant(stateData));
                return;
            }
            default:
                QStyledItemDelegate::setModelData(editor, model, index);
        }
    }

}
