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

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/ext
)

file(GLOB SOURCE_FILE
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/util/*.h
        ${CMAKE_SOURCE_DIR}/src/util/*.hpp
        ${CMAKE_SOURCE_DIR}/src/util/*.cpp
        ${CMAKE_SOURCE_DIR}/src/ext/*/*.h
        ${CMAKE_SOURCE_DIR}/src/ext/*/*.hpp
        ${CMAKE_SOURCE_DIR}/src/ext/*/*.cpp
)

# Sort the file into different folders
foreach(_source_file IN ITEMS ${SOURCE_FILE})
    get_filename_component(_source_path "${_source_file}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source_file}")
endforeach()

add_executable(EdenEngine ${SOURCE_FILE})

find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLFW3 CONFIG REQUIRED)


target_link_libraries(EdenEngine PRIVATE GLEW::GLEW)
target_link_libraries(EdenEngine PRIVATE assimp::assimp)
target_link_libraries(EdenEngine PRIVATE glm::glm)
target_link_libraries(EdenEngine PRIVATE glfw)

