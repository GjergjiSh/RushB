cmake_minimum_required(VERSION 3.16.3)

project(VideoSub VERSION 0.1 DESCRIPTION "RushB VideoSub module")

find_package (Threads)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(MODULE_INTERFACE_DIR "../../include")

add_library(VideoSub SHARED .
    src/VideoSub.cpp
)

set_target_properties(VideoSub PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/VideoSub.h
)

target_include_directories(VideoSub PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
    /usr/include/gstreamer-1.0
    /usr/include/glib-2.0
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
)

target_link_libraries(VideoSub
    -lgstreamer-1.0
    -lgobject-2.0
    -lglib-2.0
    -lgstapp-1.0
    Threads::Threads
)