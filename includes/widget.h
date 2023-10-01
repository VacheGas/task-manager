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
    /**
     * @brief The Widget class represents the main user interface for task management.
     *
     * This class inherits QWidget and provides functionality for adding, removing, and filtering tasks.
     */
    class Widget : public QWidget {
    Q_OBJECT

    private:
        QTableView *_table; /**< Table view to display tasks. */
        QLineEdit *_newName; /**< Line edit for entering new task names. */
        QLineEdit *_newDescription; /**< Line edit for entering new task descriptions. */
        QDateEdit *_newDate; /**< Date edit for entering new task dates. */
        QPushButton *_btnAdd; /**< Button to add tasks. */
        QPushButton *_btnDel; /**< Button to delete selected tasks. */
        QPushButton *_saveTasks; /**< Button to save tasks to a JSON file. */
        QPushButton *_resetButton; /**< Button to reset filters. */
        QComboBox *_filterColumn; /**< Combo box to select filter columns. */
        QCheckBox *isCaseInsensitive; /**< Check box for case-Insensitive filtering. */
        QLineEdit *_filterNameDesc; /**< Line edit for name and description filtering. */
        QComboBox *_filterState; /**< Combo box for filtering task completion states. */
        QDateEdit *_filterDate; /**< Date edit for filtering tasks by date. */
        QStackedWidget *_filterLineStack; /**< Stacked widget for filter pattern selection. */
        DataModel *_model; /**< Data model for tasks. */
        QSortFilterProxyModel *_proxyModel;  /**< Proxy model for sorting and filtering tasks. */
        delegate *_del; /**< Custom item delegate for task editing. */


    public:
       /**
        * @brief Constructor for the Widget class.
        * @param parent The parent QWidget.
        */
        explicit Widget(QWidget *parent = nullptr);

    private:
        /**
         * @brief Allocates and initializes UI components.
         */
        void allocateComponents();
        /**
         * @brief Configures the components of the widget for proper initialization.
         *
         * This function sets up various UI components, such as models, item delegates,
         * placeholders for input fields, and filter options. It prepares the widget
         * for displaying and interacting with the task data.
         */
        void configureComponents();
        /**
         * @brief Arranges the layout of the widget, organizing UI components for a clear and user-friendly interface.
         *
         * This function sets up the layout of the widget, including filter settings, task details input,
         * control buttons, and table view. It arranges components in horizontal and vertical layouts
         * to provide an organized and intuitive user interface for managing tasks.
         */
        void arrangeLayout();
        /**
         * @brief Sets up signal-slot connections for various UI components in the widget.
         *
         * This function establishes connections between different UI components and corresponding
         * slot functions, enabling interactivity in the widget. It connects filter column selection,
         * add, delete, and reset buttons, filter inputs, and save button signals to their respective functions.
         */
        void setupConnections();

    public slots:
        /**
         * @brief Slot function to insert a new task based on user input.
         *
         * This function reads data from the name, description, date, and state input fields and
         * adds a new task to the task list.
         */
        void insertTask();
        /**
         * @brief Slot function to remove selected tasks from the task list.
         */
        void removeRow();
        /**
         * @brief Slot function to handle changes in the filter pattern.
         */
        void patternFilterChanged();
        /**
         * @brief Slot function to reset applied filters.
         */
        void resetFilter();

        /**
         * @brief Slot function to save tasks to a JSON file.
         *
         * This function saves the current tasks data to a JSON file.
         * The tasks are serialized and stored in a JSON format.
         * Call this function to persistently save tasks to a file.
         */
        void saveTasks();
        /**
         * @brief Slot function to handle changes in the filter pattern type.
         */
        void handleFilterPatternType();
        /**
         * @brief Slot function to enable the add/edit button based on input validity.
         */
        void enableAddButton();

    };

}
#endif //TODO_LIST_INCLUDES_WIDGET_H
