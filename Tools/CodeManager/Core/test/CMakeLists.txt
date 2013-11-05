find_package (GTest REQUIRED)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -mtune=native -march=native -fprofile-arcs -ftest-coverage")
set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


set (
    CodeManagerCoreTest_SOURCES
    ${PROJECT_SOURCE_DIR}/Core/src/Exception.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Validator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Calculator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Representer.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/ValidatorTest.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/CalculatorTest.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/RepresenterTest.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
)


add_executable (
    CodeManagerCoreTest
    #EXCLUDE_FROM_ALL
    ${CodeManagerCoreTest_SOURCES}
)


add_custom_command (
    OUTPUT  coverage.info
    COMMAND lcov -q -c -f -b . -d ${PROJECT_BINARY_DIR}/Core/test -o ${PROJECT_BINARY_DIR}/coverage.info &&
            lcov -e ${PROJECT_BINARY_DIR}/coverage.info '${PROJECT_SOURCE_DIR}/*' -o ${PROJECT_BINARY_DIR}/coverage.info &&
            genhtml ${PROJECT_BINARY_DIR}/coverage.info --legend -f -q -o ${PROJECT_BINARY_DIR}/coverage
    DEPENDS CodeManagerCoreTest
)

add_custom_target  (coverage DEPENDS coverage.info)


file (
    GLOB_RECURSE
    COVERAGE_GCNO_FILES
    "${PROJECT_BINARY_DIR}/*.gcno"
)

file (
    GLOB_RECURSE
    COVERAGE_GCDA_FILES
    "${PROJECT_BINARY_DIR}/*.gcda"
)

set (
    COVERAGE_DATA
    ${PROJECT_BINARY_DIR}/coverage
    ${PROJECT_BINARY_DIR}/coverage.info
    ${COVERAGE_GCNO_FILES}
    ${COVERAGE_GCDA_FILES}
)

set_directory_properties (
    PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${COVERAGE_DATA}"
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
