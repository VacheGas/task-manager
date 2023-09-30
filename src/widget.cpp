//
// Created by Vache Gasparyan on 22.09.23.
//

#include "../includes/widget.h"
#include <iostream>
#include <QLabel>

Widget::Widget(QWidget *parent)
        : QWidget(parent) {
    allocateComponents();
    configureComponents();
    arrangeLayout();

    connect(_btnAdd, &QPushButton::clicked,this, &Widget::insertValueFromLineEdit);
    connect(_btnDel, &QPushButton::clicked, this, &Widget::removeRow);
    connect(_resetButton, &QPushButton::clicked, this, &Widget::resetFilter);
    connect(_filterPattern, &QLineEdit::textChanged, this, &Widget::textFilterChanged);
    connect(_saveTasks, &QPushButton::clicked, this, &Widget::saveTasks);
}

void Widget::allocateComponents() {
    _model = new DataModel(this);
    _table = new QTableView(this);
    _proxyModel = new QSortFilterProxyModel(this);
    _del = new delegate(this);
    _newName = new QLineEdit("",this);
    _newDescription = new QLineEdit("",this);
    _newDate = new QDateEdit(QDate(),this);
    _btnAdd = new QPushButton("Add value", this);
    _btnDel = new QPushButton("Delete value", this);
    _saveTasks = new QPushButton("save", this);
    _resetButton = new QPushButton("Reset", this);
    _filterColumn = new QComboBox(this);
    _filterSyntax = new QCheckBox("Regular Expression", this);
    _isCaseSensitive = new QCheckBox("Case Insensitive", this);
    _filterPattern = new QLineEdit("", this);
}

void Widget::configureComponents() {
    _proxyModel->setSourceModel(_model);
    _table->setModel(_proxyModel);
    _table->setItemDelegate(_del);

    _newName->setPlaceholderText(QString("Name"));
    _newDescription->setPlaceholderText(QString("Description"));
    _filterPattern->setPlaceholderText(QString("Filter Pattern"));

    _filterColumn->addItem("Name");
    _filterColumn->addItem("Description");
    _filterColumn->addItem("Date");
    _filterColumn->addItem("State");
}

void Widget::arrangeLayout() {
    QHBoxLayout *filterSettingsLayout = new QHBoxLayout;
    filterSettingsLayout->addWidget(_filterColumn);
    filterSettingsLayout->addWidget(_filterSyntax);
    filterSettingsLayout->addWidget(_isCaseSensitive);
    filterSettingsLayout->setSpacing(8);

    QHBoxLayout *filterSecondLay = new QHBoxLayout;
    filterSecondLay->addWidget(_filterPattern);
    filterSecondLay->addWidget(_resetButton);
    filterSecondLay->setSpacing(5);

    QHBoxLayout  *taskDetail = new QHBoxLayout;
    taskDetail->addWidget(_newName);
    taskDetail->addWidget(_newDescription);
    taskDetail->addWidget( _newDate);
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

void Widget::insertValueFromLineEdit() {
    _model->addValue(_newName->text(), _newDescription->text(), _newDate->date(), 0);
}

void Widget::removeRow() {
    const QModelIndexList indexes = _table->selectionModel()->selectedIndexes();
    for (auto index : indexes) {
        int row = _proxyModel->mapToSource(index).row();
        _model->removeRows(row, 1, QModelIndex());
    }
}

void Widget::resetFilter() {
    _proxyModel->setFilterRegularExpression("");
}

void Widget::textFilterChanged()
{
    bool isRegularExpression = _filterSyntax->isChecked();
    QString pattern;
    if (isRegularExpression) {
        std::cout << _filterPattern->text().toStdString() ;
        pattern =QRegularExpression::wildcardToRegularExpression(_filterPattern->text(), QRegularExpression::UnanchoredWildcardConversion);
    } else {
        pattern = QRegularExpression::escape(_filterPattern->text());
    }
    _proxyModel->setFilterKeyColumn(_filterColumn->currentIndex());

    QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption;
    if (_isCaseSensitive->isChecked()) {
        options |= QRegularExpression::CaseInsensitiveOption;
    }
    QRegularExpression regularExpression(pattern, options);

    _proxyModel->setFilterRegularExpression(regularExpression);
}

void Widget::saveTasks() {
    _model->saveData();
}
