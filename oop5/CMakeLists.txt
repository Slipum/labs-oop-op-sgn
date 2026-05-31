cmake_minimum_required(VERSION 3.16)

project(oop5)

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

# Core

add_library(core
        src/abstructs/door/door.cpp
        src/abstructs/door/door.h
        src/abstructs/elevator/elevator.cpp
        src/abstructs/controller/controller.cpp
        src/abstructs/controller/controller.h
        src/abstructs/cabin/cabin.cpp
        src/abstructs/cabin/cabin.h
        src/abstructs/builder/builder.cpp
        src/abstructs/builder/builder.h
        src/manager/manager.cpp
        src/manager/manager.h
        src/facade.cpp
        src/facade.h
)

target_include_directories(core PUBLIC src)

# Ui components

add_library(ui
        src/interface/mainwindow.cpp
)
target_link_libraries(ui PRIVATE core Qt::Gui Qt::Widgets)

# Main

add_executable(oop5
        src/main.cpp
)

target_link_libraries(oop5 PRIVATE core ui Qt::Core Qt::Gui Qt::Widgets)

# Tests

add_executable(tests
        tests/ElevetorControllerTEST.cpp

)

target_link_libraries(
        tests
        PRIVATE
        core
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(tests)
