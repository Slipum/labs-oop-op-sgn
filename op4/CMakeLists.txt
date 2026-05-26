cmake_minimum_required(VERSION 3.31)
project(op4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/slipum/qt/6.9.2/macos")


find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
)

add_executable(op4
        src/main.cpp
        src/interface/mainwindow.cpp
        src/interface/graphics/visual.cpp
        src/entrypoint/appcontex.cpp
        src/entrypoint/entrypoint.cpp
        src/business/logic_graphics.cpp
        src/business/camera.cpp
)
target_link_libraries(op4
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

