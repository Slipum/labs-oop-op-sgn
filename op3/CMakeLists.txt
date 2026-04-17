cmake_minimum_required(VERSION 3.31)
project(op3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/slipum/qt/6.9.2/macos")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(op3 src/main.cpp src/interface/mainwindow.cpp
        src/entrypoint/entrypoint.cpp
        src/bussines/logic.cpp
        src/interface/graphwindow.cpp
        src/bussines/logic_graph.cpp)
target_link_libraries(op3
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

