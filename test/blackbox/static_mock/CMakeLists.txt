# Copyright 2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
# qt5_add_resources(QT_RESOURCES ${PROJECT_SOURCE_DIR}/qml.qrc)

# # Additional compilation steps required by a Qt program
# # User Interface Compiler (UIC)
# set(CMAKE_AUTOUIC ON)
# # Meta-Object Compiler (MOC)
# set(CMAKE_AUTOMOC ON)
# # Resource Compiler (RCC)
# set(CMAKE_AUTORCC ON)

###############################################################################
# Create Test Executable
###############################################################################
add_executable(BlackboxStaticMockTest
    BlackboxStaticMockTest.cpp ${PROJECT_SOURCES_NO_MAIN} ${PROJECT_HEADERS})

target_include_directories(BlackboxStaticMockTest PRIVATE
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(BlackboxStaticMockTest
    ${QT5_LIBRARY_LINKS}
    fastdds-statistics-backend
    static-backend-mock
    gtest)

set(BSM_TEST_LIST
    void_)

foreach(test_name ${BSM_TEST_LIST})
    add_test(NAME BlackboxStaticMock.${test_name}
            COMMAND BlackboxStaticMockTest
            --gtest_filter=BlackboxStaticMock.${test_name}:*/BlackboxStaticMock.${test_name}/*)
endforeach()
