//
// Created by Vache Gasparyan on 22.09.23.
//
#include <QLabel>

#include <headers.h>
#include <widget.h>

namespace task_manager {

    Widget::Widget(QWidget *parent)
            : QWidget(parent) {
        allocateComponents();
        configureComponents();
        arrangeLayout();
        setupConnections();

        setFixedSize(490, 400);
    }

    void Widget::allocateComponents() {
        _model = new DataModel(this);
        _table = new QTableView(this);
        _proxyModel = new QSortFilterProxyModel(this);
        _del = new delegate(this);
        _newName = new QLineEdit("", this);
        _newDescription = new QLineEdit("", this);
        _newDate = new QDateEdit(QDate(), this);
        _btnAdd = new QPushButton("Add value", this);
        _btnDel = new QPushButton("Delete value", this);
        _saveTasks = new QPushButton("save", this);
        _resetButton = new QPushButton("Reset", this);
        _filterColumn = new QComboBox(this);
        isCaseInsensitive = new QCheckBox("Case Insensitive", this);
        _filterNameDesc = new QLineEdit("", this);
        _filterDate = new QDateEdit(QDate(), this);
        _filterState = new QComboBox(this);
        _filterLineStack = new QStackedWidget;

    }

    void Widget::configureComponents() {
        _btnAdd->setEnabled(false);
        _proxyModel->setSourceModel(_model);
        _table->setModel(_proxyModel);
        _table->setItemDelegate(_del);

        _newName->setPlaceholderText(QString(header(TaskElementArrangement::NAME)));
        _newDescription->setPlaceholderText(QString(header(TaskElementArrangement::DESCRIPTION)));
        _filterNameDesc->setPlaceholderText(QString("Filter Pattern"));

        _filterColumn->addItem(header(TaskElementArrangement::NAME));
        _filterColumn->addItem(header(TaskElementArrangement::DESCRIPTION));
        _filterColumn->addItem(header(TaskElementArrangement::DATE));
        _filterColumn->addItem(header(TaskElementArrangement::STATE));
        _filterColumn->setItemData(static_cast<int>(TaskElementArrangement::NAME), header(TaskElementArrangement::NAME), Qt::UserRole);
        _filterColumn->setItemData(static_cast<int>(TaskElementArrangement::DESCRIPTION), header(TaskElementArrangement::DESCRIPTION), Qt::UserRole);
        _filterColumn->setItemData(static_cast<int>(TaskElementArrangement::DATE), header(TaskElementArrangement::DATE), Qt::UserRole);
        _filterColumn->setItemData(static_cast<int>(TaskElementArrangement::STATE), header(TaskElementArrangement::STATE), Qt::UserRole);

        _filterState->addItem("Completed");
        _filterState->addItem("In Progress");
    }

    void Widget::arrangeLayout() {
        QHBoxLayout *filterSettingsLayout = new QHBoxLayout;
        filterSettingsLayout->addWidget(_filterColumn);
        filterSettingsLayout->addWidget(isCaseInsensitive);
        filterSettingsLayout->setSpacing(8);

        QHBoxLayout *filterSecondLay = new QHBoxLayout;
        _filterLineStack->addWidget(_filterNameDesc);
        _filterLineStack->addWidget(_filterDate);
        _filterLineStack->addWidget(_filterState);
        filterSecondLay->addWidget(_filterLineStack);
        filterSecondLay->addWidget(_resetButton);
        filterSecondLay->setSpacing(5);

        QHBoxLayout *taskDetail = new QHBoxLayout;
        taskDetail->addWidget(_newName);
        taskDetail->addWidget(_newDescription);
        taskDetail->addWidget(_newDate);
        taskDetail->setSpacing(3);

        QHBoxLayout *controlPanel = new QHBoxLayout;
        controlPanel->addWidget(_btnAdd);
        controlPanel->addWidget(_btnDel);
        controlPanel->addWidget(_saveTasks);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addItem(filterSettingsLayout);
        mainLayout->addItem(filterSecondLay);
        mainLayout->addWidget(_table);

        QLabel *label = new QLabel("Add new Task");
        mainLayout->addWidget(label);

        mainLayout->addItem(taskDetail);
        mainLayout->addItem(controlPanel);
        setLayout(mainLayout);
    }

    void Widget::setupConnections() {
        connect(_filterColumn, &QComboBox::activated, this, &Widget::handleFilterPatternType);
        connect(_btnAdd, &QPushButton::clicked, this, &Widget::insertTask);
        connect(_btnDel, &QPushButton::clicked, this, &Widget::removeRow);
        connect(_resetButton, &QPushButton::clicked, this, &Widget::resetFilter);
        connect(_filterNameDesc, &QLineEdit::textChanged, this, &Widget::patternFilterChanged);
        connect(_filterDate, &QDateEdit::dateChanged, this, &Widget::patternFilterChanged);
        connect(_filterState, &QComboBox::activated, this, &Widget::patternFilterChanged);
        connect(_saveTasks, &QPushButton::clicked, this, &Widget::saveTasks);
        connect(_newName, &QLineEdit::textChanged, this, &Widget::enableAddButton);
        connect(_newDescription, &QLineEdit::textChanged, this, &Widget::enableAddButton);
    }

    void Widget::insertTask() {
        _model->addValue(_newName->text(), _newDescription->text(), _newDate->date(), 0);
    }

    void Widget::removeRow() {
        const QModelIndexList indexes = _table->selectionModel()->selectedIndexes();
        for (auto index: indexes) {
            int row = _proxyModel->mapToSource(index).row();
            _model->removeRows(row, 1, QModelIndex());
        }
    }

    void Widget::resetFilter() {
        _proxyModel->setFilterRegularExpression("");
    }

    void Widget::patternFilterChanged() {
        QWidget *currentWidget = _filterLineStack->currentWidget();
        QString pattern;
        switch (static_cast<TaskElementArrangement>(_filterColumn->currentIndex())) {
            case TaskElementArrangement::NAME ... TaskElementArrangement::DESCRIPTION :
                pattern = QRegularExpression::escape(qobject_cast<QLineEdit *>(currentWidget)->text());
                break;
            case TaskElementArrangement::DATE :
                pattern = QRegularExpression::escape(
                        qobject_cast<QDateEdit *>(currentWidget)->date().toString(Qt::ISODate));
                break;
            case TaskElementArrangement::STATE :
                pattern = QRegularExpression::escape(qobject_cast<QComboBox *>(currentWidget)->currentText());
        }
        _proxyModel->setFilterKeyColumn(_filterColumn->currentIndex());
        QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption;
        if (isCaseInsensitive->isChecked()) {
            options |= QRegularExpression::CaseInsensitiveOption;
        }
        QRegularExpression regularExpression(pattern, options);

        _proxyModel->setFilterRegularExpression(regularExpression);
    }

    void Widget::saveTasks() {
        _model->saveData();
    }

    void Widget::handleFilterPatternType() {
        switch (static_cast<TaskElementArrangement>(_filterColumn->currentIndex())) {
            case TaskElementArrangement::NAME ... TaskElementArrangement::DESCRIPTION :
                _filterLineStack->setCurrentIndex(0);
                break;
            case TaskElementArrangement::DATE :
                _filterLineStack->setCurrentIndex(1);
                break;
            case TaskElementArrangement::STATE :
                _filterLineStack->setCurrentIndex(2);
                break;
        }
    }

    void Widget::enableAddButton() {
        _btnAdd->setEnabled(!_newName->text().isEmpty() && !_newDescription->text().isEmpty());
    }
};
