cmake_minimum_required(VERSION 3.17)
project(Problem2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Problem2 Lab3Prob2.cpp)
# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")