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
    "main.cpp"
    "galaxy.cpp"
)

set(HEADERS
    "galaxy.h"
)

add_executable(Galaxy ${SOURCES} ${HEADERS})

target_link_libraries(Galaxy Qt6::Widgets)