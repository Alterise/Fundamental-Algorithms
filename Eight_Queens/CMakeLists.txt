cmake_minimum_required(VERSION 3.19)
project(Eight_Queens)

set(CMAKE_CXX_STANDARD 17)

include_directories(Solver)
add_executable(Eight_Queens main.cpp)