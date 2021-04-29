cmake_minimum_required(VERSION 3.19)
project(Lab2_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(BinaryTrees)
include_directories(Strategies)
add_executable(BinaryTrees "Main/BinaryTrees.cpp" "BinaryTrees/RB_tree.cpp")