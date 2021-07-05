# Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
