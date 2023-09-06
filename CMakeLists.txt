cmake_minimum_required(VERSION 3.26)
project(EdenEngine)

set(CMAKE_CXX_STANDARD 23)

if (WIN32)
    message("Windows detected")
endif (WIN32)

if (APPLE)
    message("Apple detected")
endif (APPLE)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)


add_executable(EdenEngine main.cpp)

