cmake_minimum_required(VERSION 3.26)
project(TODO-list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(untitled1 main.cpp)
target_link_libraries(untitled1
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
