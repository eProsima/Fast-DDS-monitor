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

###############################################################################
# Configure Qt project
###############################################################################
# Set the qml.qrc file containing the QML and other resources of the application
qt5_add_resources(QT_RESOURCES_SUBDIR ${PROJECT_SOURCE_DIR}/qml.qrc)

# Additional compilation steps required by a Qt program
# User Interface Compiler (UIC)
set(CMAKE_AUTOUIC ON)
# Meta-Object Compiler (MOC)
set(CMAKE_AUTOMOC ON)
# Resource Compiler (RCC)
set(CMAKE_AUTORCC ON)

###############################################################################
# Create Test Executable
###############################################################################
add_executable(BlackboxStaticMockTest
    BlackboxStaticMockTest.cpp ${PROJECT_SOURCES_NO_MAIN} ${PROJECT_HEADERS} ${QT_RESOURCES_SUBDIR})

if(MSVC)
    target_compile_definitions(BlackboxStaticMockTest PRIVATE _CRT_DECLARE_NONSTDC_NAMES=0)
endif(MSVC)

target_include_directories(BlackboxStaticMockTest PRIVATE
    ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}>)

target_link_libraries(BlackboxStaticMockTest
    ${QT5_LIBRARY_LINKS}
    fastdds_statistics_backend
    static-backend-mock
    ${GTEST_LIBRARIES})

get_win32_path_dependencies(BlackboxStaticMockTest TEST_FRIENDLY_PATH)

set(BSM_TEST_LIST
    enable_engine)

foreach(test_name ${BSM_TEST_LIST})
    add_test(NAME BlackboxStaticMockTest.${test_name}
            COMMAND BlackboxStaticMockTest
            --gtest_filter=BlackboxStaticMockTest.${test_name}:*/BlackboxStaticMockTest.${test_name}/*)

    if(TEST_FRIENDLY_PATH)
        set_tests_properties(BlackboxStaticMockTest.${test_name} PROPERTIES ENVIRONMENT "PATH=${TEST_FRIENDLY_PATH}")
    endif(TEST_FRIENDLY_PATH)
endforeach()
