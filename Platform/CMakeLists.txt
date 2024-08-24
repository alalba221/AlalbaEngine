cmake_minimum_required(VERSION 3.22)

add_library(Alalba_platform
        Private/AlalbaLog.cpp
        Private/AlalbaWindow.cpp
        Private/Window/AlalbaGLFWindow.cpp
)

target_include_directories(Alalba_platform PUBLIC External)
add_subdirectory(External/glfw)
target_link_libraries(Alalba_platform PRIVATE glfw)