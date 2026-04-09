cmake_minimum_required(VERSION 3.31)
project(oop2)

set(CMAKE_CXX_STANDARD 20)

add_executable(oop2 main.cpp tests.cpp ./matrix/matrix.cpp ./matrix/iterator.cpp)
