###############################################################################
# CMake build rules for Fast DDS Monitor
###############################################################################
cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5...3.13)

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
project(fastdds-monitor)
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
# Load external projects
###############################################################################
set(QT_PATH "" CACHE STRING "Path to the Qt installation folder")
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})

find_package(Qt5 5.15 COMPONENTS Core Widgets Gui Qml Quick Charts REQUIRED)
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(fastdds-statistics-backend REQUIRED)

foreach(c Core Widgets Gui Quick Qml Charts)
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
if(${fastdds-statistics-backend_FOUND})
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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

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
# Configure Qt project
###############################################################################
# Include the Qt5Widgets and QtQml header files for the Qt Framework and QML functions.
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
# Specify the needed Qt definitions
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

# Set the qml.qrc file containing the QML and other resources of the application
qt5_add_resources(QT_RESOURCES qml.qrc)

# Additional compilation steps required by a Qt program
# User Interface Compiler (UIC)
set(CMAKE_AUTOUIC ON)
# Meta-Object Compiler (MOC)
set(CMAKE_AUTOMOC ON)
# Resource Compiler (RCC)
set(CMAKE_AUTORCC ON)

###############################################################################
# Compile Mock if CMake option set
###############################################################################
option(COMPLEX_MOCK "Build Fast DDS Complex Monitor Mock library to simulate Fast DDS Statistics Backend" OFF)
option(STATIC_MOCK "Build Fast DDS Static Monitor Mock library to simulate Fast DDS Statistics Backend" OFF)

# If complex mock is set, static mock does not compile and link
if(COMPLEX_MOCK)
    set(STATIC_MOCK OFF)
endif()

# Compile mock subdirectory
# Only one of the mocks will be compiled and the edstination library would be <backend-mock>
if(COMPLEX_MOCK OR STATIC_MOCK)
    add_subdirectory(mock)
endif()

###############################################################################
# Compile program
###############################################################################
# set(PROJECT_HEADERS
#     include/backend/backend_types.h
#     include/backend/backend_utils.h
#     include/backend/Callback.h
#     include/backend/Listener.h
#     include/backend/SyncBackendConnection.h
#     include/Controller.h
#     include/Engine.h
#     include/model/dds/EndpointModelItem.h
#     include/model/dds/LocatorModelItem.h
#     include/model/dds/ParticipantModelItem.h
#     include/model/EntityContainerModelItem.h
#     include/model/ListItem.h
#     include/model/ListModel.h
#     include/model/logical/DomainModelItem.h
#     include/model/logical/TopicModelItem.h
#     include/model/model_types.h
#     include/model/physical/HostModelItem.h
#     include/model/physical/ProcessModelItem.h
#     include/model/physical/UserModelItem.h
#     include/model/statistics/EntityItem.h
#     include/model/SubListedListItem.h
#     include/model/SubListedListModel.h
#     include/model/tree/TreeItem.h
#     include/model/tree/TreeModel.h
#     include/statistics/StatisticsData.h
#     include/utils.h
# )

file(GLOB_RECURSE ALL_HEADERS
    ${PROJECT_SOURCE_DIR}/include/**/*.h
    )

set(PROJECT_SOURCES
    ${ALL_HEADERS}
    src/Engine.cpp
    src/Controller.cpp
    src/backend/backend_utils.cpp
    src/backend/Listener.cpp
    src/backend/SyncBackendConnection.cpp
    src/main.cpp
    src/model/dds/EndpointModelItem.cpp
    src/model/dds/ParticipantModelItem.cpp
    src/model/ListItem.cpp
    src/model/ListModel.cpp
    src/model/logical/TopicModelItem.cpp
    src/model/physical/ProcessModelItem.cpp
    src/model/SubListedListModel.cpp
    src/model/tree/TreeItem.cpp
    src/model/tree/TreeModel.cpp
    src/statistics/StatisticsData.cpp
    src/utils.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QT_RESOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Qt5 required libraries
set(QT5_LIBRARY_LINKS
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::Charts)

# If any mock CMake option has been set, the monitor will use the mock library
if(COMPLEX_MOCK OR STATIC_MOCK)

    message(STATUS "Compiling monitor with Mock backend library")

    set(BACKEND_LIBRARIES
        backend-mock)

else()

    # Link against fast backend and its dependencies
    set(BACKEND_LIBRARIES
        fastcdr
        fastrtps
        fastdds-statistics-backend)

endif()

target_link_libraries(${PROJECT_NAME} ${QT5_LIBRARY_LINKS} ${BACKEND_LIBRARIES})

