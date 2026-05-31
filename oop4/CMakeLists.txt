cmake_minimum_required(VERSION 3.16)

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

# Core

add_library(core
        src/entities/abstructs/services/figure.cpp
        src/entities/abstructs/services/vertex.cpp
        src/math/transform.cpp
        src/scene/camera.cpp
        src/scene/scene.cpp
        src/business/file.cpp
        src/facade.cpp
)

target_include_directories(core PUBLIC src)

add_library(ui
        src/drawer/drawer.h
)
target_link_libraries(ui PRIVATE core Qt::Gui Qt::Widgets)

# Visual

add_executable(oop4
        src/main.cpp
        src/interface/mainwindow.cpp
        src/interface/graphics/visual.cpp
        src/interface/qtscene.h
        src/interface/qtscene.cpp
)

target_link_libraries(oop4 PRIVATE core ui Qt::Core Qt::Gui Qt::Widgets)

# Tests

add_executable(tests
        tests/vertexTest.cpp
        tests/figureTest.cpp
        tests/edgeTest.cpp
        tests/transformMatrixTest.cpp
        tests/sceneTest.cpp
        tests/fileReader.cpp
        tests/facadeTest.cpp
)

target_link_libraries(
        tests
        PRIVATE
        core
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(tests)
