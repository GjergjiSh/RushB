cmake_minimum_required(VERSION 3.16.3)

project(controller VERSION 1.0 DESCRIPTION "RushB Controller Module")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)


add_library(Controller SHARED .
    src/Controller.cpp
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(Controller PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/Controller.h
)

target_include_directories(Controller PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
)