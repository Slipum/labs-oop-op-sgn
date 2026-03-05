cmake_minimum_required(VERSION 3.31)
project(op1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/slipum/Qt/6.9.2/macos")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(op1 main.cpp)
target_link_libraries(op1
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

