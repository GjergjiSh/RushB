cmake_minimum_required(VERSION 3.16.3)

project(TEMPLATE VERSION 1.0 DESCRIPTION "RushB TEMPLATE module")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(MODULE_INTERFACE_DIR "../../include")

add_library(TEMPLATE SHARED .
    src/TEMPLATE.cpp
)

set_target_properties(TEMPLATE PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/TEMPLATE.h
)

target_include_directories(TEMPLATE PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
)

target_link_libraries( TEMPLATE
)