//
// Created by Vache Gasparyan on 24.09.23.
//

#ifndef TODO_LIST_INCLUDES_DELEGATE_H
#define TODO_LIST_INCLUDES_DELEGATE_H

#include <QStyledItemDelegate>

class delegate : public QStyledItemDelegate {
Q_OBJECT

public:
    explicit delegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};


#endif //TODO_LIST_INCLUDES_DELEGATE_H
