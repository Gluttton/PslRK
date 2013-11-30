cmake_minimum_required (VERSION 2.8.8)

find_package (PugiXML REQUIRED)
find_package (Qt5Core REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++0x")
set (CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")

set (CMAKE_SHARED_LINKER_FLAGS "-Wall -Wextra")


set (CodeManagerQt_SOURCES
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/main.cpp
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/MainWidget.cpp
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/StorageManageWidget.cpp
    ${PROJECT_SOURCE_DIR}/Ui/Qt/src/ActivityWidget.cpp
    ${PROJECT_SOURCE_DIR}/External/QCustomPlot/qcustomplot.cpp
)

set (CodeManagerQt_HEADERS
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/MainWidget.h
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/StorageManageWidget.h
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include/ActivityWidget.h
    ${PROJECT_SOURCE_DIR}/External/QCustomPlot/qcustomplot.h
)

qt5_wrap_cpp (
    CodeManagerQt_HEADERS_MOC ${CodeManagerQt_HEADERS}
)

include_directories (
    ${PROJECT_SOURCE_DIR}/Core/include
    ${PROJECT_SOURCE_DIR}/Ui/Qt/include
    ${PROJECT_SOURCE_DIR}
    ${PUGIXML_INCLUDE_DIR}
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
    mslmcore
    ${PUGIXML_LIBRARIES}
)

qt5_use_modules (
    pslcmqt
    Core
    Widgets
    PrintSupport
)
