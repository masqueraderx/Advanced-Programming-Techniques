cmake_minimum_required(VERSION 3.17)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab3 Lab3Prob3.cpp)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")