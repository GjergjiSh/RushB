cmake_minimum_required(VERSION 3.16.3)

project(VideoPlayer VERSION 1.0 DESCRIPTION "RushB VideoPlayer module")

find_package( OpenCV REQUIRED )

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)

add_library(VideoPlayer SHARED .
    src/VideoPlayer.cpp
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(VideoPlayer PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/VideoPlayer.h
)

target_include_directories(VideoPlayer PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(VideoPlayer
    ${OpenCV_LIBS}
)