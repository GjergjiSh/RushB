cmake_minimum_required(VERSION 3.16.3)

project(zmq_pipeline VERSION 2.0 DESCRIPTION "RushB zmq pipeline module")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)

add_library(ZmqPipeline SHARED .
    src/ZmqPipeline.cpp
    src/ProtoModuleInterface.pb.cc
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(ZmqPipeline PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/ZmqPipeline.h
)

target_include_directories(ZmqPipeline PRIVATE .
    include
    ${MODULE_INTERFACE_DIR}
)

target_link_libraries( ZmqPipeline
    -lzmq
    -lprotobuf
)