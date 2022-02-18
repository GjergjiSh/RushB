cmake_minimum_required(VERSION 3.16.3)

project(control_center VERSION 1.0 DESCRIPTION "RushB Control Center")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -O2 -std=c++17 -Wno-deprecated-declarations")
set(MODULES_DIR ${CMAKE_HOME_DIRECTORY}/RushBModules)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_BINARY_DIR}/modules ${MODULES_DIR}/build)

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

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/modules)
add_custom_command(
        TARGET ControlCenter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/resources/Modules.xml
                ${CMAKE_CURRENT_BINARY_DIR}/Modules.xml
)

if (BUILD_MODULES)
add_custom_command(TARGET ControlCenter POST_BUILD
  COMMAND  cd ${MODULES_DIR} && mkdir build && cd build && cmake .. && make
)

add_custom_command(TARGET ControlCenter POST_BUILD
  COMMAND  find ${MODULES_DIR} -type f | grep -i so | xargs -i mv {} ${CMAKE_BINARY_DIR}/modules
)
endif()