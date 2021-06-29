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
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils.h # if all includes are linked, statistics-backend is required
    )

if(MSVC)
    target_compile_definitions(UtilsTest PRIVATE _CRT_DECLARE_NONSTDC_NAMES=0)
endif(MSVC)

target_include_directories(UtilsTest PRIVATE
    ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}>)

target_link_libraries(UtilsTest PUBLIC ${QT5_LIBRARY_LINKS} ${GTEST_LIBRARIES})

get_win32_path_dependencies(UtilsTest TEST_FRIENDLY_PATH)

set(UTILS_TEST_LIST
    to_QString
    to_string
    now_format)

foreach(test_name ${UTILS_TEST_LIST})
    add_test(NAME utilsTest.${test_name}
            COMMAND UtilsTest
            --gtest_filter=utilsTest.${test_name}:*/utilsTest.${test_name}/*)

    if(TEST_FRIENDLY_PATH)
        set_tests_properties(utilsTest.${test_name} PROPERTIES ENVIRONMENT "PATH=${TEST_FRIENDLY_PATH}")
    endif(TEST_FRIENDLY_PATH)

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
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/utils.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/backend_utils.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/backend/backend_types.h
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/model/model_types.h)

add_executable(BackendUtilsTest
    ${BACKENDUTILS_TEST_SOURCE}
    ${BACKENDUTILS_TEST_HEADERS}
    )

if(MSVC)
    target_compile_definitions(BackendUtilsTest PRIVATE _CRT_DECLARE_NONSTDC_NAMES=0)
endif(MSVC)

target_include_directories(BackendUtilsTest PRIVATE
    ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(BackendUtilsTest PUBLIC
    fastdds_statistics_backend
    ${QT5_LIBRARY_LINKS}
    ${GTEST_LIBRARIES})

get_win32_path_dependencies(BackendUtilsTest TEST_FRIENDLY_PATH)

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

    if(TEST_FRIENDLY_PATH)
        set_tests_properties(utilsBackendTest.${test_name} PROPERTIES ENVIRONMENT "PATH=${TEST_FRIENDLY_PATH}")
    endif(TEST_FRIENDLY_PATH)
endforeach()
