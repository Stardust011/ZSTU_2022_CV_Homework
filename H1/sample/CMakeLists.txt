cmake_minimum_required(VERSION 3.16)
project(opencv_learn)

set(CMAKE_CXX_STANDARD 14)

#opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_executable(sample main.cpp)
