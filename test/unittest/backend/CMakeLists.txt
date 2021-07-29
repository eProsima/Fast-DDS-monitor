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

################
# SYNC BACKEND #
################

# These references could be reduced, but they are almost every source and header
set(SYNCBACKEND_TEST_SOURCE
    SyncBackendConnectionTest.cpp
    ${PROJECT_SOURCES_NO_MAIN})

set(BACKENDUTILS_TEST_HEADERS
    ${PROJECT_HEADERS})

add_executable(SyncBackendConnectionTest
    ${SYNCBACKEND_TEST_SOURCE}
    ${BACKENDUTILS_TEST_HEADERS}
    )

if(MSVC)
    target_compile_definitions(SyncBackendConnectionTest PRIVATE _CRT_DECLARE_NONSTDC_NAMES=0)
endif(MSVC)

target_include_directories(SyncBackendConnectionTest PRIVATE
    ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}>)

target_link_libraries(SyncBackendConnectionTest PUBLIC
    fastrtps
    fastcdr
    fastdds_statistics_backend
    ${QT5_LIBRARY_LINKS}
    ${GTEST_LIBRARIES})

get_win32_path_dependencies(SyncBackendConnectionTest TEST_FRIENDLY_PATH)

set(SYNCBACKEND_TEST_LIST
    listener)

foreach(test_name ${SYNCBACKEND_TEST_LIST})
    add_test(NAME SyncBackendConnectionTest.${test_name}
            COMMAND SyncBackendConnectionTest
            --gtest_filter=SyncBackendConnectionTest.${test_name}:*/SyncBackendConnectionTest.${test_name}/*)

    if(TEST_FRIENDLY_PATH)
        set_tests_properties(SyncBackendConnectionTest.${test_name} PROPERTIES ENVIRONMENT "PATH=${TEST_FRIENDLY_PATH}")
    endif(TEST_FRIENDLY_PATH)
endforeach()
