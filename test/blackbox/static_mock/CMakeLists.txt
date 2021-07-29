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
    fastrtps
    fastcdr
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
