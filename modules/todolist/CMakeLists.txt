cmake_minimum_required(VERSION 3.1.0)

project(
    ToDoList
    VERSION 0.3
    DESCRIPTION "To Do List Module - Galaxy"
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUTPUT_TYPE "OUTPUT_TYPE" CACHE STRING "")

find_package(Qt6 COMPONENTS Widgets REQUIRED)
if (NOT WIN32)
    find_package(Threads REQUIRED)
endif (NOT WIN32)

set(SOURCES
    "main.cpp"
    "todolist.cpp"
    "widgets/sidebartab.cpp"
    "widgets/list.cpp"
    "widgets/sublist.cpp"
    "widgets/element.cpp"
    "widgets/clickable.cpp"
    "widgets/iconbutton.cpp"
    "widgets/popup.cpp"
    "tools/json.cpp"
    "tools/manager.cpp"
    "../../tools/logger.cpp"
)

set(HEADERS
    "todolist.h"
    "widgets/sidebartab.h"
    "widgets/list.h"
    "widgets/sublist.h"
    "widgets/element.h"
    "widgets/clickable.h"
    "widgets/iconbutton.h"
    "widgets/filters.h"
    "widgets/popup.h"
    "tools/json.h"
    "tools/logger.h"
    "tools/manager.h"
    "../../tools/logger.h"
)

qt_add_resources(SOURCES res.qrc)

if (${OUTPUT_TYPE} STREQUAL "dl")
    add_library(ToDoList SHARED ${SOURCES} ${HEADERS})
    set_target_properties(ToDoList PROPERTIES LIBRARY_OUTPUT_NAME todolist) # TODO : allow upper case
    set_target_properties(ToDoList PROPERTIES PREFIX "")
    set_target_properties(ToDoList PROPERTIES SUFFIX ".glx")
    target_compile_definitions(ToDoList PRIVATE DL)
else()
    add_executable(ToDoList ${SOURCES} ${HEADERS})
endif()

if (NOT WIN32)
    target_link_libraries(ToDoList pthread)
endif()

target_link_libraries(ToDoList Qt6::Widgets)