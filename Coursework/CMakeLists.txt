cmake_minimum_required(VERSION 3.19)
project(Coursework)

set(CMAKE_CXX_STANDARD 17)

include_directories(BinaryTree Generator DataBase Strategies Utility)
add_executable(Coursework main.cpp)