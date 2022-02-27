cmake_minimum_required(VERSION 3.16.3)

project(VideoPub VERSION 1.0 DESCRIPTION "RushB VideoPub module")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)

add_library(VideoPub SHARED .
    src/VideoPub.cpp
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(VideoPub PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/VideoPub.h
)

target_include_directories(VideoPub PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
    /usr/include/gstreamer-1.0
    /usr/include/glib-2.0
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
)

target_link_libraries( VideoPub
    -lgstreamer-1.0
    -lgobject-2.0
    -lglib-2.0
    -lgstapp-1.0
)