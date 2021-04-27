PROJECT(lesson8)

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

add_executable(program src/main.cpp)

target_include_directories(program PRIVATE include)