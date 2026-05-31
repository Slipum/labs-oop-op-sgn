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

# Pure logic (no Qt)

add_library(logic
        src/entrypoint/entrypoint.h
        src/abstructs/cabin/cabin.cpp
        src/abstructs/cabin/cabin.h
        src/abstructs/door/door.cpp
        src/abstructs/door/door.h
        src/abstructs/controller/controller.cpp
        src/abstructs/controller/controller.h
        src/abstructs/elevator/elevator.cpp
        src/abstructs/elevator/elevator.h
        src/manager/manager.cpp
        src/manager/manager.h
        src/abstructs/builder/builder.cpp
        src/abstructs/builder/builder.h
)

target_include_directories(logic PUBLIC src)

# Qt: тексты + фасад

add_library(elevator_qt
        src/interface/texts.cpp
        src/interface/texts.h
        src/facade.cpp
        src/facade.h
)

target_include_directories(elevator_qt PUBLIC src)
target_link_libraries(elevator_qt PUBLIC logic Qt6::Core)

# UI

add_library(ui
        src/interface/mainwindow.cpp
        src/interface/mainwindow.h
        src/interface/mainwindow.ui
)

target_include_directories(ui PUBLIC src)
target_link_libraries(ui PUBLIC elevator_qt Qt6::Gui Qt6::Widgets)

# Main

add_executable(oop5
        src/main.cpp
)

target_link_libraries(oop5 PRIVATE ui Qt6::Core Qt6::Gui Qt6::Widgets)

# Tests

add_executable(tests
        tests/ElevatorControllerTest.cpp
)

target_link_libraries(
        tests
        PRIVATE
        logic
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(tests)
