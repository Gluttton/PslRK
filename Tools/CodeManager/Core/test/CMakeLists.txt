find_package (GTest REQUIRED)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -mtune=native -march=native -fprofile-arcs -ftest-coverage")
set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


set (
    CodeManagerCoreTest_SOURCES
    ../src/Validator.cpp
    ../src/Calculator.cpp
    ../src/Representer.cpp
    ValidatorTest.cpp
    CalculatorTest.cpp
    RepresenterTest.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
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
