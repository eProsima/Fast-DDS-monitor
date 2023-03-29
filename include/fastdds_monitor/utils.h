// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

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
        std::string& st);

//! Cast a const std string to QString Qt type
QString to_QString(
        const std::string& st);

//! Cast a QString to std string
std::string to_string(
        QString& st);

//! Cast a const QString to std string
std::string to_string(
        const QString& st);

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

//! Cast a double to string removing the trailing zeros
std::string double_to_string(
        const double& d);

//! Cast a std::vector<std::string> to QStringList
QStringList to_QStringList(
        const std::vector<std::string>& vector);

std::string erase_substr(
        std::string substring,
        const QString& file_name);
} //namespace utils

#endif // _EPROSIMA_FASTDDS_MONITOR_UTILS_H
