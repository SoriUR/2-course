cmake_minimum_required(VERSION 3.3)
project(Lab5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp fileMapping.cpp sort_util.cpp utils.cpp)
add_executable(Lab5 ${SOURCE_FILES})