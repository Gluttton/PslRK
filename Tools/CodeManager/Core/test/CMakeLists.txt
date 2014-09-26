find_package (GTest                       REQUIRED)
find_package (Boost COMPONENTS filesystem
                               system     REQUIRED)
find_package (PugiXML                     REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -march=native -mtune=native -fprofile-arcs -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


set (
    CodeManagerCoreTest_SOURCES
    ${PROJECT_SOURCE_DIR}/Core/src/Exception.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Validator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Calculator.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/Representer.cpp
    ${PROJECT_SOURCE_DIR}/Core/src/XmlManager.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/ValidatorTest.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/CalculatorTest.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/RepresenterTest.cpp
    ${PROJECT_SOURCE_DIR}/Core/test/XmlManagerTest.cpp
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
    ${Boost_INCLUDE_DIR}
    ${PUGIXML_INCLUDE_DIR}
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

determine_coverage_data ("${CodeManagerCoreTest_SOURCES}" CodeManagerCoreTest COVERAGE_GCNO_FILES ".gcno")
determine_coverage_data ("${CodeManagerCoreTest_SOURCES}" CodeManagerCoreTest COVERAGE_GCDA_FILES ".gcda")
set (Coverage_REPORT ${PROJECT_BINARY_DIR}/coverage.info)
set (Coverage_DIR    ${PROJECT_BINARY_DIR}/coverage)
set (
    COVERAGE_DATA
    ${Coverage_REPORT}
    ${Coverage_DIR}
    ${COVERAGE_GCNO_FILES}
    ${COVERAGE_GCDA_FILES}
)

set_directory_properties (
    PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${COVERAGE_DATA}"
)


target_link_libraries (
    CodeManagerCoreTest
    ${Boost_LIBRARIES}
    ${PUGIXML_LIBRARIES}
    gtest
    gtest_main
    gcov
    pthread
)

add_test (
    CodeManagerCoreTest
    CodeManagerCoreTest
)
