cmake_minimum_required(VERSION 2.6)
project(graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wshadow")

add_executable(graph cgraph.cpp main.cpp)

install(TARGETS graph RUNTIME DESTINATION bin)
