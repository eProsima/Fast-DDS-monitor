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
# CMake build rules for Fast DDS Monitor Documentation
###############################################################################
cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5...3.13)

###############################################################################
# Version
###############################################################################
set(PRODUCT_MAJOR_VERSION 3)
set(PRODUCT_MINOR_VERSION 3)
set(PRODUCT_PATCH_VERSION 0)
set(PRODUCT_VERSION_STR ${PRODUCT_MAJOR_VERSION}.${PRODUCT_MINOR_VERSION}.${PRODUCT_PATCH_VERSION})

###############################################################################
# Project
###############################################################################
project(fastdds_monitor_docs)
set(PROJECT_VERSION_MAJOR "${PRODUCT_MAJOR_VERSION}")
set(PROJECT_VERSION_MINOR "${PRODUCT_MINOR_VERSION}")
set(PROJECT_VERSION_PATCH "${PRODUCT_PATCH_VERSION}")
set(PROJECT_VERSION "${PRODUCT_VERSION_STR}")

set(PROJECT_NAME_LARGE "Fast DDS Monitor Documentation")
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
set(${PROJECT_NAME}_DESCRIPTION_SUMMARY "ReadTheDocs documentation of Fast DDS Monitor")
set(${PROJECT_NAME}_DESCRIPTION
    "ReadTheDocs documentation of Fast DDS Monitor")

message(STATUS "Configuring ${PROJECT_NAME_LARGE}")
message(STATUS "Version: ${PROJECT_VERSION}")

###############################################################################
# Test
###############################################################################
option(BUILD_DOCUMENTATION_TESTS "Build Fast DDS Monitor documentation tests" OFF)

if (BUILD_TESTS)
    set(BUILD_DOCUMENTATION_TESTS ON)
endif()


if(BUILD_DOCUMENTATION_TESTS)
    enable_testing()
    include(CTest)
endif()

####################################################################################################
# Build documentation
####################################################################################################

set(PROJECT_SOURCE_DOCS_DIR ${PROJECT_SOURCE_DIR})
set(PROJECT_BINARY_DOCS_DIR ${PROJECT_BINARY_DIR}/docs)
set(DOCS_OUTPUT_HTML_DIR ${PROJECT_BINARY_DOCS_DIR}/html)

# Create docs directories
add_custom_target(doc-dirs
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DOCS_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DOCS_OUTPUT_HTML_DIR}
    COMMENT "Creating documentation directories" VERBATIM)

####################################################################################################
# Build Sphinx documentation
####################################################################################################

# Find sphinx
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
find_package(Sphinx REQUIRED)

set(DOCS_BUILDER html)

# Generate the sphinx documentation
add_custom_target(Sphinx ALL
    COMMAND
    ${SPHINX_EXECUTABLE} -b ${DOCS_BUILDER}
    -d "${PROJECT_BINARY_DOCS_DIR}/doctrees"
    ${PROJECT_SOURCE_DOCS_DIR}
    ${DOCS_OUTPUT_HTML_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Sphinx"
    $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:-Dtodo_include_todos=1>)

# Install the generated docs
install(DIRECTORY ${DOCS_OUTPUT_HTML_DIR}
    DESTINATION docs/${PROJECT_NAME}/sphinx
    COMPONENT monitor-sphinx
    PATTERN ".buildinfo" EXCLUDE)
set(CPACK_COMPONENT_monitor-sphinx_DISPLAY_NAME "Fast DDS Monitor Sphinx")
set(CPACK_COMPONENT_monitor-sphinx_DESCRIPTION
    "eProsima Fast DDS Monitor documentation in ${DOCS_BUILDER} format")
set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} ${DOCS_BUILDER})

# Add tests if required
if(BUILD_DOCUMENTATION_TESTS)
    message(STATUS "Adding documentation tests")
    add_subdirectory(test)
endif()
