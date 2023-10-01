//
// Created by Vache Gasparyan on 23.09.23.
//

#ifndef TODO_LIST_INCLUDES_TASK_H
#define TODO_LIST_INCLUDES_TASK_H

#include <QDate>
namespace task_manager {
/**
 * @brief The task struct represents a task with a name, description, date, and completion state.
 */
    struct task {
        QString name; /**< The name of the task. */
        QString description; /**< The description of the task. */
        QDate date; /**< The date of the task. */
        bool state; /**< The completion state of the task. */

        /**
         * @brief Default constructor for the task struct.
         */
        task() = default;

        /**
         * @brief Constructor for the task struct.
         * @param newName The name of the task.
         * @param newDescription The description of the task.
         * @param newDate The date of the task.
         * @param newState The completion state of the task.
         */
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
