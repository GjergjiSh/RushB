cmake_minimum_required(VERSION 3.16.3)

project(control_center VERSION 1.0 DESCRIPTION "RushB Control Center")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations")

add_subdirectory(modules)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/avail_modules)

add_executable(ControlCenter .
    src/Main.cpp
    src/ModuleHandler.cpp
    src/SignalHandler.cpp
)

set_target_properties(ControlCenter PROPERTIES
    VERSION ${PROJECT_VERSION}
)

target_include_directories(ControlCenter PRIVATE .
    include
    ModuleInterface
)

target_link_libraries(ControlCenter
    -lpugixml
    ${CMAKE_DL_LIBS}
)

add_custom_command(
        TARGET ControlCenter PRE_BUILD
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/avail_modules
         COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/resources/ModuleConfig.xml
                ${CMAKE_CURRENT_BINARY_DIR}/ModuleConfig.xml
)

add_custom_target(avail_modules ALL
    COMMAND  find ./modules -type f | grep -i so | xargs -i cp {} ./avail_modules
    COMMENT Installing modules
)