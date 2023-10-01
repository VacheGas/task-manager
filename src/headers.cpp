//
// Created by Vache Gasparyan on 01.10.23.
//

#include <headers.h>

#include <array>
#include <QString>

namespace task_manager {
    namespace {
            std::array<QString, 4> headers = {"Name", "Description", "Date", "State"};
    };

    const QString& header(TaskElementArrangement index) {
        return headers[static_cast<int>(index)];
    }
}