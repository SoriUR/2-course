cmake_minimum_required(VERSION 3.3)
project(Lab4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp utils.cpp)
set(SORT_SOURCE sortMain.cpp fileMapping.cpp sort_util.cpp utils.cpp)
add_executable(sort_find ${SORT_SOURCE})
add_executable(Lab4 ${SOURCE_FILES})