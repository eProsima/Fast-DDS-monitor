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

# include_directories(${MyProject_SOURCE_DIR}/LibProject/inc)

cmake_minimum_required(VERSION 3.14)

###############################################################################
# Default shared libraries
###############################################################################
# Global flag to cause add_library() to create shared libraries if on.
# If set to true, this will cause all libraries to be built shared
# unless the library was explicitly added as a static library.
option(BUILD_SHARED_LIBS "Create shared libraries by default" ON)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(fastdds-statistics-backend REQUIRED)

###############################################################################
# Compile MOCKs
###############################################################################
if(COMPLEX_MOCK OR BUILD_MOCK)
    add_subdirectory(complex_mock)
endif()

if(STATIC_MOCK OR BUILD_MOCK)
    add_subdirectory(static_mock)
endif()

