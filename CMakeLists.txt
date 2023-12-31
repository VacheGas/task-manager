cmake_minimum_required(VERSION 3.26)
project(Task-Manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(RESOURCES_PATH ${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/includes)

add_executable(task-manager
        main.cpp
        src/widget.cpp
        includes/widget.h
        src/datamodel.cpp
        includes/datamodel.h
        includes/task.h
        src/delegate.cpp
        includes/delegate.h
        includes/task_element_arrangement.h
        src/headers.cpp
        includes/headers.h
)
target_compile_definitions(task-manager PRIVATE RESOURCES_PATH="${RESOURCES_PATH}")
target_link_libraries(task-manager
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
