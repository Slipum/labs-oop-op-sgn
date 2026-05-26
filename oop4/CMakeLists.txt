cmake_minimum_required(VERSION 3.31)
project(oop4)

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

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(oop4
        src/main.cpp
        src/facade.cpp
        src/scene/scene.cpp # TODO: вроде сделал QtSceneDrawer
        src/transform/transform.cpp # доделать
        src/scene/object/object.cpp # доделать
        src/operations/operations.cpp

        src/interface/mainwindow.cpp
        src/interface/graphics/visual.cpp
)
target_link_libraries(oop4
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

