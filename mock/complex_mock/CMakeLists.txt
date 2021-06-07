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

cmake_minimum_required(VERSION 3.5)

project(complex-backend-mock)

# Find FastDDS Statistics Backend library
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(fastdds-statistics-backend REQUIRED)

# Allow to use threads
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(COMPLEX_MOCK_SOURCE

    StatisticsBackend.cpp
    EntityId.cpp

    database/Database.cpp
    database/RandomGenerator.cpp

    entities/utils.cpp
    entities/source/Entity.cpp
    entities/source/Host.cpp
    entities/source/User.cpp
    entities/source/Process.cpp
    entities/source/Domain.cpp
    entities/source/Topic.cpp
    entities/source/Participant.cpp
    entities/source/Endpoint.cpp
    entities/source/Locator.cpp
    )

add_library(${PROJECT_NAME} ${COMPLEX_MOCK_SOURCE})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<AND:$<NOT:$<BOOL:${WIN32}>>,$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">>:__DEBUG>
)

target_link_libraries(${PROJECT_NAME} fastdds-statistics-backend)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION Mock/${PROJECT_NAME}/${BIN_INSTALL_DIR})
