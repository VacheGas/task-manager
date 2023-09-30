//
// Created by Vache Gasparyan on 28.09.23.
//

#ifndef TODO_LIST_INCLUDES_FILTERMODEL_H
#define TODO_LIST_INCLUDES_FILTERMODEL_H
#include <QSortFilterProxyModel>
#include <QObject>
#include <QDateEdit>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MySortFilterProxyModel(QObject *parent = nullptr);

    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(QDate date);

    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(QDate date);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool dateInRange(QDate date) const;

    QDate minDate;
    QDate maxDate;
};

#endif //TODO_LIST_INCLUDES_FILTERMODEL_H
