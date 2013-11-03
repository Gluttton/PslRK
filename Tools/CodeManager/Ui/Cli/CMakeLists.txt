cmake_minimum_required (VERSION 2.8.8)

#find_package (Boost COMPONENTS filesystem REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++0x")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")


set (CodeManagerCli_SOURCES
    ${PROJECT_SOURCE_DIR}/Ui/Cli/src/main.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
    ${PROJECT_SOURCE_DIR}/Ui/Cli/include
)

link_directories (
    ${PROJECT_BINARY_DIR}
)

add_executable (
    pslcm
    ${CodeManagerCli_SOURCES}
)

target_link_libraries (
    pslcm
    mslmcore
#    ${Boost_LIBRARIES}
)
