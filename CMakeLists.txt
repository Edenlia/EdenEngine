cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)

project(EdenEngine)

find_package(Vulkan REQUIRED)

# Add glm as a subdirectory
add_subdirectory(Source/ThirdParty/glm)

# Platform specific configurations
if(APPLE)
    # Enable Objective-C++ language for macOS
    enable_language(OBJCXX)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(METAL_FRAMEWORK Metal)
    find_library(METALKIT_FRAMEWORK MetalKit)
    find_library(QUARTZ_CORE_FRAMEWORK QuartzCore)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore")
    
    # Set source files for macOS
    set(MAC_PLATFORM_SOURCES
            Source/Runtime/Core/Display/MacDisplay.mm
            Source/Runtime/Core/RHI/Metal/MetalRHI.mm
            Source/Runtime/Core/RHI/Metal/MetalRHI.h
    )
    
    # Enable Objective-C++ compilation for macOS files
    set_source_files_properties(
        Source/Runtime/Main.cpp
            Source/Runtime/Core/Display/MacDisplay.mm
        PROPERTIES LANGUAGE OBJCXX
    )
elseif(WIN32)
    # Set source files for Windows
    set(WIN_PLATFORM_SOURCES
        Source/Runtime/Core/Display/WindowsDisplay.cpp
            Source/Runtime/Core/RHI/Vulkan/VulkanRHI.cpp
            Source/Runtime/Core/RHI/Vulkan/VulkanRHI.h
    )
endif()

if (APPLE)
    set(PLATFORM_SOURCES ${MAC_PLATFORM_SOURCES})
elseif (WIN32)
    set(PLATFORM_SOURCES ${WIN_PLATFORM_SOURCES})
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
# Include source files
add_executable(EdenEngine 
    Source/Runtime/Main.cpp
    ${PLATFORM_SOURCES}
    Source/Runtime/Core/RHI/IRHI.h
)

if (APPLE)
    # Link Cocoa framework
    target_link_libraries(EdenEngine PRIVATE 
        ${COCOA_FRAMEWORK}
        ${METAL_FRAMEWORK}
        ${METALKIT_FRAMEWORK}
        ${QUARTZ_CORE_FRAMEWORK}
    )
endif()

    # Include directories
target_include_directories(EdenEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/Source/Runtime
    ${CMAKE_SOURCE_DIR}/Source/ThirdParty/glm
)

# Link glm and Vulkan libraries
target_link_libraries(EdenEngine PRIVATE
        glm::glm-header-only
        Vulkan::Vulkan
)

