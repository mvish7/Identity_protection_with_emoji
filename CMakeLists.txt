cmake_minimum_required(VERSION 3.10)
project(Identity_Protection)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_executable(Identity_Protection main.cpp)
target_link_libraries (Identity_Protection ${OpenCV_LIBRARIES})