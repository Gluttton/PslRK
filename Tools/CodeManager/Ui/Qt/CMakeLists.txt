cmake_minimum_required (VERSION 2.8.8)

find_package (PugiXML       REQUIRED)
find_package (Qt5Core       REQUIRED)
find_package (QCustomPlot   REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")


set (CodeManagerQt_SOURCES
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/main.cpp
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/MainWidget.cpp
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/StorageManageWidget.cpp
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/ActivityWidget.cpp
)

set (CodeManagerQt_HEADERS
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/ValidatorAdapter.h
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/MainWidget.h
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/StorageManageWidget.h
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/ActivityWidget.h
)

qt5_wrap_cpp (
    CodeManagerQt_HEADERS_MOC ${CodeManagerQt_HEADERS}
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include
    ${PROJECT_SOURCE_DIR}
    ${PUGIXML_INCLUDE_DIR}
    ${QCustomPlot_INCLUDE_DIR}
)

link_directories (
    ${PROJECT_BINARY_DIR}
)

add_executable (
    pslcmqt
    ${CodeManagerQt_SOURCES}
    ${CodeManagerQt_HEADERS_MOC}
)

target_link_libraries (
    pslcmqt
    pslcmcore
    ${PUGIXML_LIBRARIES}
    ${QCustomPlot_LIBRARIES}
)

qt5_use_modules (
    pslcmqt
    Core
    Widgets
    PrintSupport
)
