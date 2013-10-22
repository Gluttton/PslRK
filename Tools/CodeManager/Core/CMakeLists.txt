cmake_minimum_required (VERSION 2.8.8)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++0x")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")


set (CodeManagerCore_SOURCES
    ${PROJECT_SOURCE_DIR}/Core/src/Exception.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Validator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Calculator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Representer.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
)

link_directories (
    ${PROJECT_BINARY_DIR}
)

add_library (
    mslmcore SHARED
    ${CodeManagerCore_SOURCES}
)

target_link_libraries (
    mslmcore
)


add_subdirectory (
    test
)
