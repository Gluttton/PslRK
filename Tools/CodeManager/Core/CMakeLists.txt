cmake_minimum_required (VERSION 2.8.8)

find_package (PugiXML REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native -std=c++11")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")


set (CodeManagerCore_SOURCES
    ${PROJECT_SOURCE_DIR}/Core/src/Exception.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Validator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Calculator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Representer.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/XmlManager.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
    ${PUGIXML_INCLUDE_DIR}
)

link_directories (
    ${PROJECT_BINARY_DIR}
)

add_library (
    pslcmcore SHARED
    ${CodeManagerCore_SOURCES}
    ${PUGIXML_LIBRARIES}
)

add_subdirectory (
    test
)
