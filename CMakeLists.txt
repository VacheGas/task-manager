cmake_minimum_required(VERSION 3.26)
project(TODO-list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(RESOURCES_PATH ${CMAKE_SOURCE_DIR})

add_executable(todo-list
        main.cpp
        src/widget.cpp
        includes/widget.h
        src/datamodel.cpp
        includes/datamodel.h
        includes/task.h
        src/delegate.cpp
        includes/delegate.h
)
target_compile_definitions(todo-list PRIVATE RESOURCES_PATH="${RESOURCES_PATH}")
target_link_libraries(todo-list
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

