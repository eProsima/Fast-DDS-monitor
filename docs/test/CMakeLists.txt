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

####################################################################################################
# Add tests
####################################################################################################

message(STATUS "Building the Fast DDS Monitor documentation tests.")

find_package(Python COMPONENTS Interpreter Development)
if(NOT(${Python_FOUND} AND (${Python_VERSION} VERSION_GREATER "3.6")))
    message(FATAL_ERROR "Building the documentation tests requires Python 3.7")
endif()

# Check docs style
find_program(DOC8 doc8 DOC "path to doc8 executable")
if(DOC8)
    message(STATUS "Found doc8: ${DOC8}")
    add_test(
        NAME documentation.doc8
        COMMAND ${DOC8} --ignore D001 ${PROJECT_SOURCE_DOCS_DIR})
else()
    message(FATAL_ERROR "Could not find doc8")
endif()

# Check docs spelling
add_test(NAME documentation.spell_check
    COMMAND
    ${SPHINX_EXECUTABLE} -W --keep-going
    -b spelling
    -d "${PROJECT_BINARY_DOCS_DIR}/doctrees"
    ${PROJECT_SOURCE_DOCS_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/spelling)
