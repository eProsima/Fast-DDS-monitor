# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

# include_directories(${MyProject_SOURCE_DIR}/LibProject/inc)

cmake_minimum_required(VERSION 2.8.12)

if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    cmake_policy(SET CMP0048 NEW)
endif()

project(monitor-mock)

find_package(fastdds-statistics-backend REQUIRED)

###############################################################################
# Compile MOCK
###############################################################################
message(STATUS "Configuring MOCK ...")

# add_library (StaticSimpleMock StatisticsBackend.cpp)
# target_include_directories (StaticSimpleMock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# TODO rebase over new Entity id
# add_subdirectory(src/mock/static_mock_simple)

add_subdirectory(src/complex_mock)
