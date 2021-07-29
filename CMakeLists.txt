# Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# This file is part of eProsima Fast DDS Monitor.
#
# eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

###############################################################################
# CMake build rules for Fast DDS Monitor
###############################################################################
cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5...3.13)

# Set CMAKE_BUILD_TYPE to Release by default.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

###############################################################################
# Version
###############################################################################
set(PRODUCT_MAJOR_VERSION 0)
set(PRODUCT_MINOR_VERSION 1)
set(PRODUCT_PATCH_VERSION 0)
set(PRODUCT_VERSION_STR ${PRODUCT_MAJOR_VERSION}.${PRODUCT_MINOR_VERSION}.${PRODUCT_PATCH_VERSION})

###############################################################################
# Project
###############################################################################
project(fastdds_monitor)
set(PROJECT_VERSION_MAJOR "${PRODUCT_MAJOR_VERSION}")
set(PROJECT_VERSION_MINOR "${PRODUCT_MINOR_VERSION}")
set(PROJECT_VERSION_PATCH "${PRODUCT_PATCH_VERSION}")
set(PROJECT_VERSION "${PRODUCT_VERSION_STR}")

set(PROJECT_NAME_LARGE "Fast DDS Monitor")
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
set(${PROJECT_NAME}_DESCRIPTION_SUMMARY "Qt application to display and interact with the Fast DDS statistics module data")
set(${PROJECT_NAME}_DESCRIPTION
    "eProsima ${PROJECT_NAME_LARGE} provides a simple and easy-to-use user application for interacting with data from Fast DDS statistics module")

message(STATUS "Configuring ${PROJECT_NAME_LARGE}")
message(STATUS "Version: ${PROJECT_VERSION}")

###############################################################################
# System configuration
###############################################################################
set(SYSTEM_NAME "${CMAKE_SYSTEM_NAME}")
set(SYSTEM_VERSION "${CMAKE_SYSTEM_VERSION}")
set(SYSTEM_PROCESSOR "${CMAKE_SYSTEM_PROCESSOR}")

###############################################################################
# Build timestamp
###############################################################################
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")

###############################################################################
# Git commit hash
###############################################################################
execute_process(
    COMMAND git log -1 --format=%H
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET)

###############################################################################
# Load external projects
###############################################################################
set(QT_PATH "" CACHE STRING "Path to the Qt installation folder")
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})

find_package(Qt5 5.15 COMPONENTS Core Widgets Gui Qml Quick Charts QuickControls2 REQUIRED)
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(fastdds_statistics_backend REQUIRED)

foreach(c Core Widgets Gui Quick Qml Charts QuickControls2 Utils)
    if(${Qt5${c}_FOUND})
        message(STATUS "Found Qt5${c}: ${Qt5${c}_CONFIG} (found version ${Qt5${c}_VERSION})")
    endif()
endforeach()

if(${fastcdr_FOUND})
    message(STATUS "Fast CDR found!")
endif()
if(${fastrtps_FOUND})
    message(STATUS "Fast DDS found!")
endif()
if(${fastdds_statistics_backend_FOUND})
    message(STATUS "Fast DDS Statistics Backend found!")
endif()

###############################################################################
# Set C++14 as the C++ standard required to build the project
###############################################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

###############################################################################
# Warning level
###############################################################################
if(MSVC OR MSVC_IDE)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
else()
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-unknown-pragmas -Wno-error=deprecated-declarations")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,error")
    endif()
endif()

###############################################################################
# Qt compiler flags, pthreads, and position independent code (PIE)
###############################################################################
if(MSVC OR MSVC_IDE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -pthread -no-pie")
endif()

###############################################################################
# Installation paths
###############################################################################
set(BIN_INSTALL_DIR bin/ CACHE PATH "Installation directory for binaries")
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for C++ headers")
set(LIB_INSTALL_DIR lib${LIB_SUFFIX}/ CACHE PATH "Installation directory for libraries")
set(DATA_INSTALL_DIR share/ CACHE PATH "Installation directory for data")
if(WIN32)
    set(LICENSE_INSTALL_DIR . CACHE PATH "Installation directory for licenses")
else()
    set(LICENSE_INSTALL_DIR ${DATA_INSTALL_DIR}/${PROJECT_NAME} CACHE PATH "Installation directory for licenses")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

###############################################################################
# Compile Mock if CMake option set
###############################################################################
option(COMPLEX_MOCK "Use Fast DDS Complex Monitor Mock library to simulate Fast DDS Statistics Backend" OFF)
option(STATIC_MOCK "Use Fast DDS Static Monitor Mock library to simulate Fast DDS Statistics Backend" OFF)

# Option used to build both mocks independently if they are going to be used or not
# Used with tests proposes
option(BUILD_MOCK "Build Fast DDS Complex and Static Monitor Mock library" OFF)

# If complex mock is set, static mock does not compile and link
if(COMPLEX_MOCK OR STATIC_MOCK)
    set(BUILD_MOCK ON)
endif()

# Compile mock subdirectory
# Only one of the mocks will be compiled and the edstination library would be <backend-mock>
if(BUILD_MOCK)
    add_subdirectory(mock)
endif()

###############################################################################
# Configure Qt project
###############################################################################
# Include the Qt5Widgets and QtQml header files for the Qt Framework and QML functions.
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
# Specify the needed Qt definitions
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${Qt5Quick_DEFINITIONS})

# WARNING
# The creation of the qml_qrc.cpp file is managed by the rcc
# If this functionality is called from the main cmake dir (this) the file will be generated in building time
# Thus, if this file is required in subdirectories, this 4 instructions below must be added in the same
# CMakeList of the executable (Use different name for QT_RESOURCES variable)

