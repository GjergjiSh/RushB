cmake_minimum_required(VERSION 3.16.3)

project(ObjectDetector VERSION 2.0 DESCRIPTION "RushB ObjectDetector module")

find_package(TensorflowCC REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CUDA)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations"
)

set(CONTROL_CENTER_DIR "../../")
set(MODULE_INTERFACE_DIR ${CONTROL_CENTER_DIR}/include)
set(DETECTION_LIB_DIR "detection-lib")

add_library(ObjectDetector SHARED .
    src/ObjectDetector.cpp
    ${DETECTION_LIB_DIR}/src/DnnObjectDetector.cpp
    ${DETECTION_LIB_DIR}/src/TfObjectDetector.cpp
    ${CONTROL_CENTER_DIR}/src/Logger.cpp
)

set_target_properties(ObjectDetector PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ./include/ObjectDetector.h
)

target_include_directories(ObjectDetector PRIVATE .
    include
    ${DETECTION_LIB_DIR}/include
    ${MODULE_INTERFACE_DIR}
    ${OpenCV_INCLUDE_DIRS}

    # OpenCV Contrib modules not automatically being added
    # by OpenCV_INCLUDE_DIRS
    /usr/local/include/opencv4/opencv2/
)

target_link_libraries( ObjectDetector
    ${OpenCV_LIBS}
    TensorflowCC::TensorflowCC
    -fopenmp
)

if(CUDA_FOUND)
  target_link_libraries(ObjectDetector ${CUDA_LIBRARIES})
endif()