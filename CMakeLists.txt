#You must specify a minimum version of cmake to ensure correct behavior
cmake_minimum_required(VERSION 3.10)

#Set the project name
project(OpenCV)

#Enable support for a specific C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#We need to find the OpenCV files on the system
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#This tells CMake to create an executable with the following name based on the specified source files
add_executable(main main.cpp)

target_link_libraries(main ${OpenCV_LIBS})
