//
// Created by Vache Gasparyan on 23.09.23.
//

#ifndef TODO_LIST_INCLUDES_TASK_H
#define TODO_LIST_INCLUDES_TASK_H

#include <QDate>
namespace task_manager {

    struct task {
        QString name;
        QString description;
        QDate date;
        bool state{};

        task() = default;

        task(QString newName,
             QString newDescription,
             QDate newDate, bool newState)
                : name(std::move(newName)),
                  description(std::move(newDescription)),
                  date(newDate),
                  state(newState) {}
    };

}
#endif //TODO_LIST_INCLUDES_TASK_H
