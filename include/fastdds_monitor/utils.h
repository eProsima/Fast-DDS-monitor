// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file utils.h
 * @brief collection of util general porpose functions related with bakend
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_UTILS_H
#define _EPROSIMA_FASTDDS_MONITOR_UTILS_H

#include <string>

#include <QHash>
#include <QString>

#define MIN(a, b) (((a) < (b))?(a):(b))
#define MAX(a, b) (((a) > (b))?(a):(b))

namespace utils {

//! Cast a std string to QString Qt type
QString to_QString(
        std::string st);

//! Cast a QString to std string
std::string to_string(
        QString st);

/**
 * @brief Returns the current time in string format
 *
 * The format is: "YYYY-MM-DD HH:MM:SS"
 * If \c miliseconds is set to true, the format is: "YYYY-MM-DD HH:MM:SS.sss"
 *
 * @param miliseconds add miliseconds to the string
 * @return string with actual time
 */
std::string now(
        bool miliseconds = true);

} //namespace utils

#endif // _EPROSIMA_FASTDDS_MONITOR_UTILS_H
