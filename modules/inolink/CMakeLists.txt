cmake_minimum_required(VERSION 3.16.3)

project(InoLink VERSION 1.0 DESCRIPTION "RushB InoLink module")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations -fPIC"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)

add_library(InoLink SHARED .
    src/InoLink.cpp
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(InoLink PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/InoLink.h
)

target_include_directories(InoLink PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
)

target_link_libraries( InoLink
    -lCppLinuxSerial
)