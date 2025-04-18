cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)

project(EdenEngine)

# Add glm as a subdirectory
add_subdirectory(Source/ThirdParty/glm)

# Platform specific configurations
if(APPLE)
    # Enable Objective-C++ language for macOS
    enable_language(OBJCXX)
    find_library(COCOA_FRAMEWORK Cocoa)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
    
    # Set source files for macOS
    set(PLATFORM_SOURCES
        Source/Runtime/Core/Display/MacDisplay.cpp
    )
    
    # Enable Objective-C++ compilation for macOS files
    set_source_files_properties(
        Source/Runtime/Main.cpp
        Source/Runtime/Core/Display/MacDisplay.cpp
        PROPERTIES LANGUAGE OBJCXX
    )
    
    # Link Cocoa framework
    target_link_libraries(EdenEngine PRIVATE ${COCOA_FRAMEWORK})
elseif(WIN32)
    # Set source files for Windows
    set(PLATFORM_SOURCES
        Source/Runtime/Core/Display/WindowsDisplay.cpp
    )
endif()

# Include source files
add_executable(EdenEngine 
    Source/Runtime/Main.cpp
    ${PLATFORM_SOURCES}
)

# Include directories
target_include_directories(EdenEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/Source/Runtime
    ${CMAKE_SOURCE_DIR}/Source/ThirdParty/glm
)

# Link glm
target_link_libraries(EdenEngine PRIVATE glm::glm-header-only)

# Commented out all other configurations
# if(NOT $ENV{VCPKG_ROOT} STREQUAL "")
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# endif()
# if(NOT $ENV{VCPKG_DEFAULT_TRIPLET} STREQUAL "")
#     set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
# endif()

# include_directories(
#         ${CMAKE_SOURCE_DIR}/src
#         ${CMAKE_SOURCE_DIR}/src/ext
# )

# file(GLOB SOURCE_FILE
#         ${CMAKE_SOURCE_DIR}/src/*.h
#         ${CMAKE_SOURCE_DIR}/src/*.hpp
#         ${CMAKE_SOURCE_DIR}/src/*.cpp
#         ${CMAKE_SOURCE_DIR}/src/util/*.h
#         ${CMAKE_SOURCE_DIR}/src/util/*.hpp
#         ${CMAKE_SOURCE_DIR}/src/util/*.cpp
#         ${CMAKE_SOURCE_DIR}/src/ext/*/*.h
#         ${CMAKE_SOURCE_DIR}/src/ext/*/*.hpp
#         ${CMAKE_SOURCE_DIR}/src/ext/*/*.cpp
# )

# foreach(_source_file IN ITEMS ${SOURCE_FILE})
#     get_filename_component(_source_path "${_source_file}" PATH)
#     string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
#     string(REPLACE "/" "\\" _group_path "${_group_path}")
#     source_group("${_group_path}" FILES "${_source_file}")
# endforeach()

# find_package(GLEW REQUIRED)
# find_package(GLUT REQUIRED)
# find_package(assimp REQUIRED)
# find_package(glm CONFIG REQUIRED)

# target_link_libraries(EdenEngine PRIVATE GLUT::GLUT)
# target_link_libraries(EdenEngine PRIVATE GLEW::GLEW)
# target_link_libraries(EdenEngine PRIVATE assimp::assimp)
# target_link_libraries(EdenEngine PRIVATE glm::glm)

