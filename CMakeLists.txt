###############################################################################
# CMake build rules for Fast DDS Monitor
###############################################################################
cmake_minimum_required(VERSION 3.14)

file(READ version.pri FASTDDSMONITORVERSION)

set(IS_TOP_LEVEL TRUE)
if(PROJECT_SOURCE_DIR)
    set(IS_TOP_LEVEL FALSE)
endif()

# Set CMAKE_BUILD_TYPE to Release by default.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

project(fastdds_monitor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Configuring ${PROJECT_NAME}")

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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-unknown-pragmas")
endif()

###############################################################################
# GCC colors if using CCache
###############################################################################
if("${CMAKE_CXX_COMPILER_LAUNCHER}" STREQUAL "ccache" AND
        CMAKE_COMPILER_IS_GNUCXX AND
        CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4,8)
    add_compile_options(-fdiagnostics-color=always)
endif()

###############################################################################
# Test system configuration
###############################################################################
include(${PROJECT_SOURCE_DIR}/cmake/common/check_configuration.cmake)
check_stdcxx()
check_compile_feature()
check_endianness()

###############################################################################
# Check MSVC architecture
###############################################################################
if(MSVC OR MSVC_IDE)
    check_msvc_arch()
endif()

###############################################################################
# Installation paths
###############################################################################
set(BIN_INSTALL_DIR bin/ CACHE PATH "Installation directory for binaries")
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for C++ headers")
set(LIB_INSTALL_DIR lib${LIB_SUFFIX}/ CACHE PATH "Installation directory for libraries")
set(DATA_INSTALL_DIR share/ CACHE PATH "Installation directory for data")
if(WIN32 AND EPROSIMA_INSTALLER AND IS_TOP_LEVEL)
    set(LICENSE_INSTALL_DIR . CACHE PATH "Installation directory for licenses")
else()
    set(LICENSE_INSTALL_DIR ${DATA_INSTALL_DIR}/${PROJECT_NAME} CACHE PATH "Installation directory for licenses")
endif()

###############################################################################
# Load external eProsima projects.
###############################################################################
find_package(StaticMockSimple_FastDDSStatisticsBackend REQUIRED)

###############################################################################
# Compile
###############################################################################
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

message(STATUS "Configuring Fast DDS Monitor...")
set(PROJECT_SOURCES
        src/backend/AsyncBackendConnection.cpp
        src/backend/backend_utils.cpp
        src/backend/SyncBackendConnection.cpp
        src/Engine.cpp
        src/main.cpp
        src/model/dds/EndpointModelItem.cpp
        src/model/dds/ParticipantModelItem.cpp
        src/model/EntityModelItem.cpp
        src/model/ListItem.cpp
        src/model/ListModel.cpp
        src/model/logical/DomainModelItem.cpp
        src/model/logical/TopicModelItem.cpp
        src/model/physical/HostModelItem.cpp
        src/model/physical/ProcessModelItem.cpp
        src/model/physical/UserModelItem.cpp
        src/model/SubListedListItem.cpp
        src/model/SubListedListModel.cpp
        src/model/tree/TreeItem.cpp
        src/model/tree/TreeModel.cpp
        src/utils.cpp
        src/main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
