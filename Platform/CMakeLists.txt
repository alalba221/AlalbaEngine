cmake_minimum_required(VERSION 3.22)

add_library(Alalba_platform
        Private/AlalbaLog.cpp
        Private/AlalbaWindow.cpp
        Private/Window/AlalbaGLFWindow.cpp
        Private/AlalbaGFXContext.cpp
        Public/GFX/Vulkan/VKCommon.h
        Private/GFX/Vulkan/GFXContext.cpp
)

target_include_directories(Alalba_platform PUBLIC External)
add_subdirectory(External/glfw)
target_link_libraries(Alalba_platform PRIVATE glfw)

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message("--------> Find Vulkan success: ${Vulkan_INCLUDE_DIRS}")
endif()

target_include_directories(Alalba_platform PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(Alalba_platform PRIVATE ${Vulkan_LIBRARY})