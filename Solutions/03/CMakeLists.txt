cmake_minimum_required (VERSION 2.8.8)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/CMakeModules")
find_package (PugiXML REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")


include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/Core/include
    ${PUGIXML_INCLUDE_DIR}
)

link_directories (
    ${PROJECT_BINARY_DIR}
)


set (CodeManagerCore_SOURCES
    ${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/Core/src/Exception.cpp
    ${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/Core/src/Validator.cpp
    ${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/Core/src/Calculator.cpp
    ${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/Core/src/Representer.cpp
    ${PROJECT_SOURCE_DIR}/../../Tools/CodeManager/Core/src/XmlManager.cpp
    ${PROJECT_SOURCE_DIR}/XmlManagerCBind.cpp
)

add_library (
    pslcmcore STATIC
    ${CodeManagerCore_SOURCES}
    ${PUGIXML_LIBRARIES}
)


set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native -std=c11")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set (CMAKE_C_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_C_FLAGS_RELEASE "-O3")

add_definitions (-DTHREADS=1)

set (lpslcd_SOURCES
    ${PROJECT_SOURCE_DIR}/main.c
)

add_executable (
    lpslcd
    ${lpslcd_SOURCES}
)

target_link_libraries (
    lpslcd
    pslcmcore
    pthread
    m
    ${PUGIXML_LIBRARIES}
)
