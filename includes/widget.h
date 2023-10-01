//
// Created by Vache Gasparyan on 22.09.23.
//

#ifndef TODO_LIST_INCLUDES_WIDGET_H
#define TODO_LIST_INCLUDES_WIDGET_H


#include <QWidget>
#include <QSortFilterProxyModel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QTableView>
#include <QDateEdit>
#include <QStackedWidget>

#include "delegate.h"
#include "datamodel.h"

namespace task_manager {

    class Widget : public QWidget {
    Q_OBJECT

    private:
        QTableView *_table{};
        QLineEdit *_newName{};
        QLineEdit *_newDescription{};
        QDateEdit *_newDate{};
        QPushButton *_btnAdd{};
        QPushButton *_btnDel{};
        QPushButton *_saveTasks{};
        QPushButton *_resetButton{};
        QComboBox *_filterColumn{};
        QCheckBox *_isCaseSensitive{};
        QLineEdit *_filterPattern{};
        QComboBox *_filterState{};
        QDateEdit *_filterDate{};
        QStackedWidget *_filterLineStack{};
        DataModel *_model{};
        QSortFilterProxyModel *_proxyModel{};
        delegate *_del{};


    public:
        explicit Widget(QWidget *parent = nullptr);

    private:
        void allocateComponents();

        void configureComponents();

        void arrangeLayout();

    public slots:

        void insertValueFromLineEdit();

        void removeRow();

        void patternFilterChanged();

        void resetFilter();

        void saveTasks();

        void handleFilterPatternType();

    };

}
#endif //TODO_LIST_INCLUDES_WIDGET_H
