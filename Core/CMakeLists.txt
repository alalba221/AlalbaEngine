cmake_minimum_required(VERSION 3.22)

add_library( Alalba_core
        Private/AlalbaApplication.cpp
)

target_link_libraries(Alalba_core PUBLIC Alalba_platform)