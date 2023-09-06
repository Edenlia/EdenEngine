cmake_minimum_required(VERSION 3.26)
project(EdenEngine)

set(CMAKE_CXX_STANDARD 23)

#if (WIN32)
#    message("Windows detected")
#endif (WIN32)
#
#if (APPLE)
#    message("Apple detected")
#endif (APPLE)

add_executable(EdenEngine main.cpp)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(EdenEngine PRIVATE GLUT::GLUT)
target_link_libraries(EdenEngine PRIVATE GLEW::GLEW)
target_include_directories(EdenEngine PRIVATE ${GLM_INCLUDE_DIRS})
