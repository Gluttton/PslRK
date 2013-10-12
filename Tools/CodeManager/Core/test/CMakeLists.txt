find_package (GTest REQUIRED)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -mtune=native -march=native -fprofile-arcs -ftest-coverage")
set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


set (
    CodeManagerCoreTest_SOURCES
    ValidatorTest.cpp
    CalculatorTest.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/include
)


add_executable (
    CodeManagerCoreTest
    #EXCLUDE_FROM_ALL
    ${CodeManagerCoreTest_SOURCES}
)

target_link_libraries (
    CodeManagerCoreTest
    gtest
    gtest_main
    gcov
    pthread
)

add_test (
    CodeManagerCoreTest
    CodeManagerCoreTest
)
