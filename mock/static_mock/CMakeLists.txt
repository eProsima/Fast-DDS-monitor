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

cmake_minimum_required(VERSION 3.5)

project(static-backend-mock)

# Find FastDDS Statistics Backend library
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(fastdds_statistics_backend REQUIRED)

# Allow to use threads
if(NOT (MSVC OR MSVC_IDE))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(STATIC_MOCK_SOURCE
    StatisticsBackend.cpp
    EntityId.cpp
    )

add_library(${PROJECT_NAME} ${STATIC_MOCK_SOURCE})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<AND:$<NOT:$<BOOL:${WIN32}>>,$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">>:__DEBUG>
)

target_link_libraries(${PROJECT_NAME} PUBLIC fastdds_statistics_backend)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR})
