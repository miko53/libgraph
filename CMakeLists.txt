cmake_minimum_required(VERSION 2.6)
project(graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wshadow")

# Setup testing
#enable_testing()

add_executable(graph cgraph.cpp main.cpp)
add_executable(graph_tu tu.cpp cgraph.cpp)

install(TARGETS graph RUNTIME DESTINATION bin)