# Set the qml.qrc file containing the QML and other resources of the application
qt5_add_resources(QT_RESOURCES ${PROJECT_SOURCE_DIR}/qml.qrc)

# Additional compilation steps required by a Qt program
# User Interface Compiler (UIC)
set(CMAKE_AUTOUIC ON)
# Meta-Object Compiler (MOC)
set(CMAKE_AUTOMOC ON)
# Resource Compiler (RCC)
set(CMAKE_AUTORCC ON)

###############################################################################
# Compile program
###############################################################################
set(PROJECT_HEADERS
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/backend_types.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/backend_utils.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/Callback.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/Listener.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/SyncBackendConnection.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Controller.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Engine.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/io/csv.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/dds/EndpointModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/dds/LocatorModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/dds/ParticipantModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/EntityContainerModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/ListItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/ListModel.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/logical/DomainModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/logical/TopicModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/model_types.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/physical/HostModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/physical/ProcessModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/physical/UserModelItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/statistics/EntityItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/SubListedListItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/SubListedListModel.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/tree/TreeItem.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/tree/TreeModel.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/DataChartBox.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/DataModel.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/dynamic/DynamicDataChartBox.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/dynamic/DynamicStatisticsData.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/historic/HistoricDataChartBox.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/historic/HistoricStatisticsData.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/statistics/StatisticsData.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils.h
)

set(PROJECT_SOURCES_NO_MAIN
    ${PROJECT_SOURCE_DIR}/src/backend/backend_utils.cpp
    ${PROJECT_SOURCE_DIR}/src/backend/Listener.cpp
    ${PROJECT_SOURCE_DIR}/src/backend/SyncBackendConnection.cpp
    ${PROJECT_SOURCE_DIR}/src/Controller.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine.cpp
    ${PROJECT_SOURCE_DIR}/src/io/csv.cpp
    ${PROJECT_SOURCE_DIR}/src/model/dds/EndpointModelItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/dds/ParticipantModelItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/ListItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/ListModel.cpp
    ${PROJECT_SOURCE_DIR}/src/model/logical/TopicModelItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/physical/ProcessModelItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/statistics/EntityItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/SubListedListModel.cpp
    ${PROJECT_SOURCE_DIR}/src/model/tree/TreeItem.cpp
    ${PROJECT_SOURCE_DIR}/src/model/tree/TreeModel.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/DataChartBox.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/DataModel.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/dynamic/DynamicDataChartBox.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/dynamic/DynamicStatisticsData.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/historic/HistoricDataChartBox.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/historic/HistoricStatisticsData.cpp
    ${PROJECT_SOURCE_DIR}/src/statistics/StatisticsData.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
)

# Concatenate main with the rest of the sources
set(PROJECT_SOURCES
    ${PROJECT_SOURCES_NO_MAIN}
    ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Configure config file
configure_file(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.h.in
${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/config.h)

# Avoid launch command prompt when running the executable (.exe) from file explorer
if(MSVC OR MSVC_IDE)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${QT_RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${QT_RESOURCES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}>)

# Qt5 required libraries
set(QT5_LIBRARY_LINKS
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::Charts
    Qt5::QuickControls2)

# If any mock CMake option has been set, the monitor will use the mock library
if(COMPLEX_MOCK)

    message(STATUS "Compiling monitor with Complex Mock backend library")

    target_link_libraries(${PROJECT_NAME}
        ${QT5_LIBRARY_LINKS}
        complex-backend-mock)

elseif(STATIC_MOCK)

    message(STATUS "Compiling monitor with Static Mock backend library")

    target_link_libraries(${PROJECT_NAME}
        ${QT5_LIBRARY_LINKS}
        static-backend-mock)

else()

    # Link against fast backend and its dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${QT5_LIBRARY_LINKS}
        fastcdr
        fastrtps
        fastdds_statistics_backend)

endif()

# Install config.h header
install(FILES ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/config.h
DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}
COMPONENT headers
)

###############################################################################
# Disable QDebug traces in Release
###############################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<NOT:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">>:QT_NO_DEBUG_OUTPUT>)

###############################################################################
# Test
###############################################################################
option(BUILD_TESTS "Build Fast DDS Monitor appliction and documentation tests" OFF)
option(BUILD_APP_TESTS "Build Fast DDS Monitor application tests" OFF)
option(BUILD_DOCUMENTATION_TESTS "Build Fast DDS Monitor documentation tests" OFF)

if (BUILD_TESTS)
    set(BUILD_APP_TESTS ON)
    set(BUILD_DOCUMENTATION_TESTS ON)
endif()

if (BUILD_TESTS OR BUILD_APP_TESTS OR BUILD_DOCUMENTATION_TESTS)
    # CTest needs to be included here, otherwise it is not possible to run the tests from the root
    # of the build directory
    enable_testing()
    include(CTest)
endif()

if (BUILD_TESTS OR BUILD_APP_TESTS)
    add_subdirectory(test)
endif()

###############################################################################
# Documentation
###############################################################################
option(BUILD_DOCUMENTATION "Generate documentation" OFF)
if(BUILD_DOCUMENTATION OR BUILD_DOCUMENTATION_TESTS)
    set(BUILD_DOCUMENTATION ON)
    add_subdirectory(docs)
endif()

###############################################################################
# Packaging
###############################################################################
# Install license
install(FILES ${PROJECT_SOURCE_DIR}/LICENSE
    DESTINATION ${LICENSE_INSTALL_DIR}
    COMPONENT licenses
    )
set(CPACK_COMPONENT_LICENSES_HIDDEN 1)

#Install executable
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR})
