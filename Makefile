cmake_minimum_required(version 3.5)
project(ASCII_DRAWER)

find_package(OPENCV REQUIRED)
include_directories({$OpenCV_INCLUDE_DIRS})
add_executable(image_to_ascii.cpp)
target_include_directories() //TODO Finish this

