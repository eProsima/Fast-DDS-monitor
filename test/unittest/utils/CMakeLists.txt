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

#########
# UTILS #
#########

set(UTILS_TEST_SOURCE
    utilsTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp)

add_executable(UtilsTest
    ${UTILS_TEST_SOURCE}
    ${PROJECT_SOURCE_DIR}/include/fastdds-monitor/utils.h # if all includes are linked, statistics-backend is required
    )

target_include_directories(UtilsTest PRIVATE
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(UtilsTest PUBLIC ${QT5_LIBRARY_LINKS} gtest)

set(UTILS_TEST_LIST
    to_QString
    to_string
    now_format)

foreach(test_name ${UTILS_TEST_LIST})
    add_test(NAME utilsTest.${test_name}
            COMMAND UtilsTest
            --gtest_filter=utilsTest.${test_name}:*/utilsTest.${test_name}/*)
endforeach()


#################
# BACKEND UTILS #
#################

set(BACKENDUTILS_TEST_SOURCE
    backend_utilsTest.cpp
    ${PROJECT_SOURCE_DIR}/src/backend/backend_utils.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp)

# Needed headers from backend
set(BACKENDUTILS_TEST_HEADERS
    ${PROJECT_SOURCE_DIR}/include/fastdds-monitor/utils.h
    ${PROJECT_SOURCE_DIR}/include/fastdds-monitor/backend/backend_utils.h
    ${PROJECT_SOURCE_DIR}/include/fastdds-monitor/backend/backend_types.h
    ${PROJECT_SOURCE_DIR}/include/fastdds-monitor/model/model_types.h)

add_executable(BackendUtilsTest
    ${BACKENDUTILS_TEST_SOURCE}
    ${BACKENDUTILS_TEST_HEADERS}
    )

target_include_directories(BackendUtilsTest PRIVATE
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(BackendUtilsTest PUBLIC
    fastdds-statistics-backend
    ${QT5_LIBRARY_LINKS}
    gtest)

set(BACKENDUTILS_TEST_LIST
    id_to_QString
    models_id_to_backend_id
    get_info_value
    string_to_entity_kind
    string_to_data_kind
    string_to_statistic_kind)

foreach(test_name ${BACKENDUTILS_TEST_LIST})
    add_test(NAME utilsBackendTest.${test_name}
            COMMAND BackendUtilsTest
            --gtest_filter=utilsBackendTest.${test_name}:*/utilsBackendTest.${test_name}/*)
endforeach()
