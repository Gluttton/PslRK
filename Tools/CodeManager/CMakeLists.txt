cmake_minimum_required (VERSION 2.8.8)

project (CodeManager)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")
include ("${PROJECT_SOURCE_DIR}/CMakeModules/UseGCov.cmake")

set (CodeManager_VERSION_MAJOR 0)
set (CodeManager_VERSION_MINOR 1)


enable_testing ()

add_custom_target (tests)
add_dependencies  (tests CodeManagerCoreTest)

add_subdirectory (Core)
add_subdirectory (Ui)
