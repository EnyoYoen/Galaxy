cmake_minimum_required(VERSION 3.1.0)

project(
    Galaxy
    VERSION 0.1
    DESCRIPTION "A modular set of tools grouped in an app, made in C++ with Qt6"
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES
    "src/main.cpp"
    "src/galaxy.cpp"
    "src/widgets/sidebar.cpp"
    "src/widgets/sidebarmodule.cpp"
    "tools/logger.cpp"
)

set(HEADERS
    "src/galaxy.h"
    "src/widgets/sidebar.h"
    "src/widgets/sidebarmodule.h"
    "src/tools/logger.h"
    "tools/logger.h"
)

qt_add_resources(SOURCES "src/galaxy.qrc")

add_executable(Galaxy ${SOURCES} ${HEADERS})

target_link_libraries(Galaxy Qt6::Widgets)