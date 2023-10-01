//
// Created by Vache Gasparyan on 01.10.23.
//

#ifndef TODO_LIST_INCLUDES_TASK_ELEMENT_ARRANGEMENT_H
#define TODO_LIST_INCLUDES_TASK_ELEMENT_ARRANGEMENT_H
namespace task_manager {
   /**
     * @brief The TaskElementArrangement enum class represents the arrangement order of task elements.
     *
     * This enum class defines the possible arrangement orders for task elements such as name, description,
     * date, and state.
     */
    enum class TaskElementArrangement {
        NAME = 0,
        DESCRIPTION,
        DATE,
        STATE
    };

}
#endif //TODO_LIST_INCLUDES_TASK_ELEMENT_ARRANGEMENT_H
