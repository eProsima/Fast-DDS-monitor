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
    now_format
    double_to_string)

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
    fastrtps
    fastcdr
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
