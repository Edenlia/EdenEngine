cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)

# vcpkg
if(NOT $ENV{VCPKG_ROOT} STREQUAL "")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
if(NOT $ENV{VCPKG_DEFAULT_TRIPLET} STREQUAL "")
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif()


project(EdenEngine)

add_executable(EdenEngine main.cpp)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(EdenEngine PRIVATE GLUT::GLUT)
target_link_libraries(EdenEngine PRIVATE GLEW::GLEW)
target_link_libraries(EdenEngine PRIVATE glm::glm)
