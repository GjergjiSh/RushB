cmake_minimum_required(VERSION 3.16.3)

project(Writer VERSION 1.0 DESCRIPTION "Sets servo values to values configured in ModuleConfig.xml")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(MODULE_INTERFACE_DIR "../../include")

add_library(Writer SHARED .
    src/Writer.cpp
)

set_target_properties(Writer PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/Writer.h
)

target_include_directories(Writer PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
)

target_link_libraries( Writer
)