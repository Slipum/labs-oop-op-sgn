cmake_minimum_required(VERSION 3.31)
project(oop1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Только .cpp файлы!
file(GLOB_RECURSE SOURCES "./src/*.cpp")

# Проверка: нашли ли .cpp файлы
if(NOT SOURCES)
    message(FATAL_ERROR "Не найдено .cpp файлов! Проверьте структуру проекта.")
endif()

message("Найдено исходников: ${SOURCES}")

# Создать исполняемый файл
add_executable(oop1 ${SOURCES})

# Include директории (опционально)
target_include_directories(oop1 PRIVATE .)
