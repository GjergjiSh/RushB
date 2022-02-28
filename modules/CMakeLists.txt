cmake_minimum_required(VERSION 3.16.3)

project(rushb_modules VERSION 1.0 DESCRIPTION "Modules for RushB")

option(BUILD_EXAMPLE_MODULES "Building Example Modules" ON)
option(BUILD_CONTROLLER "Building Controller Module" ON)
option(BUILD_ZMQPIPELINE "Building ZMQ Pipeline Module" ON)
option(BUILD_VIDEOPUB "Building Video Publisher Module" ON)
option(BUILD_VIDEOSUB "Building Video Subscriber Module" ON)
option(BUILD_VIDEOPLAYER "Building Video Player Module" ON)
option(BUILD_OBJECTDETECTOR "Building Object Detection Module" ON)
option(BUILD_INOLINK "Building Inolink Module" ON)

if(BUILD_EXAMPLE_MODULES)
    add_subdirectory(example-modules)
endif()

if(BUILD_CONTROLLER)
    add_subdirectory(controller)
endif()
if(BUILD_ZMQPIPELINE)
    add_subdirectory(zmqpipeline)
endif()
if(BUILD_VIDEOSUB)
    add_subdirectory(videosub)
endif()
if(BUILD_VIDEOPUB)
    add_subdirectory(videopub)
endif()
if(BUILD_VIDEOPLAYER)
    add_subdirectory(videoplayer)
endif()
if(BUILD_OBJECTDETECTOR)
    add_subdirectory(objectdetector)
endif()
if(BUILD_INOLINK)
    add_subdirectory(inolink)
endif()








