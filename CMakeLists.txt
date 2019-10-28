cmake_minimum_required(VERSION 3.1)
project(sketch)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_GXX_FLAGS "-Wall -Wextra -Wconversion  -pedantic")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(sketch src/sketch.cpp)
target_link_libraries(sketch ${OpenCV_LIBS})