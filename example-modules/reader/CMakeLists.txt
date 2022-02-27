cmake_minimum_required(VERSION 3.16.3)

project(reader VERSION 1.0 DESCRIPTION "Reads shared module data and prints them out")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)

add_library(Reader SHARED .
    src/Reader.cpp
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(Reader PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/Reader.h
)

target_include_directories(Reader PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
)

target_link_libraries( Reader
)