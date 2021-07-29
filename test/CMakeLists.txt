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

# add utils dependency to all targets
include_directories("TestUtils")

include(${PROJECT_SOURCE_DIR}/cmake/common/gtest.cmake)
check_gtest()

if(WIN32)

    # populates out_var with the value that the PATH environment variable should have
    # in order to cover all target dependencies required for a ctest.
    # Arguments:
    # GOAL_TARGET -> dependencies related target
    # OUTPUT_VARIABLE -> name of the output variable (in parent scope) that receives the new path
    # a third argument can be specify to simplify recursive operation. If it's value is
    # "EXTRA_PATHS" the current PATH will not be included in the output.
    function(get_win32_path_dependencies GOAL_TARGET OUTPUT_VARIABLE)
        unset(LOCAL_PATH)

        get_target_property(LINK_LIBRARIES_ ${GOAL_TARGET} LINK_LIBRARIES)
        if(NOT "${LINK_LIBRARIES_}" STREQUAL "LINK_LIBRARIES_-NOTFOUND")
            foreach(LIBRARY_LINKED ${LINK_LIBRARIES_})
                if(TARGET ${LIBRARY_LINKED})
                    # Check if is a real target or a target interface
                    get_target_property(type ${LIBRARY_LINKED} TYPE)
                    if(NOT type STREQUAL "INTERFACE_LIBRARY")

                        if(LOCAL_PATH)
                            set(LOCAL_PATH "$<TARGET_FILE_DIR:${LIBRARY_LINKED}>;${LOCAL_PATH}")
                        else(LOCAL_PATH)
                            set(LOCAL_PATH "$<TARGET_FILE_DIR:${LIBRARY_LINKED}>")
                        endif(LOCAL_PATH)

                        # Check for dependencies recursively
                        get_win32_path_dependencies(${LIBRARY_LINKED} DEP_WIN_PATH "EXTRA_PATHS")
                        if(DEP_WIN_PATH)
                            set(LOCAL_PATH "${DEP_WIN_PATH};${LOCAL_PATH}")
                        endif(DEP_WIN_PATH)
                        unset(DEP_WIN_PATH)
                    endif()
                    unset(type)
                endif()
            endforeach()
        endif()

        if( (ARGC EQUAL 2) OR NOT (ARGV2 STREQUAL "EXTRA_PATHS"))
            set(LOCAL_PATH "${LOCAL_PATH};$ENV{PATH}")
            list(REMOVE_DUPLICATES LOCAL_PATH)
            string(REPLACE ";" "\\;" LOCAL_PATH "${LOCAL_PATH}")
        endif()

        set(${OUTPUT_VARIABLE} "${LOCAL_PATH}" PARENT_SCOPE)

    endfunction(get_win32_path_dependencies)

else(WIN32)
    # dummy
    function(get_win32_path_dependencies)
    endfunction(get_win32_path_dependencies)
endif(WIN32)

add_subdirectory(blackbox)
add_subdirectory(unittest)
