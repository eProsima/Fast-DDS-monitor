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

# set(BSM_TEST_SOURCE
#     BlackboxStaticMockTest.cpp
#     ${PROJECT_SOURCE_DIR}/src/Engine.cpp)

add_executable(BlackboxStaticMockTest
    BlackboxStaticMockTest.cpp ${PROJECT_SOURCES_NO_MAIN} ${PROJECT_HEADERS} ${QT_RESOURCES})

target_include_directories(BlackboxStaticMockTest PRIVATE
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(BlackboxStaticMockTest PUBLIC
    fastdds-statistics-backend
    static-backend-mock
    ${QT5_LIBRARY_LINKS}
    gtest)

set(BSM_TEST_LIST
    void_)

foreach(test_name ${BSM_TEST_LIST})
    add_test(NAME BlackboxStaticMock.${test_name}
            COMMAND BlackboxStaticMockTest
            --gtest_filter=BlackboxStaticMock.${test_name}:*/BlackboxStaticMock.${test_name}/*)
endforeach()
